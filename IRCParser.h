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
class CIRCParser {
	string m_buffer;
	void addNames(const string& param);

	CConnectionEventBase* createTopicMessageEvent(const string& host,
			const string& param) const;
	CConnectionEventBase* createJoinMessageEvent(const string& host,
			const string& param) const;
	CConnectionEventBase* createPartMessageEvent(const string& host,
			const string& param) const;
	CConnectionEventBase* createPrivateMessageEvent(const string& host,
			const string& param) const;
	CConnectionEventBase* createNamesEvent(const string& param);
	CConnectionEventBase* createTopicEvent(const string& param) const;
public:
	CConnectionEventBase* parse(const std::string& content);

};
}
}

#endif
