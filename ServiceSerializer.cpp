#include "ServiceSerializer.hpp"

using namespace std;
const wxString CServiceSerializer::PATH = "filename.xml";

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
void CServiceSerializer::saveService(const vector<CChatServiceBase*>& services)
{
    wxXmlNode* docRoot = new wxXmlNode(wxXML_DOCUMENT_NODE, "R");
    wxXmlNode* root = new wxXmlNode(wxXML_ELEMENT_NODE, "root");

    // 各サーバについて
    vector<CChatServiceBase*>::const_iterator it;
    for (it = services.begin(); it != services.end(); it++){
        if ((*it)->getChatType() == CChatServiceBase::STAR_CHAT){

            // StarChatのとき
            wxXmlNode* serverRoot = new wxXmlNode(root, wxXML_ELEMENT_NODE, "StarChat");
            wxXmlNode* server1 = new wxXmlNode(serverRoot, wxXML_ELEMENT_NODE, "host");
            wxXmlNode* child1 = new wxXmlNode(server1, wxXML_TEXT_NODE, "text", (*it)->getHost());
            wxXmlNode* server3 = new wxXmlNode(serverRoot, wxXML_ELEMENT_NODE, "pass");
            wxXmlNode* child3 = new wxXmlNode(server3, wxXML_TEXT_NODE, "text", (*it)->getBasic());
            wxXmlNode* server2 = new wxXmlNode(serverRoot, wxXML_ELEMENT_NODE, "name");
            wxXmlNode* child2 = new wxXmlNode(server2, wxXML_TEXT_NODE, "text", (*it)->getUserName());
        } else {

            // IRCのとき
            wxXmlNode* serverRoot = new wxXmlNode(root, wxXML_ELEMENT_NODE, "IRC");
            wxXmlNode* server1 = new wxXmlNode(serverRoot, wxXML_ELEMENT_NODE, "host");
            wxXmlNode* child1 = new wxXmlNode(server1, wxXML_TEXT_NODE, "text", (*it)->getHost());
            wxXmlNode* server2 = new wxXmlNode(serverRoot, wxXML_ELEMENT_NODE, "name");
            wxXmlNode* child2 = new wxXmlNode(server2, wxXML_TEXT_NODE, "text", (*it)->getUserName());
            wxXmlNode* server3 = new wxXmlNode(serverRoot, wxXML_ELEMENT_NODE, "nick");
            wxXmlNode* child3 = new wxXmlNode(server3, wxXML_TEXT_NODE, "text", (*it)->getNickName());
        }
    }

    m_doc->SetRoot(root);
    m_doc->Save(PATH);
}

// 保存されたサービス情報を基に、vectorにpushする
void CServiceSerializer::loadService(wxEvtHandler* handler, 
    vector<CChatServiceBase*>& services)
{
	CChatServiceBase* service;

    // ファイルが存在しない時
    if (!m_doc->Load(PATH)){
        return;
    }

    // 各サーバ情報の読み込み
    wxXmlNode* child = m_doc->GetRoot()->GetChildren();

    int count = 1000;

    // 各サーバの情報から、サービスを作成
    while(child){

        if (child->GetName() == "StarChat"){

            // SC 文字列読み込み
            wxXmlNode* status = child->GetChildren();
            wxString name = status->GetChildren()->GetContent();
            status = status->GetNext();
            wxString pass = status->GetChildren()->GetContent();
            status = status->GetNext();
            wxString host = status->GetChildren()->GetContent();

            // サービス作成
            service = new CSCService();
            service->setId(count++);
            service->init(handler);
            service->setHost(host);
            services.push_back(service);
            service->regUser(name, pass);

        } else if (child->GetName() == "IRC"){

            // IRC 文字列読み込み
            wxXmlNode* status = child->GetChildren();
            wxString nick = status->GetChildren()->GetContent();
            status = status->GetNext();
            wxString name = status->GetChildren()->GetContent();
            status = status->GetNext();
            wxString host = status->GetChildren()->GetContent();

            // サービス作成
            service = new CornStarch::IRC::CIRCService();
            service->setId(count++);
            service->init(handler);
            service->setHost(host);
            services.push_back(service);
            service->regUser(nick, "");
        }

        // 次のサーバ情報の読み込み
        child = child->GetNext();
    }
}

