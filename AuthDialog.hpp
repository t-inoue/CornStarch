#pragma once
#include "header.hpp"

// ユーザ名登録用ダイアログ
class CAuthDialog : public wxDialog
{
private:
    wxTextCtrl* m_nameText; // ユーザ名入力欄
    wxTextCtrl* m_passText; // パスワード入力欄

public:
    CAuthDialog(void);
    ~CAuthDialog(void);

    // 初期化を行う
    void init(wxWindow* parent, const wxString& title);

    // ユーザ名を取得する
    wxString getName(void) const;

    // パスワードを取得する
    wxString getPass(void) const;

};

