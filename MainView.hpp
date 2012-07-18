#pragma once
#include "ViewDialog.hpp"
#include "MainMenuBar.hpp"
#include "MainPanel.hpp"
#include <map>

// ビュー部分(メニューバー、画面、ダイアログ)を管理
class CMainView
{
private:
    CMainMenuBar* m_menuBar; // メニューバーを管理
    CViewDialog* m_dialog; // ダイアログを管理
    CMainPanel* m_panel; // 各ペインを管理

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

    // 選択されているチャンネル名を取得する
    wxString getSelectedChannel(void) const;

    // sashの位置を更新する
    void updateSashPos(const wxSize& size);

    // 指定したチャンネルを選択済み項目にする
    void setSelectedChannel(const wxString& channelName);

    // メッセージ一覧を表示する
    void displayMessages(const std::vector<CMessageData*>& messages,
        const std::map<wxString, wxString>& nickTable);

    // メンバー一覧を表示する
    void displayMembers(const std::vector<CMemberData*>& members);

    // チャンネル一覧を表示する
    void displayChannels(const std::vector<wxString>& channels);

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

    // 認証ダイアログを表示する
    int showModalAuthDlg(void);

    // チャンネル名指定用ダイアログを表示する
    int showModalChannelDlg(void);

    // 認証中止ダイアログを表示する
    int showModalAuthCancelDlg(void);

    // 認証中止ダイアログを消す
    void clearAuthCancelDlg(void);

    // ユーザ名をwxStringで取得する
    wxString getDlgUserNameAsString(void) const;

    // パスワードをwxStringで取得する
    wxString getDlgPasswordAsString(void) const;

    // チャンネル名を取得する
    wxString getDlgChannelNameAsString(void) const;

};

