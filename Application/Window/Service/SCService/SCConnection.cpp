#include "SCConnection.hpp"
#include "SCEventFactory.hpp"

using namespace std;

namespace CornStarch
{
;
namespace StarChat
{
;

CSCConnection::CSCConnection(void) :
        m_getStreamTask(NULL), m_authTask(NULL)
{
}

CSCConnection::~CSCConnection(void)
{
    disconnect();
}

// 切断します
void CSCConnection::disconnect()
{
    if (m_getStreamTask != NULL){
        if (m_getStreamTask->IsRunning()){
            m_getStreamTask->Delete();
            delete m_getStreamTask;

        } else{
            delete m_getStreamTask;
        }
        m_getStreamTask = NULL;
    }
}

///////////////////////////////////////////////////////////////////////////

// 初期化を行う
void CSCConnection::init(int connectionId, wxEvtHandler* handler)
{
    m_connectionId = connectionId;
    m_handler = handler;
}

// メッセージを投稿するタスク(別スレッド)を開始する
void CSCConnection::startPostMessageTask(const IUser* user,
        const wxString& message, const wxString& channel)
{
    CSCPostMessageTask* postMessageTask = new CSCPostMessageTask();
    postMessageTask->init(this, user->getBasic());
    postMessageTask->setChannel(channel);
    postMessageTask->setMessage(message);

    // 別スレッドでの開始
    startThread(postMessageTask);
}

// チャンネルのメッセージを取得するタスク(別スレッド)を開始する
void CSCConnection::startGetMessageTask(const IUser* user,
        const wxString& channel)
{
    if (channel != ""){
        CSCGetMessageTask* getMessageTask = new CSCGetMessageTask();
        getMessageTask->init(this, user->getBasic());
        getMessageTask->setChannel(channel);
        // 別スレッドでの開始
        startThread(getMessageTask);
    }
}

// チャンネルのメンバーを取得するタスク(別スレッド)を開始する
void CSCConnection::startGetMemberTask(const IUser* user,
        const wxString& channel)
{
    CSCGetMemberTask* getMemberTask = new CSCGetMemberTask();
    getMemberTask->init(this, user->getBasic());
    getMemberTask->setChannel(channel);
    // 別スレッドでの開始
    startThread(getMemberTask);
}

// ユーザの所属するチャンネル一覧を取得するタスク(別スレッド)を開始する
void CSCConnection::startGetChannelTask(const IUser* user)
{

    CSCGetChannelTask* getChannelTask = new CSCGetChannelTask();
    getChannelTask->init(this, user->getBasic());
    getChannelTask->setUserName(user->getUserName());
    // 別スレッドでの開始
    startThread(getChannelTask);
}

// チャンネルから離脱するタスク(別スレッド)を開始する
void CSCConnection::startPartTask(const IUser* user, const wxString& channel)
{
    CSCPartChannelTask* partChannelTask = new CSCPartChannelTask();
    partChannelTask->init(this, user->getBasic());
    partChannelTask->setUserName(user->getUserName());
    partChannelTask->setChannel(channel);

    // 別スレッドでの開始
    startThread(partChannelTask);
}

// チャンネルに参加するタスク(別スレッド)を開始する
void CSCConnection::startJoinTask(const IUser* user, const wxString& channel)
{

    CSCJoinChannelTask* joinChannelTask = new CSCJoinChannelTask();
    joinChannelTask->init(this, user->getBasic());
    joinChannelTask->setUserName(user->getUserName());
    joinChannelTask->setChannel(channel);
    // 別スレッドでの開始
    startThread(joinChannelTask);
}

// メンバーの情報を取得するタスク(別スレッド)を開始する
void CSCConnection::startGetMemberInfoTask(const IUser* user,
        const wxString& name)
{

    CSCGetMemberInfoTask* getInfoTask = new CSCGetMemberInfoTask();
    getInfoTask->init(this, user->getBasic());
    getInfoTask->setUsername(name);
    // 別スレッドでの開始
    startThread(getInfoTask);
}

// ニックネームを変更するタスク(別スレッド)を開始する
void CSCConnection::startNickChangeTask(const IUser* user, const wxString& nick)
{
    CSCNickChangeTask* changeNickTask = new CSCNickChangeTask();
    changeNickTask->init(this, user->getBasic());
    changeNickTask->setNick(nick);
    changeNickTask->setName(user->getUserName());
    // 別スレッドでの開始
    startThread(changeNickTask);
}

// トピックを変更するタスク(別スレッド)を開始する
void CSCConnection::startChangeTopicTask(const IUser* user,
        const wxString& topic)
{
    CSCTopicChangeTask* changeTopicTask = new CSCTopicChangeTask();
    changeTopicTask->init(this, user->getBasic());
    changeTopicTask->setTopic(topic);
    changeTopicTask->setChannel(user->getChannelString());
    // 別スレッドでの開始
    startThread(changeTopicTask);
}

// ユーザが正規の人かどうか判断するタスク(別スレッド)を開始する
void CSCConnection::startAuthTask(const IUser* user)
{
    // 初期化
    m_authTask = new CSCAuthTask();
    m_authTask->init(this, user->getBasic());
    m_authTask->setUserName(user->getUserName());
    // 別スレッドでの開始
    startThread(m_authTask);
    m_user = user;
}

// ストリーム通信タスク(別スレッド)を開始
void CSCConnection::startStreamTask(const IUser* user)
{
    // 既に実行中だったら
    if (m_getStreamTask != NULL){
        return;
    }

    // ストリームの初期化
    m_getStreamTask = new CSCGetStreamTask();
    m_getStreamTask->init(this, user->getBasic());
    m_getStreamTask->setUserName(user->getUserName());
    // 別スレッドでの実行
    startThread(m_getStreamTask);
}

// ホストを取得
wxString CSCConnection::getHost(void) const
{
    return m_host;
}

// ホストを設定
void CSCConnection::setHost(const wxString& host)
{
    m_host = host;
}

///////////////////////////////////////////////////////////////////////////

// 別スレッドでタスクを開始する
void CSCConnection::startThread(CSCTask* task)
{
    task->setHost(getHost());
    task->setPort(getPort());
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

// メッセージ取得
void CSCConnection::onMessageReceived(CMessageData* message)
{
    CSCMessageData* scMessage = dynamic_cast<CSCMessageData*>(message);
    CSCEventFactory factory;
    CConnectionEventBase* event = factory.Create(*scMessage);
    if (event != NULL){
        invokeEvent(event);
    }
}
void CSCConnection::invokeEvent(CConnectionEventBase* event)
{
    event->setConnectionId(m_connectionId);
    wxQueueEvent(m_handler, event);
}
// 切断時
void CSCConnection::onDisconnected()
{
    CDisconnectEvent* event = new CDisconnectEvent();
    event->SetEventType(myEVT_THREAD_DISCONNECT); // イベントの種類をセット
    invokeEvent(event);
}
// 接続開始時
void CSCConnection::onConnected()
{
    CAuthEvent* event = new CAuthEvent();
    event->setAuthResult(true); // 値取得
    event->SetEventType(myEVT_THREAD_GET_PING); // イベントの種類をセット
    invokeEvent(event);

}
//　接続失敗時
void CSCConnection::onConnectionFailed()
{
    CAuthEvent* event = new CAuthEvent();
    event->setAuthResult(false);
    event->SetEventType(myEVT_THREAD_GET_PING); // イベントの種類をセット
    invokeEvent(event);

}
// サービスのステータスを調べます。
void CSCConnection::onCheckServiceStatus()
{
    CSCAuthTask *task = new CSCAuthTask();
    task->init(this,m_user->getBasic());
    task->setPing(true);
    task->setUserName(m_user->getUserName());
    // 別スレッドでの開始
    startThread(task);
}
// ポートを設定
void CSCConnection::setPort(int port)
{
    m_port = port;
}
// ポートを取得
int CSCConnection::getPort() const
{
    return m_port;
}
}
}
