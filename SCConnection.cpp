#include "SCConnection.hpp"

using namespace std;

CSCConnection::CSCConnection(void) : m_getStreamTask(NULL), m_authTask(NULL)
{
}


CSCConnection::~CSCConnection(void)
{
    if (m_getStreamTask != NULL){
        if (m_getStreamTask->IsRunning()){
            m_getStreamTask->Delete();
        } else {
            delete m_getStreamTask;
        }
    }
}


///////////////////////////////////////////////////////////////////////////


    // 初期化を行う
void CSCConnection::init(void)
{
}

    // メッセージを投稿するタスク(別スレッド)を開始する
void CSCConnection::startPostMessageTask(wxEvtHandler* handler, 
    const wxString& message, const wxString& channel, const wxString& basic)
{
    CSCPostMessageTask* postMessageTask = new CSCPostMessageTask();
    postMessageTask->init(handler, channel, basic);
    postMessageTask->setMessage(message);

    // 別スレッドでの開始
    startThread(postMessageTask);
}

    // チャンネルのメッセージを取得するタスク(別スレッド)を開始する
void CSCConnection::startGetMessageTask(wxEvtHandler* handler, const wxString& channel,
    const wxString& basic)
{
    CSCGetMessageTask* getMessageTask = new CSCGetMessageTask();
    getMessageTask->init(handler, channel, basic);

    // 別スレッドでの開始
    startThread(getMessageTask);
}

    // チャンネルのメンバーを取得するタスク(別スレッド)を開始する
void CSCConnection::startGetMemberTask(wxEvtHandler* handler, const wxString& channel,
    const wxString& basic)
{
    CSCGetMemberTask* getMemberTask = new CSCGetMemberTask();
    getMemberTask->init(handler, channel, basic);

    // 別スレッドでの開始
    startThread(getMemberTask);
}

    // ユーザの所属するチャンネル一覧を取得するタスク(別スレッド)を開始する
void CSCConnection::startGetChannelTask(wxEvtHandler* handler, const wxString& userName,
    const wxString& basic)
{

    CSCGetChannelTask* getChannelTask = new CSCGetChannelTask();
    getChannelTask->init(handler, userName, basic);

    // 別スレッドでの開始
    startThread(getChannelTask);
}

    // チャンネルから離脱するタスク(別スレッド)を開始する
void CSCConnection::startPartTask(wxEvtHandler* handler, const wxString& channel,
    const wxString& userName, const wxString& basic)
{

    CSCPartChannelTask* partChannelTask = new CSCPartChannelTask();
    partChannelTask->init(handler, userName, channel, basic);

    // 別スレッドでの開始
    startThread(partChannelTask);
}

    // チャンネルに参加するタスク(別スレッド)を開始する
void CSCConnection::startJoinTask(wxEvtHandler* handler, const wxString& channel,
    const wxString& userName, const wxString& basic)
{

    CSCJoinChannelTask* joinChannelTask = new CSCJoinChannelTask();
    joinChannelTask->init(handler, userName, channel, basic);

    // 別スレッドでの開始
    startThread(joinChannelTask);
}

    // メンバーの情報を取得するタスク(別スレッド)を開始する
void CSCConnection::startGetMemberInfoTask(wxEvtHandler* handler,
    const wxString& userName, const wxString& basic)
{

    CSCGetMemberInfoTask* getInfoTask = new CSCGetMemberInfoTask();
    getInfoTask->init(handler, userName, basic);

    // 別スレッドでの開始
    startThread(getInfoTask);
}

    // ユーザが正規の人かどうか判断するタスク(別スレッド)を開始する
void CSCConnection::startAuthTask(wxEvtHandler* handler, const wxString& userName,
    const wxString& basic)
{
    // 初期化
    m_authTask = new CSCAuthTask();
    m_authTask->init(handler, userName, basic);

    // 別スレッドでの開始
    startThread(m_authTask);
}

    // ストリーム通信タスク(別スレッド)を開始
void CSCConnection::startStreamTask(wxEvtHandler* handler, const wxString& userName,
    const wxString& basic)
{
    // 既に実行中だったら
    if (m_getStreamTask != NULL){

        return;
    }

    // ストリームの初期化
    m_getStreamTask = new CSCGetStreamTask();
    m_getStreamTask->init(handler, userName, basic);

    // 別スレッドでの実行
    startThread(m_getStreamTask);
}

    // 認証用タスク(別スレッド)を削除する
void CSCConnection::deleteAuthTask(void)
{
    m_authTask->Delete();
}


///////////////////////////////////////////////////////////////////////////


    // 別スレッドでタスクを開始する
void CSCConnection::startThread(CSCTask* task)
{
    // 別スレッドを作る
    if (task->Create() != wxTHREAD_NO_ERROR){
        delete task;
        task = NULL;
        return;
    }

    // 別スレッドを走らせる
    if (task->Run() != wxTHREAD_NO_ERROR){
        delete task;
        task = NULL;
        return;
    }
}

