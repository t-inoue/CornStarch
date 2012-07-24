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

namespace CornStarch
{
namespace IRC
{
// IRCと接続するためのクライントクラスです。
class CIRCClient: public CSocketClient
{

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
	void start(wxEvtHandler* handler, const wxString& userName,
			const wxString& password);
	// 切断します。
	void quit(void);
	// メッセージを送ります。
	void sendMessage(const wxString& target, const wxString& content);
	// Noticeを送ります。
	void sendNotice(const wxString& target, const wxString& content);
	// チャンネルに参加します。
	void join(const wxString& channelName);
	// チャンネルから離脱します。
	void part(const wxString& channelName);
	// トピックを変更します。
	void changeTopic(const wxString& channelName, const wxString& content);
	// ニックネームを変更します。
	void changeNickname(const wxString& content);

	// トピックを非同期で取得します。
	void getTopicAsync(const wxString& channelName);
	// 名前一覧を非同期で取得します。
	void getNamesAsync(const wxString& channelName);

	// ホストを取得
	wxString getHost() const
	{
		return m_host;
	}
	// ホストを設定
	void setHost(wxString host)
	{
		m_host = host;
	}
	// ポートを取得
	wxString getPort() const
	{
		return m_port;
	}
	// ポートを設定
	void setPort(wxString port)
	{
		m_port = port;
	}
}

;
}
} /* namespace CornStarch */

#endif
