#pragma once
#include "SCPostMessageTask.hpp"
#include "SCGetChannelTask.hpp"
#include "SCGetMessageTask.hpp"
#include "SCGetMemberTask.hpp"
#include "SCAuthTask.hpp"
#include "SCJoinChannelTask.hpp"
#include "SCPartChannelTask.hpp"
#include "SCGetMemberInfoTask.hpp"
#include "SCGetStreamTask.hpp"

// 通信部分を管理(通信結果をイベントとして返す)
class CSCConnection
{
private:

    CSCAuthTask* m_authTask; // ユーザ認証用タスク
    CSCGetStreamTask* m_getStreamTask; // ストリーム受信タスク

public:

    CSCConnection(void);
    ~CSCConnection(void);

    // 初期化を行う
    void init(void);

    // メッセージを投稿するタスク(別スレッド)を開始する
    void startPostMessageTask(wxEvtHandler* handler, const wxString& message,
        const wxString& channel, const wxString& basic);

        // チャンネルのメッセージを取得するタスク(別スレッド)を開始する
    void startGetMessageTask(wxEvtHandler* handler, const wxString& channel,
        const wxString& basic);

    // チャンネルのメンバーを取得するタスク(別スレッド)を開始する
    void startGetMemberTask(wxEvtHandler* handler, const wxString& channel,
        const wxString& basic);

    // ユーザの所属するチャンネル一覧を取得するタスク(別スレッド)を開始する
    void startGetChannelTask(wxEvtHandler* handler, const wxString& userName,
        const wxString& basic);

    // チャンネルから離脱するタスク(別スレッド)を開始する
    void startPartTask(wxEvtHandler* handler, const wxString& channel, 
        const wxString& userName, const wxString& basic);

    // チャンネルに参加するタスク(別スレッド)を開始する
    void startJoinTask(wxEvtHandler* handler, const wxString& channel,
        const wxString& userName, const wxString& basic);

    // メンバーの情報を取得するタスク(別スレッド)を開始する
    void startGetMemberInfoTask(wxEvtHandler* handler,
        const wxString& userName, const wxString& basic);

    // ユーザが正規の人かどうか判断するタスク(別スレッド)を開始する
    void startAuthTask(wxEvtHandler* handler, const wxString& userName,
        const wxString& basic);

    // ストリーム通信タスク(別スレッド)を開始
    void startStreamTask(wxEvtHandler* handler, const wxString& userName,
        const wxString& basic);

    // 認証用タスク(別スレッド)を削除する
    void deleteAuthTask(void);

private:

    // 別スレッドでタスクを開始する
    void startThread(CSCTask* task);

};

