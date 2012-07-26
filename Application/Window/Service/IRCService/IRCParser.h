//
//  IRCParser.h
//  testtest
//
//  Created by  on 12/07/17.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef _IRCParser_h
#define _IRCParser_h
#include <wx/wxprec.h>
#include <wx/wx.h>
#include <string>
#include <iostream>
#include <vector>
#include "StringUtility.h"
#include "../Event/GetMemberEvent.hpp"
#include "../Event/MsgStreamEvent.hpp"
#include "../Event/GetMessageEvent.hpp"
#include "../Event/MsgStreamEvent.hpp"
#include "../Event/ChannelStreamEvent.hpp"
#include "../Event/JoinStreamEvent.hpp"
#include "../Event/PartStreamEvent.hpp"
#include "../Event/UserStreamEvent.hpp"
#include "../Event/AuthEvent.hpp"
#include "../Event/ConnectionEventBase.hpp"

using namespace std;

namespace CornStarch
{
namespace IRC
{
//IRC用のイベントから呼び出します。
class CIRCParser
{

	// メッセージに設定するId
	int m_messageId;

	string m_buffer;
	// 名前一覧の名前をバッファに追加します。
	void addNames(const string& param);

	// ニックネームイベントを生成します。
	CConnectionEventBase* createNickMessageEvent(const string& host,
			const string& param) const;
	// トピックイベントを生成します。
	CConnectionEventBase* createTopicMessageEvent(const string& host,
			const string& param) const;
	// 参加イベントを生成します。
	CConnectionEventBase* createJoinMessageEvent(const string& host,
			const string& param) const;
	// 離脱イベントを作成します。
	CConnectionEventBase* createPartMessageEvent(const string& host,
			const string& param) const;
	// メッセージのイベントを作成します。
	CConnectionEventBase* createPrivateMessageEvent(const string& host,
			const string& param) const;
	//　名前一覧取得のイベントを作成します。
	CConnectionEventBase* createNamesEvent(const string& param);
	// トピック取得のイベントを作成します。
	CConnectionEventBase* createTopicEvent(const string& param) const;
public:

	CIRCParser();
	virtual ~CIRCParser(void);
	CConnectionEventBase* parse(const std::string& content);

};
}
}

#endif
