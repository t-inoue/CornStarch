#pragma once
#include "SCPostMessageTask.hpp"
#include "SCGetChannelTask.hpp"
#include "SCGetMessageTask.hpp"
#include "SCGetMemberTask.hpp"
#include "SCAuthTask.hpp"
#include "SCJoinChannelTask.hpp"
#include "SCPartChannelTask.hpp"
#include "SCGetMemberInfoTask.hpp"
#include "SCNickChangeTask.hpp"
#include "SCTopicChangeTask.hpp"
#include "SCGetStreamTask.hpp"
#include "IConnection.hpp"
#include "IUser.h"

namespace CornStarch
{;
namespace StarChat
{;

// 通信部分を管理(通信結果をイベントとして返す)
class CSCConnection: public IConnection
{
private:

	CSCAuthTask* m_authTask; // ユーザ認証用タスク
	CSCGetStreamTask* m_getStreamTask; // ストリーム受信タスク
	int m_connetionId;
	wxEvtHandler* m_handler;
	wxString m_host;
public:

	CSCConnection(void);
	~CSCConnection(void);
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
	// 初期化を行う
	void init(int connectionId, wxEvtHandler* handler);

	// メッセージを投稿するタスク(別スレッド)を開始する
	void startPostMessageTask(const IUser* user, const wxString& message,
			const wxString& channel);

	// チャンネルのメッセージを取得するタスク(別スレッド)を開始する
	void startGetMessageTask(const IUser* user, const wxString& channel);

	// チャンネルのメンバーを取得するタスク(別スレッド)を開始する
	void startGetMemberTask(const IUser* user, const wxString& channel);

	// ユーザの所属するチャンネル一覧を取得するタスク(別スレッド)を開始する
	void startGetChannelTask(const IUser* user);

	// チャンネルから離脱するタスク(別スレッド)を開始する
	void startPartTask(const IUser* user, const wxString& channel);

	// チャンネルに参加するタスク(別スレッド)を開始する
	void startJoinTask(const IUser* user, const wxString& channel);

	// メンバーの情報を取得するタスク(別スレッド)を開始する
	void startGetMemberInfoTask(const IUser* user,const wxString& name);

    // ニックネームを変更するタスク(別スレッド)を開始する
    void startNickChangeTask(const IUser* user, const wxString& nick);

    // トピックを変更するタスク(別スレッド)を開始する
    void startChangeTopicTask(const IUser* user, const wxString& topic);

	// ユーザが正規の人かどうか判断するタスク(別スレッド)を開始する
	void startAuthTask(const IUser* user);

	// ストリーム通信タスク(別スレッド)を開始
	void startStreamTask(const IUser* user);

	// 認証用タスク(別スレッド)を削除する
	void deleteAuthTask(void);

private:

	// 別スレッドでタスクを開始する
	void startThread(CSCTask* task);

};

}
}