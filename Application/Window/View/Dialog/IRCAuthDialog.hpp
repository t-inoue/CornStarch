#pragma once
#include "AuthDialog.hpp"

namespace CornStarch
{;

// IRCのサーバ追加用認証ダイアログ
class CIRCAuthDialog : public CAuthDialog
{
private:
    wxTextCtrl* m_nickText;

public:
    CIRCAuthDialog(void);
    ~CIRCAuthDialog(void);

    // 初期化を行う
    void init(wxWindow* parent, const wxString& title);

    // ニックネームを取得する
    wxString getNick(void) const;
};

}