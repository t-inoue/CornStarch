#pragma once
#include "AuthDialog.hpp"
#include "ChannelDialog.hpp"
#include "ChangeTopicDialog.hpp"
#include "NickChangeDialog.hpp"
#include "../../Service/ChatServiceBase.hpp"

namespace CornStarch
{;

// 表示するダイアログを管理
class CViewDialog
{
private:
    CAuthDialog* m_authDlg; // ユーザ認証ダイアログ
    CChannelDialog* m_channelDlg; // チャンネル名指定用ダイアログ
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
    int showModalAuthDlg(void);


    // ニックネーム変更ダイアログを表示
    int showModalNickDlg(void);

    // トピック変更ダイアログを表示
    int showModalTopicDlg(void);

    // チャンネル名を取得
    wxString getChannelName(void) const;

    // サービスを取得
    CChatServiceBase* getNewServiceFromDialog(void) const;

    // ニックネームを取得
    wxString getNickName(void) const;

    // トピック名を取得
    wxString getTopic(void) const;
};

}
