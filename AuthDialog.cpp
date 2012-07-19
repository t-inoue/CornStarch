#include "AuthDialog.hpp"

using namespace std;

CAuthDialog::CAuthDialog(void) : m_nameText(NULL), m_passText(NULL)
{
}


CAuthDialog::~CAuthDialog(void)
{
}


//////////////////////////////////////////////////////////////////////


// 初期化を行う
void CAuthDialog::init(wxWindow* parent, const wxString& title)
{
    wxDialog::Create(parent, wxID_ANY, title);

    // 自身に貼り付けるパネルを作成
    m_panel = new wxPanel(this, wxID_ANY);

    // パネル上のテキストボックス
    m_nameText = new wxTextCtrl(
        m_panel, wxID_ANY, "", wxPoint(100, 10), wxSize(200, 30));
    m_passText = new wxTextCtrl(
        m_panel, wxID_ANY, "", wxPoint(100, 50), wxSize(200, 30), wxTE_PASSWORD);
    m_hostText = new wxTextCtrl(
        m_panel, wxID_ANY, "", wxPoint(100, 90), wxSize(200, 30));

    // パネル上の文字
    wxStaticText* sName = new wxStaticText(
        m_panel, wxID_ANY, "ユーザ名", wxPoint(10, 10));
    wxStaticText* sPass = new wxStaticText(
        m_panel, wxID_ANY, "パスワード", wxPoint(10, 50));
    wxStaticText* shost = new wxStaticText(
        m_panel, wxID_ANY, "ホスト名", wxPoint(10, 90));

    // パネル上のボタン
    wxButton* ok = new wxButton(m_panel, wxID_OK, "OK",  wxPoint(250, 150));

    // タイトルバーで消した時の挙動
    SetEscapeId(wxID_CANCEL);

    // エンターキー押下時の挙動
    SetDefaultItem(ok);
}

// ユーザ名を取得する
wxString CAuthDialog::getName(void) const
{
    return m_nameText->GetValue();
}

// パスワードを取得する
wxString CAuthDialog::getPass(void) const
{
    return m_passText->GetValue();
}

// ホスト名を取得する
wxString CAuthDialog::getHostName(void) const
{
    return m_hostText->GetValue();
}