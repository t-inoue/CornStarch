//
//  IRCParser.h
//  testtest
//
//  Created by  on 12/07/17.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef _IRCParser_h
#define _IRCParser_h
#include "StreamData.hpp"
#include "header.hpp"
#include "ConnectionEventBase.hpp"
#include "string"

using namespace std;

namespace CornStarch {
namespace IRC {
//IRC用のイベントから呼び出します。
class CIRCParser {
	string m_buffer;
	// 名前をバッファに追加します。
	void addNames(const string& param);

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
	CConnectionEventBase* parse(const std::string& content);

};
}
}

#endif
