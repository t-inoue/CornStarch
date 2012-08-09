#include "ServiceSerializer.hpp"
#ifndef _WIN32

using namespace std;

namespace CornStarch
{
;

const wxString CServiceSerializer::PATH = wxString(getenv("HOME"))
        + "/.CornStarch";

CServiceSerializer::CServiceSerializer(void) :
        m_doc(NULL)
{
}

CServiceSerializer::~CServiceSerializer(void)
{
    delete m_doc;
}

//////////////////////////////////////////////////////////////////////

// 初期化を行う
void CServiceSerializer::init(void)
{
    m_doc = new wxXmlDocument();
}

// サービスを受け取り、ファイルに保存する
void CServiceSerializer::saveService(
        const map<int, CChatServiceBase*>& services)
{
    wxXmlNode* root = new wxXmlNode(wxXML_ELEMENT_NODE, "root");

    // 各サービスについて
    map<int, CChatServiceBase*>::const_reverse_iterator it;
    for (it = services.rbegin(); it != services.rend(); it++){

        // サービス情報をRootノードに追加
        addServiceToRoot(root, it->second);
    }

    m_doc->SetRoot(root);
    m_doc->Save(PATH);
    chmod(PATH, S_IRUSR | S_IWUSR);
}

// 保存されたサービス情報を基に、vectorにpushする
void CServiceSerializer::loadService(wxEvtHandler* handler,
        map<int, CChatServiceBase*>& services, int& serviceId)
{
    // ファイルが存在しない時
    if (!wxFileExists(PATH)){
        return;
    }

    // ファイルの読み込みに失敗
    if (!m_doc->Load(PATH)){
        return;
    }

    // ファイルからサーバ情報を読み込み、サービスを作成
    wxXmlNode* child = m_doc->GetRoot()->GetChildren();
    while (child){

        // サービスを作成して追加
        CChatServiceBase* service = newService(child, handler, serviceId);
        services.insert(
                map<int, CChatServiceBase*>::value_type(service->getId(),
                        service));

        // 次のサーバ情報の読み込み
        serviceId++;
        child = child->GetNext();
    }
}

//////////////////////////////////////////////////////////////////////

// XMLNodeからサービスを作成する
CChatServiceBase* CServiceSerializer::newService(wxXmlNode* node,
        wxEvtHandler* handler, int& serviceId)
{
    // サービス作成
    CChatServiceBase* service;
    if (node->GetName() == "StarChat"){ // StarChat
        service = new StarChat::CSCService();
    } else if (node->GetName() == "IRC"){ // IRC
        service = new IRC::CIRCService();
    }

    // 各タグの情報を取得
    wxXmlNode* status = node->GetChildren();
    wxString nick, name, pass, host, user;
    long port;
    vector<wxString> channels;
    while (status){

        // タグ情報の読み込み
        wxString tag = status->GetName();
        if (tag == "user"){
            user = status->GetNodeContent();
        } else if (tag == "pass"){
            pass = status->GetNodeContent();
        } else if (tag == "name"){
            name = status->GetNodeContent();
        } else if (tag == "host"){
            host = status->GetNodeContent();
        } else if (tag == "port"){
            status->GetNodeContent().ToLong(&port);
        }
        if (tag == "channels"){
            wxXmlNode* channel = status->GetChildren();
            while (channel){
                channels.push_back(channel->GetNodeContent());
                channel = channel->GetNext();
            }
        }
        // 次のタグへ
        status = status->GetNext();
    }

    // サービスのパラメータを代入
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
void CServiceSerializer::createNode(wxXmlNode* parent, wxString name,
        wxString content)
{
    wxXmlNode* server1 = new wxXmlNode(parent, wxXML_ELEMENT_NODE, name);
    new wxXmlNode(server1, wxXML_TEXT_NODE, "text", content);
}
// サービス情報をRootノードに追加
void CServiceSerializer::addServiceToRoot(wxXmlNode* root,
        const CChatServiceBase* service)
{
    wxXmlNode* serverRoot;
    if (service->getChatType() == CChatServiceBase::STAR_CHAT){

        // StarChatのとき
        serverRoot = new wxXmlNode(root, wxXML_ELEMENT_NODE, "StarChat");

    } else{
        // IRCのとき
        serverRoot = new wxXmlNode(root, wxXML_ELEMENT_NODE, "IRC");
    }
    createNode(serverRoot, "name", service->getName());
    createNode(serverRoot, "host", service->getHost());
    wxString portString;
    portString<<service->getPort();
    createNode(serverRoot, "port", portString);

    createNode(serverRoot, "user", service->getUserName());
    createNode(serverRoot, "pass", service->getBasic());
    createNode(serverRoot, "nick", service->getUserName());

    if (service->getChatType() == CChatServiceBase::IRC){

        wxXmlNode* server4 = new wxXmlNode(serverRoot, wxXML_ELEMENT_NODE,
                "channels");
        vector<CChannelStatus*> channels = service->getChannels();
        vector<CChannelStatus*>::iterator it = channels.begin();
        while (it != channels.end()){
            wxXmlNode* channel = new wxXmlNode(server4, wxXML_ELEMENT_NODE,
                    "channel");
            new wxXmlNode(channel, wxXML_TEXT_NODE, "text",
                    (*it)->getChannelName());
            it++;
        }
    }

}

}
#endif
