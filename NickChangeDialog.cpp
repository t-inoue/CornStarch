#include "NickChangeDialog.hpp"

namespace CornStarch
{;

CNickChangeDialog::CNickChangeDialog(void) : m_nickText(NULL)
{
}


CNickChangeDialog::~CNickChangeDialog(void)
{
}


//////////////////////////////////////////////////////////////////////


// 初期化を行う
void CNickChangeDialog::init(wxWindow* parent, const wxString& title)
{
    wxDialog::Create(parent, wxID_ANY, title);

    // 自身に貼り付けるパネルを作成
    wxPanel* panel = new wxPanel(this, wxID_ANY);

    // パネル上のテキストボックス
    m_nickText = new wxTextCtrl(
        panel, wxID_ANY, "", wxPoint(100, 50), wxSize(100, 30));

    // パネル上の文字
    wxStaticText* sChannel = new wxStaticText(
        panel, wxID_ANY, "ニックネーム", wxPoint(10, 50));

    // パネル上のボタン
    wxButton* ok = new wxButton(panel, wxID_OK, "OK",  wxPoint(250, 150));

    // Escで消した時の挙動
    SetEscapeId(wxID_CANCEL);

    // エンターキー押下時の挙動
    SetDefaultItem(ok);
}

// チャンネル名を取得する
wxString CNickChangeDialog::getNickName(void) const
{
    if (m_nickText != NULL){
        return m_nickText->GetValue();
    }

    return "";
}

}