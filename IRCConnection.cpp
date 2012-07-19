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
void CIRCConnection::init(int connectionId,wxEvtHandler* handler)
{
	m_connectionId = connectionId;
	m_handler = handler;
	m_client = new CIRCClient();
	m_client->init(connectionId);
	m_client->start(handler);
}

// メッセージを投稿するタスク(別スレッド)を開始する
void CIRCConnection::startPostMessageTask(const IUser* user,
		const wxString& message, const wxString& channel)
{
	m_client->sendMessage(channel, message);
	CConnectionEventBase* event = new CConnectionEventBase();
	event->SetEventType(myEVT_THREAD_POST_MESSAGE);
	event->setConnectionId(m_connectionId);
	wxQueueEvent(m_handler, event);

}

// チャンネルのメッセージを取得するタスク(別スレッド)を開始する
void CIRCConnection::startGetMessageTask(const IUser* user,
		const wxString& channel)
{
	time_t timer = time(NULL);

	vector<CMessageData*> result;
	result.push_back(new CMessageData(1, "", "Connect", channel, timer));
	CGetMessageEvent* event = new CGetMessageEvent();
	event->setMessages(result); // 値取得
	event->SetEventType(myEVT_THREAD_GET_MESSAGE); // イベントの種類をセット
	event->setConnectionId(m_connectionId);
	wxQueueEvent(m_handler, event);

}

// チャンネルのメンバーを取得するタスク(別スレッド)を開始する
void CIRCConnection::startGetMemberTask(const IUser* user,
		const wxString& channel)
{
	m_client->getNamesAsync(channel);
}

// ユーザの所属するチャンネル一覧を取得するタスク(別スレッド)を開始する
void CIRCConnection::startGetChannelTask(const IUser* user)
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
	event->setConnectionId(m_connectionId);
	wxQueueEvent(m_handler, event);
}

// チャンネルから離脱するタスク(別スレッド)を開始する
void CIRCConnection::startPartTask(const IUser* user,
		const wxString& channel)
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
	event->setConnectionId(m_connectionId);
	wxQueueEvent(m_handler, event);
}

// チャンネルに参加するタスク(別スレッド)を開始する
void CIRCConnection::startJoinTask(const IUser* user,
		const wxString& channel)
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
	event->setConnectionId(m_connectionId);
	wxQueueEvent(m_handler, event);
}

// メンバーの情報を取得するタスク(別スレッド)を開始する
void CIRCConnection::startGetMemberInfoTask(const IUser* user,
		const wxString& userName)
{
	CGetMemberInfoEvent* event = new CGetMemberInfoEvent();
	CMemberData member(userName, userName);
	event->setMember(member); // 値取得
	event->SetEventType(myEVT_THREAD_GET_MEMBER_INFO); // イベントの種類をセット
	event->setConnectionId(m_connectionId);
	wxQueueEvent(m_handler, event);

}

// ユーザが正規の人かどうか判断するタスク(別スレッド)を開始する
void CIRCConnection::startAuthTask(const IUser* user)
{
	// 初期化
//        m_authTask = new CAuthTask();
//        m_authTask->init(handler, userName, basic);
//        
//        // 別スレッドでの開始
//        startThread(m_authTask);
}

// ストリーム通信タスク(別スレッド)を開始
void CIRCConnection::startStreamTask(const IUser* user)
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
{}

}
} /* namespace CornStarch */
