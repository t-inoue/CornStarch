#pragma once
#include "MainView.hpp"
#include "MainLogHolder.hpp"
#include "SCContents.hpp"

// ビューコントローラとなるウィンドウクラス
class CMainWindow : public wxFrame
{
private:

    // CornStarch全般
    CMainView* m_view; // ビューの挙動を管理
    CMainLogHolder* m_logHolder; // チャットのログを保持

    // StarChat
    CSCContents* m_contents; // スターチャットのコンテンツを管理

    // wxWindowイベントを処理させたいクラスに利用するマクロ
    DECLARE_EVENT_TABLE()

public:
    CMainWindow(void);
    ~CMainWindow(void);

    // 初期化を行う
    void init(void);

private:

    // 画面操作に関するイベントハンドラを設定する
    void initHandle(void);
    
    // Modelがあれば画面を更新する
    void updateAllView(const wxString& channel);

    // メッセージ画面を更新する(Modelがある場合)
    void updateMessageView(const wxString& channel);

    // メンバー画面を更新する(Modelがある場合)
    void updateMemberView(const wxString& channel);

    // チャンネル画面とタイトルバーを更新する(Modelがある場合)
    void updateChannelView(const wxString& channel);

    // タイトルバーにタイトルを表示する
    void displayTitle(const wxString& channel, const wxString& topic);

private: // メニュー系

    // 終了
    void onQuit(wxCommandEvent& event);

    // ユーザ登録
    void onRegister(wxCommandEvent& event);

    // ログアウトメニュー
    void onLogout(wxCommandEvent& event);

    // チャンネルに参加メニュー
    void onJoin(wxCommandEvent& event);

    // チャンネルから離脱メニュー
    void onPart(wxCommandEvent& event);

    // 表示を更新
    void onUpdateDisplay(wxCommandEvent& event);

private: // 画面系

    // サイズ変更
    void OnSize(wxSizeEvent& event);

    // 投稿ペインでEnterキーを押下
    void onEnter(wxCommandEvent& event);

    // チャンネル選択時
    void onChannel(wxCommandEvent& event);

private: // 通信系

    // メッセージ投稿終了時
    void onFinishPostMessage(wxThreadEvent& event);

    // 認証情報の受信時
    void onGetAuth(CAuthEvent& event);

    // メッセージ一覧受信時
    void onGetMessages(CGetMessageEvent& event);

    // メンバー一覧受信時
    void onGetMembers(CGetMemberEvent& event);

    // チャンネル一覧受信時
    void onGetChannels(CGetChannelEvent& event);

    // チャンネル参加時
    void onJoinChannel(CJoinEvent& event);

    // チャンネル離脱時
    void onPartChannel(wxThreadEvent& event);

    // メンバー情報の受信時
    void onGetMemberInfo(CGetMemberInfoEvent& event);

    // メッセージストリーム受信時
    void onMsgStream(CMsgStreamEvent& event);

    // チャンネル参加ストリーム受信時
    void onJoinStream(CJoinStreamEvent& event);

    // チャンネル離脱ストリーム受信時
    void onPartStream(CPartStreamEvent& event);

    // チャンネル更新ストリーム受信時
    void onChannelStream(CChannelStreamEvent& event);

    // ユーザ情報更新ストリーム受信時
    void onUserStream(CUserStreamEvent& event);

};
