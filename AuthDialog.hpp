#pragma once
#include "header.hpp"

namespace CornStarch
{;

// ユーザ名登録用ダイアログ
class CAuthDialog : public wxDialog
{
protected:
    wxPanel* m_panel; // 自身に貼り付けるパネル

    wxTextCtrl* m_nameText; // ユーザ名入力欄
    wxTextCtrl* m_passText; // パスワード入力欄
    wxTextCtrl* m_hostText; // host名入力欄

public:
    CAuthDialog(void);
    virtual ~CAuthDialog(void);

    // 初期化を行う
    void init(wxWindow* parent, const wxString& title);

    // ユーザ名を取得する
    wxString getName(void) const;

    // パスワードを取得する
    wxString getPass(void) const;

    // ホスト名を取得する
    wxString getHostName(void) const;
};

}