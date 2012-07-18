#pragma once
#include "SCConnection.hpp"
#include "SCChannelHolder.hpp"
#include "SCUser.hpp"
#include "SCNickTable.hpp"
#include "MyPersistent.hpp"

// StarChatのModelコンテンツを扱うクラス
class CSCContents
{
private:
    // イベントハンドラ
    wxEvtHandler* m_handler;

    // StarChatのデータ部
    CSCConnection* m_connect; // 通信を司るクラス
    CSCChannelHolder* m_channel; // チャンネル情報を保持
    CSCUser* m_user; // ユーザ情報
    CSCNickTable* m_nickTable; // ニックネームテーブル

    // 汎用クラス
    CMyPersistent* m_persist; // 永続化を扱う

public:
    CSCContents(void);
    ~CSCContents(void);

    // 初期化を行う
    void init(wxEvtHandler* handler);

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
    CSCNickTable getNickTable(void) const;

    // ユーザが呼ばれたか
    bool isUserCalled(const wxString& message);

    // メンバーのニックネームを取得
    wxString getMemberNick(const wxString& member);

    // チャンネルのトピックを取得
    wxString getTopic(const wxString& channel);

    // このクライアントから投稿されたメッセージか
    bool isPostedThisClient(const CMessageData& message);



    // 
    void onUpdateMessageView(const wxString& channel);

    // 
    void onUpdateMemberView(const wxString& channel);

    // 
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
};

