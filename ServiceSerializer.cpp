#include "ServiceSerializer.hpp"

using namespace std;

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

    //m_doc->Load("serial/test2.xml");
    //wxXmlNode* node = m_doc->GetRoot();
    //m_doc->Save("serial/test3.xml");

    wxXmlNode* root = new wxXmlNode(wxXML_DOCUMENT_NODE, "root");
    wxXmlNode* parent = new wxXmlNode(wxXML_ELEMENT_NODE, "element", "element");
    wxXmlNode* child = new wxXmlNode(wxXML_TEXT_NODE, "text", "text");

    root->SetChildren(parent);
    parent->SetChildren(child);
    //child->SetParent(parent);

    m_doc->SetRoot(root);
    m_doc->Save("serial/filename.xml");
}

// サービスを受け取り、ファイルに保存する
void CServiceSerializer::saveService(const vector<CConnectionContents*> services)
{
    //wxXmlNode* child = 

    // 各サービスについてループ
    //vector<CConnectionContents*>::const_iterator it;
    //for (it = services.begin(); it != services.end(); it++){
    //    m_doc->SetRoot(child);
    //    m_doc->Save("filename.xml");
    //}
}
