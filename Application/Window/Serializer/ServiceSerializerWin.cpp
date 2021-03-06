﻿#include "ServiceSerializerWin.hpp"
#ifdef _WIN32

using namespace std;

namespace CornStarch
{;

const wxString CServiceSerializer::KEY_PLACE
    = "HKEY_CURRENT_USER\\Software\\CornStarch";

CServiceSerializer::CServiceSerializer(void) : m_regKey(NULL)
{
}


CServiceSerializer::~CServiceSerializer(void)
{
    delete m_regKey;
}


//////////////////////////////////////////////////////////////////////


// 初期化を行う
void CServiceSerializer::init(void)
{
    m_regKey = new wxRegKey(KEY_PLACE);

    // 存在しなければ新規作成
    if (!m_regKey->Exists()){
        m_regKey->Create();
    }
}

// サービスを受け取り、ファイルに保存する
void CServiceSerializer::saveService(const map<int, CChatServiceBase*>& services)
{
    // CornStarchレジストリの初期化
    m_regKey->DeleteSelf();
    m_regKey->Create();
    m_regKey->Open();

    // 各サービスについてループ
    int uniqueId = 0; // レジストリ上のサーバ情報を区別するためのID
    map<int, CChatServiceBase*>::const_iterator it;
    for (it = services.begin(); it != services.end(); it++){

        // レジストリに保存
        saveReg(it->second, uniqueId++);
    }
    m_regKey->Close();
}

// 保存されたサービス情報を基に、vectorにpushする
void CServiceSerializer::loadService(wxEvtHandler* handler, map<int, CChatServiceBase*>& services,
    int& serviceId)
{
    m_regKey->Open(wxRegKey::Read);

    // サービスの個数
    size_t num;
    m_regKey->GetKeyInfo(&num, NULL, NULL, NULL);

    // 最初のサービスの取得
    wxString key;
    long index;
    m_regKey->GetFirstKey(key, index);

    // 各サービスについて
    for (size_t i = 0; i < num; i++){

        CChatServiceBase* service = newService(handler, key, serviceId);
        services.insert(map<int, CChatServiceBase*>::value_type(serviceId, service));

        // 次の要素の取得
        serviceId++;
        m_regKey->GetNextKey(key, index);
    }

    m_regKey->Close();
}

//////////////////////////////////////////////////////////////////////

// レジスタに保存する
void CServiceSerializer::saveReg(const CChatServiceBase* service, int id)
{
    wxString idStr;
    idStr.Printf("%d", id);

    // レジストリ保存
    wxRegKey reg(*m_regKey, idStr);
    if (!reg.Exists()){
        reg.Create();
    }
    wxString portString;
    portString<<service->getPort();
    if (service->getChatType() == CChatServiceBase::STAR_CHAT){

        // StarChatのとき
        wxRegKey scReg(reg, "StarChat");
        if (!scReg.Exists()){
            scReg.Create();
        }
        scReg.SetValue("NAME", service->getName()));
        scReg.SetValue("HOST", service->getHost());
        scReg.SetValue("PASS", service->getBasic());
        scReg.SetValue("USER", service->getUserName());
        scReg.SetValue("PORT", portString);

    } else {

        // IRCのとき
        wxRegKey ircReg(reg, "IRC");
        if (!ircReg.Exists()){
            ircReg.Create();
        }
        ircReg.SetValue("NAME", service->getName()));
        ircReg.SetValue("HOST", service->getHost());
        ircReg.SetValue("NICK", service->getUserName());
        ircReg.SetValue("USER", service->getUserName());
        ircReg.SetValue("PORT", portString);

        // チャンネルを保存
        vector<wxString> channels = service->getChannels();
        if (channels.size() != 0){
            wxRegKey ch(ircReg, "CHANNEL");
            if (!ch.Exists()){
                ch.Create();
            }

            // チャンネル情報を保存
            vector<wxString>::const_iterator it;
            for (it = channels.begin(); it != channels.end(); it++){
                ch.SetValue((*it), (*it));
            }
        }
    }
}

// レジスタのサブキーからサービスを作成する
CChatServiceBase* CServiceSerializer::newService(wxEvtHandler* handler, 
    const wxString& subKey, int serviceId)
{
    // サーバの種類を取得
    wxRegKey regType(*m_regKey, subKey);
    wxString type;
    long idxaa;
    regType.GetFirstKey(type, idxaa);

    // サーバ情報要素取得用
    wxRegKey reg(regType, type);
    reg.Open(wxRegKey::Read);
    wxString value;

    // 情報要素の数
    size_t length;
    size_t subKeyNum;
    reg.GetKeyInfo(&subKeyNum, NULL, &length, NULL);

    // サービスの作成
    CChatServiceBase* service;
    if (type == "StarChat"){ // StarChat
        service = new StarChat::CSCService();
    } else if (type == "IRC"){ // IRC
        service = new IRC::CIRCService();
    }

    // レジストリからパラメータの読み込み
    wxString nick, name, pass, host,user,portString;
    long port;
    wxString prop;
    long idx;
    reg.GetFirstValue(prop, idx);

    vector<wxString> channels;

    for (size_t j = 0; j < length; j++){
        if (prop == "NAME"){
            reg.QueryValue(prop, name);
        } else if (prop == "PASS"){
            reg.QueryValue(prop, pass);
        } else if (prop == "USER"){
                   reg.QueryValue(prop, user);
        } else if (prop == "HOST"){
            reg.QueryValue(prop, host);
        } else if (prop == "PORT"){
                 reg.QueryValue(prop, portString);
                 portString.ToLong(&port);
        }

        // 次の要素へ
        reg.GetNextValue(prop, idx);
    }

    for(int k = 0; k < subKeyNum; k++){

        // レジストリのサブキーからパラメータを読み込む
        wxRegKey ch(reg, "CHANNEL");
        ch.Open(wxRegKey::Read);
        size_t values;
        ch.GetKeyInfo(NULL, NULL, &values, NULL);

        long ix;
        wxString chName;
        wxString result;
        ch.GetFirstValue(chName, ix);
        for (size_t k = 0; k < values; k++){
            ch.QueryValue(chName, result);
            channels.push_back(result);
            ch.GetNextValue(chName, ix);
        }
    }

    // サービスのパラメータ注入
    service->setId(serviceId);
    service->init(handler);
    service->setName(name);
     service->setPort(port);
     service->setHost(host);
     service->setSavedChannels(channels);
     service->registerUserBasiscEncoded(user, pass);
     service->connect();

    return service;
}

}
#endif
