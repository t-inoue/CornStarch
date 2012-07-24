#include "IRCAuthDialog.hpp"


CIRCAuthDialog::CIRCAuthDialog(void)
{
}


CIRCAuthDialog::~CIRCAuthDialog(void)
{
}


//////////////////////////////////////////////////////////////////////


// 初期化を行う
void CIRCAuthDialog::init(wxWindow* parent, const wxString& title)
{
    CAuthDialog::init(parent, title);

    // テキストボックス
    m_nickText = new wxTextCtrl(
        m_panel, wxID_ANY, "", wxPoint(100, 90), wxSize(200, 30));

    // 文字
    wxStaticText* shost = new wxStaticText(
        m_panel, wxID_ANY, "ニックネーム", wxPoint(10, 90));
}

// ニックネームを取得する
wxString CIRCAuthDialog::getNick(void) const
{
    return m_nickText->GetValue();
}
