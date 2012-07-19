//
//  IRCClient.h
//  testtest
//
//  Created by  on 12/07/13.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef _IRCClient_h
#define _IRCClient_h
#include "header.hpp"
#include "SocketClient.hpp"
#include "IRCUser.hpp"

namespace CornStarch {
namespace IRC {
class CIRCClient: public CSocketClient {
	CSocketClient* m_client;
	wxString m_host;
	wxString m_port;
	bool m_connected;
	CIRCUser* m_userInfo;

	wxEvtHandler* m_handler;
	void receiveLoop();
public:
	CIRCClient();
	virtual ~CIRCClient(void);
	void init(void);
	void start(wxEvtHandler* handler);
	void disconnect(void);
	void sendMessage(wxString target, wxString content);
	void sendNotice(wxString target, wxString content);
	void join(wxString channelName);
	void part(wxString channelName);
	void changeTopic(wxString channelName, wxString content);
	void changeNickname(wxString content);

	void getTopicAsync(wxString channelName);
	void getNamesAsync(wxString channelName);
};
}
} /* namespace CornStarch */

#endif
