#pragma once
#include "HttpClient.hpp"

// スターチャット接続用クライアント
class CSCClient : public CHttpClient
{
public:
    CSCClient(void);
    ~CSCClient(void);

    // pingを送るリクエストを投げる
    void sendPingRequest(const wxString& userName, const wxString& basic);

    // メッセージを投稿するリクエストを投げる
    void postMessageRequest(const wxString& body, const wxString& channel,
        const wxString& basic);

    // その人のチャンネルをJSON形式で取得するリクエストを投げる
    void sendGetChannelsRequest(const wxString& userName, const wxString& basic);

    // チャンネルのメッセージをJSON形式で取得するリクエストを投げる
    void sendGetMessagesRequest(const wxString& channel, const wxString& basic);

    // チャンネルのメンバをJSON形式で取得するリクエストを投げる
    void sendGetMembersRequest(const wxString& channel, const wxString& basic);

    // チャンネルに参加するリクエストを投げる
    void sendJoinRequest(const wxString& channel, const wxString& userName,
        const wxString& basic);

    // チャンネルから抜けるリクエストを投げる
    void sendPartRequest(const wxString& channel, const wxString& userName,
        const wxString& basic);

    // メンバーの情報をJSON形式で取得するリクエストを投げる
    void sendGetMemInfoRequest(const wxString& userName, const wxString& basic);

    // ストリームを取得するリクエストを送信する
    void sendGetStreamRequest(const wxString& userName, const wxString& basic);

    // ストリームをJSON形式で取得する
    std::string getStreamJson(void);

private:

    // ストリームを受信する
    int recvStream(long waitTimeUsec = 1000);

    // ストリーム形式が正規のものか確認する
    bool isCorrectStream(void) const;

private:

    // pingを送るAPIを叩く
    void sendPingApi(const wxString& userName);

    // メッセージ投稿するAPIを叩く
    void sendPostMstApi(const wxString& channel);

    // チャンネル一覧取得のAPIを叩く
    void sendGetCnApi(const wxString& userName);

    // メンバー一覧取得のAPIを叩く
    void sendGetMemApi(const wxString& channel);

    // メッセージ一覧取得のAPIを叩く
    void sendGetMsgApi(const wxString& channel);

    // チャンネル参加APIを叩く
    void sendJoinApi(const wxString& channel, const wxString& userName);

    // チャンネル離脱APIを叩く
    void sendPartApi(const wxString& channel, const wxString& userName);

    // メンバー情報取得APIを叩く
    void sendGetMemInfoApi(const wxString& userName);

    // ストリーム取得用APIを叩く
    void sendStreamApi(const wxString& userName);

};

