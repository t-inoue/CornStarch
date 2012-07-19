

#include <iostream>
#include "IRCParser.h"
#include "vector"
#include "GetMemberEvent.hpp"
#include "StringUtility.h"
#include "MsgStreamEvent.hpp"
#include "GetMessageEvent.hpp"
#include "MsgStreamEvent.hpp"
#include "ChannelStreamEvent.hpp"
#include "JoinStreamEvent.hpp"
#include "PartStreamEvent.hpp"
#include "UserStreamEvent.hpp"
wxDECLARE_EVENT(myEVT_THREAD_GET_MEMBER, CGetMemberEvent);
wxDECLARE_EVENT(myEVT_THREAD_GET_MESSAGE, CGetMessageEvent);

wxDECLARE_EVENT(myEVT_THREAD_STREAM_MSG_ADD, CMsgStreamEvent);
wxDECLARE_EVENT(myEVT_THREAD_STREAM_CH_JOIN, CJoinStreamEvent);
wxDECLARE_EVENT(myEVT_THREAD_STREAM_CH_PART, CPartStreamEvent);
wxDECLARE_EVENT(myEVT_THREAD_STREAM_CH_UPDATE, CChannelStreamEvent);
wxDECLARE_EVENT(myEVT_THREAD_STREAM_USER_UPDATE, CUserStreamEvent);

namespace CornStarch {
namespace IRC {
wxThreadEvent* CIRCParser::parse(const std::string& content) {
	if (content[0] == ':') {
		int index = 1;
		int nextIndex = content.find(" ");
		string host = content.substr(index, nextIndex - index);
		index = nextIndex + 1;
		nextIndex = content.find(" ", index);
		string statusCode = content.substr(index, nextIndex - index);
		index = nextIndex + 1;
		string param = content.substr(index);
		if (statusCode == "PRIVMSG") {
			return createPrivateMessageEvent(host, param);
		}
		if (statusCode == "PART") {
			return createPartMessageEvent(host, param);
		}
		if (statusCode == "JOIN") {
			return createJoinMessageEvent(host, param);
		}
		if (statusCode == "TOPIC") {
			return createTopicMessageEvent(host, param);
		}
		if (statusCode == "353") {
			addNames(param);
		}
		if (statusCode == "332") {
			return createTopicEvent(param);
		}
		if (statusCode == "366") {
			return createNamesEvent(param);
		}

	}
	return NULL;
}

wxThreadEvent* CIRCParser::createTopicMessageEvent(const string& host,
		const string& param) const {
	return NULL;
}
wxThreadEvent* CIRCParser::createJoinMessageEvent(const string& host,
		const string& param) const {
	vector<string> names = CStringUtility::split(host, "!");
	string name = names[0];

	int index = param.find(" ");
	string channel = param.substr(0, index);
	CJoinStreamEvent* event = new CJoinStreamEvent();
	event->SetEventType(myEVT_THREAD_STREAM_CH_JOIN);
	event->setChannelName(channel);
	event->setUserName(name);
	return event;
}
wxThreadEvent* CIRCParser::createPartMessageEvent(const string& host,
		const string& param) const {
	vector<string> names = CStringUtility::split(host, "!");
	string name = names[0];

	int index = param.find(" ");
	string channel = param.substr(0, index);

	CPartStreamEvent* event = new CPartStreamEvent();
	event->SetEventType(myEVT_THREAD_STREAM_CH_PART);
	event->setChannelName(channel);
	event->setUserName(name);
	return event;

}
wxThreadEvent* CIRCParser::createPrivateMessageEvent(const string& host,
		const string& param) const {
	vector<string> names = CStringUtility::split(host, "!");
	string name = names[0];

	int index = param.find(" ");
	string channel = param.substr(0, index);
	int contentIndex = param.find(":") + 1;
	string content = param.substr(contentIndex,
			param.size() - contentIndex - 1);

	CMessageData message;
	message.m_id = -1;
	message.m_username = name;
	message.m_body = content;
	message.m_channel = channel;
	message.m_time = time(NULL);

	CMsgStreamEvent* event = new CMsgStreamEvent();
	event->SetEventType(myEVT_THREAD_STREAM_MSG_ADD);
	event->setMessage(message);
	return event;
}

void CIRCParser::addNames(const string& param) {
	int index = param.find(":");
	string names = param.substr(index + 1);
	m_buffer += names;
}
wxThreadEvent* CIRCParser::createNamesEvent(const string& param) {
	vector<CMemberData*> result;
	vector<string> names = CStringUtility::split(m_buffer, " ");

	// 各メンバについてループ
	int size = (int) names.size();
	for (int i = 0; i < size; i++) {
		if (names[i].size() != 0 && names[i] != "\r") {
			// パラメータの取得
			CMemberData* mem = new CMemberData();
			mem->m_name = names[i]; // 名前(name)
			mem->m_nick = names[i]; // ニックネーム(name)
			// vectorに追加
			result.push_back(mem);
		}
	}

	CGetMemberEvent* event = new CGetMemberEvent();
	event->setMembers(result); // 値取得
	event->SetEventType(myEVT_THREAD_GET_MEMBER); // イベントの種類をセット
	m_buffer = "";
	return event;
}

wxThreadEvent* CIRCParser::createTopicEvent(const string& param) const {

	return NULL;
}

}
}
