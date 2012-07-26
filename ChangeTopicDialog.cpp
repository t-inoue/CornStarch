#include "ChangeTopicDialog.hpp"

namespace CornStarch
{;

CChangeTopicDialog::CChangeTopicDialog(void)
{
}


CChangeTopicDialog::~CChangeTopicDialog(void)
{
}


//////////////////////////////////////////////////////////////////////


// 初期化を行う
void CChangeTopicDialog::init(wxWindow* parent, const wxString& title)
{
    wxDialog::Create(parent, wxID_ANY, title);

    // 自身に貼り付けるパネルを作成
    wxPanel* panel = new wxPanel(this, wxID_ANY);

    // パネル上のテキストボックス
    m_topicText = new wxTextCtrl(
        panel, wxID_ANY, "", wxPoint(100, 50), wxSize(100, 30));

    // パネル上の文字
    wxStaticText* sChannel = new wxStaticText(
        panel, wxID_ANY, "トピック", wxPoint(10, 50));

    // パネル上のボタン
    wxButton* ok = new wxButton(panel, wxID_OK, "OK",  wxPoint(250, 150));

    // Escで消した時の挙動
    SetEscapeId(wxID_CANCEL);

    // エンターキー押下時の挙動
    SetDefaultItem(ok);
}

// チャンネル名を取得する
wxString CChangeTopicDialog::getTopic(void) const
{
    if (m_topicText != NULL){
        return m_topicText->GetValue();
    }

    return "";
}

}