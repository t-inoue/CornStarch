#pragma once
#include "SCConnection.hpp"
#include "ChannelHolder.hpp"
#include "SCUser.hpp"
#include "NickTable.hpp"
#include "MyPersistent.hpp"
#include "IUser.h"
#include "IConnection.hpp"

// 通信のModelコンテンツを扱うクラス
class CConnectionContents
{
protected:
    // イベントハンドラ
    wxEvtHandler* m_handler;

    // StarChatのデータ部
    IConnection* m_connect; // 通信を司るクラス
    CChannelHolder* m_channel; // チャンネル情報を保持
    IUser* m_user; // ユーザ情報
    CNickTable* m_nickTable; // ニックネームテーブル

    // 汎用クラス
    CMyPersistent* m_persist; // 永続化を扱う
    // 名前
    wxString m_name;
    // ID
    int m_id;

public:
    CConnectionContents(void);
    virtual ~CConnectionContents(void);

    // IDを取得
	int getId() const
	{
		return m_id;
	}
	// IDを設定
	void setId(int id)
	{
		m_id = id;
	}

	// 名前を取得
	wxString getName() const
	{
		return m_name;
	}

	// 名前を設定
	void setName(wxString name)
	{
		m_name = name;
	}


    // 初期化を行う
    virtual void init(wxEvtHandler* handler);

    // ユーザがログインしているか
    bool isUserLogin(void) const;

    // ユーザ登録を行った際のデータ更新
    void registerUser(const wxString& userName, const wxString& pass);

    // ログアウト時
    void logout(void);

    // チャンネルに参加を行う際
    void joinChannel(const wxString& channel);

    // チャンネルから離脱する際
    void partChannel(const wxString& channel);

    // 再接続を行う
    void reconnect(void);

    // 各チャンネルの情報を破棄
    void clearChannels(void);

    // ニックネームテーブルを破棄
    void clearNickTable(void);

    // 現在のチャンネル名を取得
    wxString getCurrentChannel(void) const;

    // メッセージを生成
    CMessageData generateMessage(const wxString& body);

    // ニックネームを取得
    wxString getNickName(void) const;

    // メッセージを投稿した際
    void postMessage(const CMessageData& message);

    // チャンネルを選択した際
    void selectChannel(const wxString& channel);

    // チャンネル一覧を取得
    std::vector<wxString> getChannels(void) const;

    // メッセージ一覧を取得
    std::vector<CMessageData*> getMessages(const wxString& channel) const;

    // メンバー一覧を取得
    std::vector<CMemberData*> getMembers(const wxString& channel) const;

    // ニックネームテーブルを取得
    CNickTable getNickTable(void) const;

    // ユーザが呼ばれたか
    bool isUserCalled(const wxString& message);

    // メンバーのニックネームを取得
    wxString getMemberNick(const wxString& member);

    // チャンネルのトピックを取得
    wxString getTopic(const wxString& channel);

    // このクライアントから投稿されたメッセージか
    bool isPostedThisClient(const CMessageData& message);

    // メッセージ表示を行う際
    void onUpdateMessageView(const wxString& channel);

    // メンバー表示を行う際
    void onUpdateMemberView(const wxString& channel);

    // チャンネル表示を行う際
    void onUpdateChannelView(void);

    /////////////////////////////////////////

    // 認証が成功した場合
    void onAuthSucceeed(void);

    // メッセージ一覧を取得した場合
    void onGetMessages(const std::vector<CMessageData*>& messages);

    // メンバー一覧を取得した場合
    void onGetMembers(const std::vector<CMemberData*>& members);

    // チャンネル一覧を取得した場合
    void onGetChannels(const std::vector<CChannelData*>& channels);

    // チャンネル参加成功時
    void onJoinChannel(const wxString& channel);

    // チャンネル離脱成功時
    void onPartChannel(const wxString& channel);

    // メンバー情報を取得した場合
    void onGetMemberStatus(const CMemberData& member);

    // メッセージストリームを取得した場合
    void onGetMessageStream(const CMessageData& message);

    // チャンネル参加ストリームを受信
    void onGetJoinStream(const wxString& channel, const wxString& name);

    // チャンネル離脱ストリームを受信
    void onGetPartStream(const wxString& channel, const wxString& name);

    // チャンネル情報更新ストリームを受信
    void onGetChannelStream(const CChannelData& channel);

    // ユーザ情報更新ストリームの受信
    void onGetUserStream(const CMemberData& member);
}

;

