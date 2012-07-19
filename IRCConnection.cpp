/*
 * IRCConnection.cpp
 *
 *  Created on: 2012/07/13
 */

#include "SCTask.hpp"
#include "IRCConnection.h"
#include "JoinEvent.hpp"
#include "GetChannelEvent.hpp"
#include "PartStreamEvent.hpp"
#include "MsgStreamEvent.hpp"
#include "StreamData.hpp"
#include "GetMessageEvent.hpp"
#include "GetMemberInfoEvent.hpp"

// イベントの宣言
wxDECLARE_EVENT(myEVT_THREAD_PUT_JOIN, CJoinEvent);
wxDECLARE_EVENT(myEVT_THREAD_GET_CHANNEL, CGetChannelEvent);
wxDECLARE_EVENT(myEVT_THREAD_POST_MESSAGE, wxThreadEvent);
wxDECLARE_EVENT(myEVT_THREAD_GET_MESSAGE, CGetMessageEvent);
wxDECLARE_EVENT(myEVT_THREAD_GET_MEMBER_INFO, CGetMemberInfoEvent);
namespace CornStarch
{
namespace IRC
{
CIRCConnection::CIRCConnection()
{

}

CIRCConnection::~CIRCConnection()
{
}

// 初期化を行う
void CIRCConnection::init(wxEvtHandler* handler)
{
	m_client = new CIRCClient();
	m_client->init();
	m_client->start(handler);
}

// メッセージを投稿するタスク(別スレッド)を開始する
void CIRCConnection::startPostMessageTask(wxEvtHandler* handler,
		const wxString& message, const wxString& channel, const wxString& basic)
{
	m_client->sendMessage(channel, message);
	wxThreadEvent* event = new wxThreadEvent();
	event->SetEventType(myEVT_THREAD_POST_MESSAGE);
	wxQueueEvent(handler, event);

}

// チャンネルのメッセージを取得するタスク(別スレッド)を開始する
void CIRCConnection::startGetMessageTask(wxEvtHandler* handler,
		const wxString& channel, const wxString& basic)
{
	time_t timer = time(NULL);

	vector<CMessageData*> result;
	result.push_back(new CMessageData(1, "", "Connect", channel, timer));
	CGetMessageEvent* event = new CGetMessageEvent();
	event->setMessages(result); // 値取得
	event->SetEventType(myEVT_THREAD_GET_MESSAGE); // イベントの種類をセット
	wxQueueEvent(handler, event);

}

// チャンネルのメンバーを取得するタスク(別スレッド)を開始する
void CIRCConnection::startGetMemberTask(wxEvtHandler* handler,
		const wxString& channel, const wxString& basic)
{
	m_client->getNamesAsync(channel);
}

// ユーザの所属するチャンネル一覧を取得するタスク(別スレッド)を開始する
void CIRCConnection::startGetChannelTask(wxEvtHandler* handler,
		const wxString& userName, const wxString& basic)
{
	CGetChannelEvent* event = new CGetChannelEvent();

	vector<CChannelData*> channels;
	int size = m_channels.size();
	for (int i = 0; i < size; i++)
	{
		CChannelData* channel = new CChannelData();
		channel->m_name = m_channels[i]->m_name;
		channel->m_topic = m_channels[i]->m_topic;
		channels.push_back(channel);
	}
	event->setChannels(channels); // 値取得
	event->SetEventType(myEVT_THREAD_GET_CHANNEL); // イベントの種類をセット
	wxQueueEvent(handler, event);
}

// チャンネルから離脱するタスク(別スレッド)を開始する
void CIRCConnection::startPartTask(wxEvtHandler* handler,
		const wxString& channel, const wxString& userName,
		const wxString& basic)
{
	m_client->part(channel);

	vector<CChannelData*>::iterator it = m_channels.begin();
	while (it != m_channels.end())
	{
		wxString channelName =(*it)->m_name ;
		if (channelName== channel)
		{
			m_channels.erase(it);
			break;
		}
		++it;
	}

	CJoinEvent* event = new CJoinEvent();
	event->SetEventType(myEVT_THREAD_PUT_JOIN); // イベントの種類をセット
	event->SetString(channel); // 新チャンネル名
	wxQueueEvent(handler, event);
}

// チャンネルに参加するタスク(別スレッド)を開始する
void CIRCConnection::startJoinTask(wxEvtHandler* handler,
		const wxString& channel, const wxString& userName,
		const wxString& basic)
{
	m_client->join(channel);
	m_client->getTopicAsync(channel);
	CChannelData *channelData = new CChannelData();
	channelData->m_name = channel;
	channelData->m_topic = "";
	m_channels.push_back(channelData);

	CJoinEvent* event = new CJoinEvent();
	event->SetEventType(myEVT_THREAD_PUT_JOIN); // イベントの種類をセット
	event->SetString(channel); // 新チャンネル名
	wxQueueEvent(handler, event);
}

// メンバーの情報を取得するタスク(別スレッド)を開始する
void CIRCConnection::startGetMemberInfoTask(wxEvtHandler* handler,
		const wxString& userName, const wxString& basic)
{
	CGetMemberInfoEvent* event = new CGetMemberInfoEvent();
	CMemberData member(userName, userName);
	event->setMember(member); // 値取得
	event->SetEventType(myEVT_THREAD_GET_MEMBER_INFO); // イベントの種類をセット
	wxQueueEvent(handler, event);

}

// ユーザが正規の人かどうか判断するタスク(別スレッド)を開始する
void CIRCConnection::startAuthTask(wxEvtHandler* handler,
		const wxString& userName, const wxString& basic)
{
	// 初期化
//        m_authTask = new CAuthTask();
//        m_authTask->init(handler, userName, basic);
//        
//        // 別スレッドでの開始
//        startThread(m_authTask);
}

// ストリーム通信タスク(別スレッド)を開始
void CIRCConnection::startStreamTask(wxEvtHandler* handler,
		const wxString& userName, const wxString& basic)
{

//        // 既に実行中だったら
//        if (m_getStreamTask != NULL){
//            
//            return;
//        }
//        
//        // ストリームの初期化
//        m_getStreamTask = new CGetStreamTask();
//        m_getStreamTask->init(handler, userName, basic);
//        
//        // 別スレッドでの実行
//        startThread(m_getStreamTask);
}

// 認証用タスク(別スレッド)を削除する
void CIRCConnection::deleteAuthTask(void)
{
//        m_authTask->Delete();
}

///////////////////////////////////////////////////////////////////////////

// 別スレッドでタスクを開始する
//    void CIRCConnection::startThread(CSCTask* task)
//    {
// 別スレッドを作る
//        if (task->Create() != wxTHREAD_NO_ERROR){
//            delete task;
//            task = NULL;
//            return;
//        }
//        
//        // 別スレッドを走らせる
//        if (task->Run() != wxTHREAD_NO_ERROR){
//            delete task;
//            task = NULL;
//            return;
//        }
//    }
}
} /* namespace CornStarch */
