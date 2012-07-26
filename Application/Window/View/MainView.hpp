#pragma once
#include "Dialog/ViewDialog.hpp"
#include "Menubar/MainMenuBar.hpp"
#include "Panel/MainPanel.hpp"
#include "MainNotifier.hpp"
#include <map>

namespace CornStarch
{;

// ビュー部分(メニューバー、画面、ダイアログ)を管理
class CMainView
{
private:
    CMainMenuBar* m_menuBar; // メニューバーを管理
    CViewDialog* m_dialog; // ダイアログを管理
    CMainPanel* m_panel; // 各ペインを管理
    CMainNotifier* m_notifier; // 通知を行う

public:
    CMainView(void);
    ~CMainView(void);

    // 初期化を行う
    void init(wxWindow* parent);

public: // 各ペインに関するメソッド

    // 投稿ペインのIDを取得する
    wxWindowID getPostPaneID(void) const;

    // チャンネルペインのIDを取得する
    wxWindowID getCnPaneID(void) const;

    // メンバーペインのIDを取得する
    wxWindowID getMemPaneID(void) const;

    // 指定したチャンネルを選択済み項目にする
    void setSelectedChannel(const wxString& channelName);

    // メッセージ一覧を表示する
    void displayMessages(const std::vector<CMessageData*>& messages,
        const std::map<wxString, wxString>& nickTable);

    // メンバー一覧を表示する
    void displayMembers(const std::vector<CMemberData*>& members);

    // チャンネル一覧を表示する
    void displayChannels(const std::map<int,CChatServiceBase*>& services);

    // メッセージ一覧をクリアする。
    void clearMessages(void);

    // メンバー一覧をクリアする
    void clearMembers(void);

    // チャンネル一覧をクリアする
    void clearChannels(void);



    // 投稿用ペインの文字を消す
    void clearPostPaneText(void);

    // ログ一覧にログを表示する
    void displayLogs(const std::vector<CChatLog*>& logs);

public: // メニューバーに関するメソッド

    // メニューバーを取得する
    CMainMenuBar* getMenuBar(void) const;

public: // ダイアログに関するメソッド

    // メッセージボックスを表示する
    void showMsgBox(const wxString& message);

    // 認証ダイアログを表示する(SC)
    int showModalSCAuthDlg(void);

    // 認証ダイアログを表示する(IRC)
    int showModalIRCAuthDlg(void);

    // チャンネル名指定用ダイアログを表示する
    int showModalChannelDlg(void);

    // 認証中止ダイアログを表示する
    int showModalAuthCancelDlg(void);

    // ニックネーム変更ダイアログを表示
    int showModalNickDlg(void);

    // トピック変更ダイアログを表示
    int showModalTopicDlg(void);

    // 認証中止ダイアログを消す
    void clearAuthCancelDlg(void);

    // ユーザ名をwxStringで取得する
    wxString getDlgUserName(void) const;

    // パスワードをwxStringで取得する
    wxString getDlgPassword(void) const;

    // チャンネル名を取得する
    wxString getDlgChannelName(void) const;

    // ホスト名を取得
    wxString getDlgHostName(void) const;

    // ニックネームを取得
    wxString getNickName(void) const;

    // トピック名を取得
    wxString getTopic(void) const;

public: // 通知に関するメソッド

    // メッセージを通知する
    void messageNotify(const wxString& title, const wxString& message);
};

}