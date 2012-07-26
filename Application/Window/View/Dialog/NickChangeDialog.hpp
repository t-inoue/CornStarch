#pragma once
#include "../../../header.hpp"

namespace CornStarch
{;

// ニックネーム変更用ダイアログ
class CNickChangeDialog : public wxDialog
{
private:
    wxTextCtrl* m_nickText; // ニックネーム入力欄
public:
    CNickChangeDialog(void);
    ~CNickChangeDialog(void);

    // 初期化を行う
    void init(wxWindow* parent, const wxString& title);

    // ニックネームを取得する
    wxString getNickName(void) const;
};

}