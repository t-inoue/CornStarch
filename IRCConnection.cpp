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
#include "PartEvent.hpp"
#include "ChannelStreamEvent.hpp"
#include "UserStreamEvent.hpp"

// イベントの宣言
wxDECLARE_EVENT(myEVT_THREAD_PUT_JOIN, CJoinEvent);
wxDECLARE_EVENT(myEVT_THREAD_GET_CHANNEL, CGetChannelEvent);
wxDECLARE_EVENT(myEVT_THREAD_POST_MESSAGE, wxThreadEvent);
wxDECLARE_EVENT(myEVT_THREAD_GET_MESSAGE, CGetMessageEvent);
wxDECLARE_EVENT(myEVT_THREAD_GET_MEMBER_INFO, CGetMemberInfoEvent);
wxDECLARE_EVENT(myEVT_THREAD_DELETE_PART, CPartEvent);
wxDECLARE_EVENT(myEVT_THREAD_STREAM_CH_UPDATE, CChannelStreamEvent);
wxDECLARE_EVENT(myEVT_THREAD_STREAM_USER_UPDATE, CUserStreamEvent);
namespace CornStarch
{
namespace IRC
{
CIRCConnection::CIRCConnection()
{

}

CIRCConnection::~CIRCConnection()
{
	delete m_client;
	int size = (int) m_channels.size();
	for (int i = 0; i < size; i++){
		delete m_channels[i];
	}
}

// 初期化を行う
void CIRCConnection::init(int connectionId, wxEvtHandler* handler)
{
	m_connectionId = connectionId;
	m_handler = handler;
	m_client = new CIRCClient();
	m_client->init(connectionId);
	m_client->setPort("6667");

}

// メッセージを投稿するタスク(別スレッド)を開始する
void CIRCConnection::startPostMessageTask(const IUser* user,
		const wxString& message, const wxString& channel)
{
	m_client->sendMessage(channel, message);
	wxThreadEvent* event = new wxThreadEvent();
	event->SetEventType(myEVT_THREAD_POST_MESSAGE);
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
	for (int i = 0; i < size; i++){
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
void CIRCConnection::startPartTask(const IUser* user, const wxString& channel)
{
	m_client->part(channel);

	vector<CChannelData*>::iterator it = m_channels.begin();
	while (it != m_channels.end()){
		wxString channelName = (*it)->m_name;
		if (channelName == channel){
			m_channels.erase(it);
			break;
		}
		++it;
	}

	CPartEvent* event = new CPartEvent();
	event->SetEventType(myEVT_THREAD_DELETE_PART); // イベントの種類をセット
	event->SetString(channel);
	event->setConnectionId(m_connectionId);
	wxQueueEvent(m_handler, event);
}

// チャンネルに参加するタスク(別スレッド)を開始する
void CIRCConnection::startJoinTask(const IUser* user, const wxString& channel)
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
	m_client->start(m_handler, user->getUserName(), "");
	//Sample
	startJoinTask(user, "#cc");
}

// ストリーム通信タスク(別スレッド)を開始
void CIRCConnection::startStreamTask(const IUser* user)
{
}

// 認証用タスク(別スレッド)を削除する
void CIRCConnection::deleteAuthTask(void)
{
}
//override ニックネームを変更するタスク(別スレッド)を開始する
void CIRCConnection::startNickChangeTask(const IUser* user, const wxString& nick){
	m_client->changeNickname(nick);

	CMemberData member;
	member.m_name = wxString(user->getUserName());
	member.m_nick = wxString(nick);

	CUserStreamEvent* event = new CUserStreamEvent();
	event->SetEventType(myEVT_THREAD_STREAM_USER_UPDATE);
	event->setMember(member);
	wxQueueEvent(m_handler, event);
}

//override トピックを変更するタスク(別スレッド)を開始する
void CIRCConnection::startChangeTopicTask(const IUser* user, const wxString& topic){
	m_client->changeTopic(user->getChannelString(), topic);

	CChannelData channel;
	channel.m_name = wxString(user->getChannelString());
	channel.m_topic = wxString(user->getChannelString());

	CChannelStreamEvent* event = new CChannelStreamEvent();
	event->SetEventType(myEVT_THREAD_STREAM_CH_UPDATE);
	event->setChannel(channel);
	event->setConnectionId(m_connectionId);
	wxQueueEvent(m_handler, event);
}
}
} /* namespace CornStarch */
