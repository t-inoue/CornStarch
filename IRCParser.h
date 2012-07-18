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
#include "string"

using namespace std;

namespace CornStarch {
namespace IRC {
class CIRCParser {
	string m_buffer;
	void addNames(const string& param);

	wxThreadEvent* createTopicMessageEvent(const string& host,
			const string& param) const;
	wxThreadEvent* createJoinMessageEvent(const string& host,
			const string& param) const;
	wxThreadEvent* createPartMessageEvent(const string& host,
			const string& param) const;
	wxThreadEvent* createPrivateMessageEvent(const string& host,
			const string& param) const;
	wxThreadEvent* createNamesEvent(const string& param);
	wxThreadEvent* createTopicEvent(const string& param) const;
public:
	//CStreamData getStreamData(const std::string& content) const;
	wxThreadEvent* parse(const std::string& content);

};
}
}

#endif
