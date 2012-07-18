/*
 * IRCConnection.h
 *
 *  Created on: 2012/07/13
 */

#ifndef IRCCONNECTION_H_
#define IRCCONNECTION_H_
#include "header.hpp"
#include "IConnection.hpp"
#include "IRCClient.h"
#include "ChannelData.hpp"

namespace CornStarch {
namespace IRC {
class CIRCConnection: public IConnection {
	CIRCClient *m_client;
	vector<CChannelData*> m_channels;

//        CAuthTask* m_authTask; // ユーザ認証用タスク
//        CGetStreamTask* m_getStreamTask; // ストリーム受信タスク
public:
	CIRCConnection();
	virtual ~CIRCConnection(void);

	//override 初期化を行う
	void init(wxEvtHandler* handler);

	//override メッセージを投稿するタスク(別スレッド)を開始する
	void startPostMessageTask(wxEvtHandler* handler, const std::string& message,
			const std::string& channel, const std::string& basic);

	//override チャンネルのメッセージを取得するタスク(別スレッド)を開始する
	void startGetMessageTask(wxEvtHandler* handler, const std::string& channel,
			const std::string& basic);

	//override チャンネルのメンバーを取得するタスク(別スレッド)を開始する
	void startGetMemberTask(wxEvtHandler* handler, const std::string& channel,
			const std::string& basic);

	//override ユーザの所属するチャンネル一覧を取得するタスク(別スレッド)を開始する
	void startGetChannelTask(wxEvtHandler* handler, const std::string& userName,
			const std::string& basic);

	//override チャンネルから離脱するタスク(別スレッド)を開始する
	void startPartTask(wxEvtHandler* handler, const std::string& channel,
			const std::string& userName, const std::string& basic);

	//override チャンネルに参加するタスク(別スレッド)を開始する
	void startJoinTask(wxEvtHandler* handler, const std::string& channel,
			const std::string& userName, const std::string& basic);

	//override メンバーの情報を取得するタスク(別スレッド)を開始する
	void startGetMemberInfoTask(wxEvtHandler* handler,
			const std::string& userName, const std::string& basic);

	//override ユーザが正規の人かどうか判断するタスク(別スレッド)を開始する
	void startAuthTask(wxEvtHandler* handler, const std::string& userName,
			const std::string& basic);

	//override ストリーム通信タスク(別スレッド)を開始
	void startStreamTask(wxEvtHandler* handler, const std::string& userName,
			const std::string& basic);

	//override 認証用タスク(別スレッド)を削除する
	void deleteAuthTask(void);

private:

	// 別スレッドでタスクを開始する
//        void startThread(CSCTask* task);  

};
}
} /* namespace CornStarch */
#endif /* IRCCONNECTION_H_ */
