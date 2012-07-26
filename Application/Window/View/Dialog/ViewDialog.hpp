#pragma once
#include "../../../header.hpp"
#include "SCAuthDialog.hpp"
#include "IRCAuthDialog.hpp"
#include "ChannelDialog.hpp"
#include "ChangeTopicDialog.hpp"
#include "NickChangeDialog.hpp"

namespace CornStarch
{;

// 表示するダイアログを管理
class CViewDialog
{
private:
    CAuthDialog* m_authDlg; // ユーザ認証ダイアログ
    CChannelDialog* m_channelDlg; // チャンネル名指定用ダイアログ
    wxDialog* m_cancelAuthDlg; // ユーザ認証キャンセル用ダイアログ
    CNickChangeDialog* m_nickDlg; // ニックネーム変更用ダイアログ
    CChangeTopicDialog* m_topicDlg; // トピック変更用ダイアログ

    wxWindow* m_parent; // 親となるウィンドウ

public:
    CViewDialog(void);
    ~CViewDialog(void);

    // 初期化を行う
    void init(wxWindow* parent);

    // チャンネル名指定用ダイアログを表示
    int showModalChannelDlg(void);

    // ユーザ認証ダイアログを表示(SC)
    int showModalSCAuthDlg(void);

    // ユーザ認証ダイアログを表示(IRC)
    int showModalIRCAuthDlg(void);

    // ユーザ認証キャンセル用ダイアログを表示
    int showModalAuthCancelDlg(void);

    // ニックネーム変更ダイアログを表示
    int showModalNickDlg(void);

    // トピック変更ダイアログを表示
    int showModalTopicDlg(void);

    // ユーザ認証キャンセル用ダイアログを消す
    void destroyAuthCancelDlg(void);

    // チャンネル名を取得
    wxString getChannelName(void) const;

    // ユーザ名を取得
    wxString getUserName(void) const;

    // パスワードを取得
    wxString getPassword(void) const;

    // ホスト名を取得
    wxString getHostName(void) const;

    // ニックネームを取得
    wxString getNickName(void) const;

    // トピック名を取得
    wxString getTopic(void) const;
};

}