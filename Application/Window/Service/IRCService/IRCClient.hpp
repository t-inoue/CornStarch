//
//  IRCClient.h
//  testtest
//
//  Created by  on 12/07/13.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef _IRCClient_h
#define _IRCClient_h
#include "../SocketClient.hpp"
#include "IRCParser.hpp"
#include "Thread.hpp"

namespace CornStarch
{
namespace IRC
{
// IRCと接続するためのクライントクラスです。
class CIRCClient: public CSocketClient
{
    // 受信用のスレッドです。
    Thread *recieveThread;
    // ミューテックス
    wxMutex *m_mutex;
	// ホスト名です。
	wxString m_host;
	// ポート番号です
	wxString m_port;
	// コネクションIDです。
	int m_connectionId;

	// 切断中かを示します。
	bool m_isClosing;
	wxEvtHandler* m_handler;
	// 受信ループです。
	void receiveLoop(void);
	// ハートビートへの反応です。
	void pong(const wxString& value);
    // コマンドをスレッドセーフで送信します。
    void sendCommand(const wxString& target);
	//IRCへ接続します。
	void connect(const wxString& content);
public:
	CIRCClient();
	virtual ~CIRCClient(void);
	// 初期化します。
	void init(int connectionId);
	// 通信を開始します。
	void startAsync(wxEvtHandler* handler, const wxString& userName,
			const wxString& password);
	// Quitメッセージを送ります。
	void quitAsync(void);

	// IRCから切断します。
	void disconnect(void);
	// メッセージを送ります。
	void sendMessageAsync(const wxString& target, const wxString& content);
	// Noticeを送ります。
	void sendNoticeAsync(const wxString& target, const wxString& content);
	// チャンネルに参加します。
	void joinAsync(const wxString& channelName);
	// チャンネルから離脱します。
	void partAsync(const wxString& channelName);
	// トピックを変更します。
	void changeTopicAsync(const wxString& channelName, const wxString& content);
	// ニックネームを変更します。
	void changeNicknameAsync(const wxString& content);

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
}

;
}
} /* namespace CornStarch */

#endif
