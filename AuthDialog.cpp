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
    wxPanel* panel = new wxPanel(this, wxID_ANY);

    // パネル上のテキストボックス
    m_nameText = new wxTextCtrl(
        panel, wxID_ANY, "", wxPoint(100, 10), wxSize(100, 30));
    m_passText = new wxTextCtrl(
        panel, wxID_ANY, "", wxPoint(100, 50), wxSize(100, 30), wxTE_PASSWORD);

    // パネル上の文字
    wxStaticText* sName = new wxStaticText(
        panel, wxID_ANY, "ユーザ名", wxPoint(10, 10));
    wxStaticText* sPass = new wxStaticText(
        panel, wxID_ANY, "パスワード", wxPoint(10, 50));

    // パネル上のボタン
    wxButton* ok = new wxButton(panel, wxID_OK, "OK",  wxPoint(250, 150));

    // タイトルバーで消した時の挙動
    SetEscapeId(wxID_CANCEL);

    // エンターキー押下時の挙動
    SetDefaultItem(ok);
}

// ユーザ名を取得する
wxString CAuthDialog::getName(void) const
{
    if (m_nameText != NULL){
        return m_nameText->GetValue();
    }

    return "";
}

// パスワードを取得する
wxString CAuthDialog::getPass(void) const
{
    if (m_passText != NULL){
        return m_passText->GetValue();
    }

    return "";
}

