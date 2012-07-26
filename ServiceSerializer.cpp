#include "ServiceSerializer.hpp"
#ifndef _WIN32

using namespace std;

namespace CornStarch
{;

const wxString CServiceSerializer::PATH = wxString(getenv("HOME")) + "/.CornStarch";

CServiceSerializer::CServiceSerializer(void) : m_doc(NULL)
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
void CServiceSerializer::saveService(const map<int,CChatServiceBase*>& services)
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
        services.insert(map<int, CChatServiceBase*>::value_type(service->getId(), service));

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
        service = new CSCService();
    } else if (node->GetName() == "IRC"){ // IRC
        service = new CornStarch::IRC::CIRCService();
    }

    // 各タグの情報を取得
    wxXmlNode* status = node->GetChildren();
    wxString nick, name, pass, host;
    while (status){

        // タグ情報の読み込み
        wxString tag = status->GetName();
        if (tag == "name"){
            name = status->GetNodeContent();
        } else if (tag == "pass"){
            pass = status->GetNodeContent();
        } else if (tag == "host"){
            host = status->GetNodeContent();
        }

        // 次のタグへ
        status = status->GetNext();
    }

    // サービスのパラメータを代入
    service->setId(serviceId);
    service->init(handler);
    service->setHost(host);
    service->regUser(name, pass);
    return service;
}

// サービス情報をRootノードに追加
void CServiceSerializer::addServiceToRoot(wxXmlNode* root, const CChatServiceBase* service)
{
    if (service->getChatType() == CChatServiceBase::STAR_CHAT){

        // StarChatのとき
        wxXmlNode* serverRoot = new wxXmlNode(root, wxXML_ELEMENT_NODE, "StarChat");
        wxXmlNode* server1 = new wxXmlNode(serverRoot, wxXML_ELEMENT_NODE, "host");
        wxXmlNode* child1 = new wxXmlNode(server1, wxXML_TEXT_NODE, "text", service->getHost());
        wxXmlNode* server3 = new wxXmlNode(serverRoot, wxXML_ELEMENT_NODE, "pass");
        wxXmlNode* child3 = new wxXmlNode(server3, wxXML_TEXT_NODE, "text", service->getBasic());
        wxXmlNode* server2 = new wxXmlNode(serverRoot, wxXML_ELEMENT_NODE, "name");
        wxXmlNode* child2 = new wxXmlNode(server2, wxXML_TEXT_NODE, "text", service->getUserName());
    } else {

        // IRCのとき
        wxXmlNode* serverRoot = new wxXmlNode(root, wxXML_ELEMENT_NODE, "IRC");
        wxXmlNode* server1 = new wxXmlNode(serverRoot, wxXML_ELEMENT_NODE, "host");
        wxXmlNode* child1 = new wxXmlNode(server1, wxXML_TEXT_NODE, "text", service->getHost());
        wxXmlNode* server2 = new wxXmlNode(serverRoot, wxXML_ELEMENT_NODE, "name");
        wxXmlNode* child2 = new wxXmlNode(server2, wxXML_TEXT_NODE, "text", service->getUserName());
        wxXmlNode* server3 = new wxXmlNode(serverRoot, wxXML_ELEMENT_NODE, "nick");
        wxXmlNode* child3 = new wxXmlNode(server3, wxXML_TEXT_NODE, "text", service->getUserName());
    }
}

}
#endif