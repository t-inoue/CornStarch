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
#include "StringUtility.hpp"
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
#include "IRCMessageData.hpp"

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

	wxString m_buffer;
	// 名前一覧の名前をバッファに追加します。
	void addNames(const CIRCMessageData& param);

	// ニックネームイベントを生成します。
	CConnectionEventBase* createNickMessageEvent(const CIRCMessageData& message) const;
	// トピックイベントを生成します。
	CConnectionEventBase* createTopicMessageEvent(const CIRCMessageData& message) const;
	// 参加イベントを生成します。
	CConnectionEventBase* createJoinMessageEvent(const CIRCMessageData& message) const;
	// 離脱イベントを作成します。
	CConnectionEventBase* createPartMessageEvent(const CIRCMessageData& message) const;
	// メッセージのイベントを作成します。
	CConnectionEventBase* createPrivateMessageEvent(const CIRCMessageData& message) const;
	//　名前一覧取得のイベントを作成します。
	CConnectionEventBase* createNamesEvent(const CIRCMessageData& message);
	// 招待イベントを作成します。
	CConnectionEventBase* createInviteEvent(const CIRCMessageData& message) const;
	// キックイベントを作成します。
	CConnectionEventBase* createKickEvent(const CIRCMessageData& message) const;
	// トピック取得のイベントを作成します。
	CConnectionEventBase* createTopicEvent(const CIRCMessageData& message) const;

	CConnectionEventBase* createEvent (const CIRCMessageData& message);
public:

	CIRCParser();
	virtual ~CIRCParser(void);
	CConnectionEventBase* parse(const wxString& content);

};
}
}

#endif
