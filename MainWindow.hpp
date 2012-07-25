#pragma once
#include "MainView.hpp"
#include "MainLogHolder.hpp"
#include "ChatServiceBase.hpp"
#include "vector"
#include "PartEvent.hpp"
#include "ServiceSerializer.hpp"

// ビューコントローラとなるウィンドウクラス
class CMainWindow: public wxFrame
{
private:

	// CornStarch全般
	CMainView* m_view; // ビューの挙動を管理
	CMainLogHolder* m_logHolder; // チャットのログを保持
	int m_serverIdLog;
	int m_currentServiceId;
	// 通信要素
	map<int,CChatServiceBase*> m_services; // スターチャットのコンテンツを管理
	void addNewService(CChatServiceBase* service);

    // サービスのシリアライズ
    CServiceSerializer* m_serialize;

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
	void updateAllView(int serviceId, const wxString& channel);

	// メッセージ画面を更新する(Modelがある場合)
	void updateMessageView(int serviceId, const wxString& channel);

	// メンバー画面を更新する(Modelがある場合)
	void updateMemberView(int serviceId, const wxString& channel);

	// チャンネル画面とタイトルバーを更新する(Modelがある場合)
	void updateChannelView(int serviceId, const wxString& channel);

	// タイトルバーにタイトルを表示する
	void displayTitle(const wxString& channel, const wxString& topic);

	CChatServiceBase* getService(int serviceId);
private:
	// メニュー系

	// 終了
	void onQuit(wxCommandEvent& event);

	// ユーザ登録(SC)
	void onSCRegister(wxCommandEvent& event);

	// ユーザ登録(IRC)
	void onIRCRegister(wxCommandEvent& event);

	// ログアウトメニュー
	void onLogout(wxCommandEvent& event);

	// チャンネルに参加メニュー
	void onJoin(wxCommandEvent& event);

	// チャンネルから離脱メニュー
	void onPart(wxCommandEvent& event);

	// 表示を更新
	void onUpdateDisplay(wxCommandEvent& event);

	// ニックネーム変更
	void onNickChange(wxCommandEvent& event);

	// トピック変更
	void onChangeTopic(wxCommandEvent& event);

private:
	// 画面系

	// 投稿ペインでEnterキーを押下
	void onEnter(wxCommandEvent& event);

    // メンバーがダブルクリック
    void onMemberSelected(wxCommandEvent& event);

	// チャンネル選択時
	void onChannelSelected(CChannelSelectEvent& event);

private:
	// 通信系

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
	void onPartChannel(CPartEvent& event);

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
