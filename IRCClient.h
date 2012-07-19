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
// IRCと接続するためのクライントクラスです。
class CIRCClient: public CSocketClient {

	// ホスト名です。
	wxString m_host;
	// ポート番号です
	wxString m_port;
	// コネクションIDです。
	int m_connectionId;
	// 接続されているかを取得します。
	bool m_connected;


	wxEvtHandler* m_handler;
	void receiveLoop();
public:
	CIRCClient();
	virtual ~CIRCClient(void);
	void init(int connectionId);
	void start(wxEvtHandler* handler,wxString userName,wxString password);
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
