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
	// 初期化します。
	void init(int connectionId);
	// 通信を開始します。
	void start(wxEvtHandler* handler,wxString userName,wxString password);
	// 切断します。
	void disconnect(void);
	// メッセージを送ります。
	void sendMessage(wxString target, wxString content);
	// Noticeを送ります。
	void sendNotice(wxString target, wxString content);
	// チャンネルに参加します。
	void join(wxString channelName);
	// チャンネルから離脱します。
	void part(wxString channelName);
	// トピックを変更します。
	void changeTopic(wxString channelName, wxString content);
	// ニックネームを変更します。
	void changeNickname(wxString content);

	// トピックを非同期で取得します。
	void getTopicAsync(wxString channelName);
	// 名前一覧を非同期で取得します。
	void getNamesAsync(wxString channelName);
};
}
} /* namespace CornStarch */

#endif
