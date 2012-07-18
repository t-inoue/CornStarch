#pragma once
#include "header.hpp"
#include "AuthDialog.hpp"
#include "ChannelDialog.hpp"

// 表示するダイアログを管理
class CViewDialog
{
private:
    CAuthDialog* m_authDlg; // ユーザ認証ダイアログ
    CChannelDialog* m_channelDlg; // チャンネル名指定用ダイアログ
    wxDialog* m_cancelAuthDlg; // ユーザ認証キャンセル用ダイアログ

    wxWindow* m_parent; // 親となるウィンドウ

public:
    CViewDialog(void);
    ~CViewDialog(void);

    // 初期化を行う
    void init(wxWindow* parent);

    // チャンネル名指定用ダイアログを表示
    int showModalChannelDlg(void);

    // ユーザ認証ダイアログを表示
    int showModalAuthDlg(void);

    // ユーザ認証キャンセル用ダイアログを表示
    int showModalAuthCancelDlg(void);

    // ユーザ認証キャンセル用ダイアログを消す
    void destroyAuthCancelDlg(void);

    // チャンネル名を取得
    wxString getChannelName(void) const;

    // ユーザ名を取得
    wxString getUserName(void) const;

    // パスワードを取得
    wxString getPassword(void) const;
};

