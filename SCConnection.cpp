#include "SCConnection.hpp"

using namespace std;

namespace CornStarch
{;
namespace StarChat
{;

CSCConnection::CSCConnection(void) :
		m_getStreamTask(NULL), m_authTask(NULL)
{
}

CSCConnection::~CSCConnection(void)
{
	if (m_getStreamTask != NULL){
		if (m_getStreamTask->IsRunning()){
			m_getStreamTask->Delete();
		} else{
			delete m_getStreamTask;
		}
	}
}

///////////////////////////////////////////////////////////////////////////

// 初期化を行う
void CSCConnection::init(int connectionId, wxEvtHandler* handler)
{
	m_connetionId = connectionId;
	m_handler = handler;
}

// メッセージを投稿するタスク(別スレッド)を開始する
void CSCConnection::startPostMessageTask(const IUser* user,
        const wxString& message, const wxString& channel)
{
	CSCPostMessageTask* postMessageTask = new CSCPostMessageTask();
	postMessageTask->init(m_connetionId, m_handler, channel, user->getBasic());
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
		getMessageTask->init(m_connetionId, m_handler, channel,
		        user->getBasic());

		// 別スレッドでの開始
		startThread(getMessageTask);
	}
}

// チャンネルのメンバーを取得するタスク(別スレッド)を開始する
void CSCConnection::startGetMemberTask(const IUser* user,
        const wxString& channel)
{
	CSCGetMemberTask* getMemberTask = new CSCGetMemberTask();
	getMemberTask->init(m_connetionId, m_handler, channel, user->getBasic());

	// 別スレッドでの開始
	startThread(getMemberTask);
}

// ユーザの所属するチャンネル一覧を取得するタスク(別スレッド)を開始する
void CSCConnection::startGetChannelTask(const IUser* user)
{

	CSCGetChannelTask* getChannelTask = new CSCGetChannelTask();
	getChannelTask->init(m_connetionId, m_handler, user->getUserName(),
	        user->getBasic());

	// 別スレッドでの開始
	startThread(getChannelTask);
}

// チャンネルから離脱するタスク(別スレッド)を開始する
void CSCConnection::startPartTask(const IUser* user, const wxString& channel)
{

	CSCPartChannelTask* partChannelTask = new CSCPartChannelTask();
	partChannelTask->init(m_connetionId, m_handler, user->getUserName(),
	        channel, user->getBasic());

	// 別スレッドでの開始
	startThread(partChannelTask);
}

// チャンネルに参加するタスク(別スレッド)を開始する
void CSCConnection::startJoinTask(const IUser* user, const wxString& channel)
{

	CSCJoinChannelTask* joinChannelTask = new CSCJoinChannelTask();
	joinChannelTask->init(m_connetionId, m_handler, user->getUserName(),
	        channel, user->getBasic());

	// 別スレッドでの開始
	startThread(joinChannelTask);
}

// メンバーの情報を取得するタスク(別スレッド)を開始する
void CSCConnection::startGetMemberInfoTask(const IUser* user,
        const wxString& name)
{

	CSCGetMemberInfoTask* getInfoTask = new CSCGetMemberInfoTask();
	getInfoTask->init(m_connetionId, m_handler, name, user->getBasic());

	// 別スレッドでの開始
	startThread(getInfoTask);
}

// ニックネームを変更するタスク(別スレッド)を開始する
void CSCConnection::startNickChangeTask(const IUser* user, const wxString& nick)
{
	CSCNickChangeTask* changeNickTask = new CSCNickChangeTask();
	changeNickTask->init(m_connetionId, m_handler, nick, user->getUserName(),
	        user->getBasic());

	// 別スレッドでの開始
	startThread(changeNickTask);
}

// トピックを変更するタスク(別スレッド)を開始する
void CSCConnection::startChangeTopicTask(const IUser* user,
        const wxString& topic)
{
	CSCTopicChangeTask* changeTopicTask = new CSCTopicChangeTask();
	changeTopicTask->init(m_connetionId, m_handler, user->getChannelString(),
	        topic, user->getBasic());

	// 別スレッドでの開始
	startThread(changeTopicTask);
}

// ユーザが正規の人かどうか判断するタスク(別スレッド)を開始する
void CSCConnection::startAuthTask(const IUser* user)
{
	// 初期化
	m_authTask = new CSCAuthTask();
	m_authTask->init(m_connetionId, m_handler, user->getUserName(),
	        user->getBasic());

	// 別スレッドでの開始
	startThread(m_authTask);
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
	m_getStreamTask->init(m_connetionId, m_handler, user->getUserName(),
	        user->getBasic());

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
	task->setHost(getHost());
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

}
}