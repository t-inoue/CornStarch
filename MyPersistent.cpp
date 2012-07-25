#include "MyPersistent.hpp"

using namespace std;

const wxString CMyPersistent::KEY_PLACE
    = "HKEY_CURRENT_USER\\Software\\CornStarch";

CMyPersistent::CMyPersistent(void) : m_regKey(NULL)
{
}


CMyPersistent::~CMyPersistent(void)
{
    delete m_regKey;
}


//////////////////////////////////////////////////////////////////////


// 初期化を行う
void CMyPersistent::init(void)
{
    m_regKey = new wxRegKey(KEY_PLACE);

    // 存在しなければ新規作成
    if (!m_regKey->Exists()){
        m_regKey->Create();
    }
}

// サービスを受け取り、ファイルに保存する
void CMyPersistent::saveService(const vector<CChatServiceBase*>& services)
{
    // CornStarchレジストリの初期化
    m_regKey->DeleteSelf();
    m_regKey->Create();
    m_regKey->Open();

    // 各サービスについてループ
    int uniqueId = 0; // レジストリ上のサーバ情報を区別するためのID
    vector<CChatServiceBase*>::const_iterator it;
    for (it = services.begin(); it != services.end(); it++){

        // レジストリに保存
        saveReg(*it, uniqueId++);
    }
    m_regKey->Close();
}

// 保存されたサービス情報を基に、vectorにpushする
void CMyPersistent::loadService(wxEvtHandler* handler, vector<CChatServiceBase*>& services,
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
        services.push_back(service);

        // 次の要素の取得
        serviceId++;
        m_regKey->GetNextKey(key, index);
    }

    m_regKey->Close();
}

//////////////////////////////////////////////////////////////////////

// レジスタに保存する
void CMyPersistent::saveReg(const CChatServiceBase* service, int id)
{
    wxString idStr;
    idStr.Printf("%d", id);

    // レジストリ保存
    wxRegKey reg(*m_regKey, idStr);
    if (!reg.Exists()){
        reg.Create();
    }

    if (service->getChatType() == CChatServiceBase::STAR_CHAT){

        // StarChatのとき
        wxRegKey scReg(reg, "StarChat");
        if (!scReg.Exists()){
            scReg.Create();
        }
        scReg.SetValue("HOST", service->getHost());
        scReg.SetValue("PASS", service->getBasic());
        scReg.SetValue("NAME", service->getUserName());

    } else {

        // IRCのとき
        wxRegKey ircReg(reg, "IRC");
        if (!ircReg.Exists()){
            ircReg.Create();
        }
        ircReg.SetValue("HOST", service->getHost());
        ircReg.SetValue("NICK", service->getUserName());
        ircReg.SetValue("NAME", service->getUserName());
    }
}

// レジスタのサブキーからサービスを作成する
CChatServiceBase* CMyPersistent::newService(wxEvtHandler* handler, 
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
    reg.GetKeyInfo(NULL, NULL, &length, NULL);

    // サービスの作成
    CChatServiceBase* service;
    if (type == "StarChat"){ // StarChat
        service = new CSCService();
    } else if (type == "IRC"){ // IRC
        service = new CornStarch::IRC::CIRCService();
    }

    // レジストリからパラメータの読み込み
    wxString nick, name, pass, host;
    wxString prop;
    long idx;
    reg.GetFirstValue(prop, idx);
    for (size_t j = 0; j < length; j++){
        if (prop == "NAME"){
            reg.QueryValue(prop, name);
        } else if (prop == "PASS"){
            reg.QueryValue(prop, pass);
        } else if (prop == "HOST"){
            reg.QueryValue(prop, host);
        }

        // 次の要素へ
        reg.GetNextValue(prop, idx);
    }

    // サービスのパラメータ注入
    service->setId(serviceId);
    service->init(handler);
    service->setHost(host);
    service->regUser(name, pass);

    return service;
}
