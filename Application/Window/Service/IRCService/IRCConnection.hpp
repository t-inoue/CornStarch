
#ifndef IRCCONNECTION_H_
#define IRCCONNECTION_H_
#include "../IConnection.hpp"
#include "IRCClient.hpp"
#include "IRCUser.hpp"
#include "../Event/AuthEvent.hpp"
#include "../Event/JoinEvent.hpp"
#include "../Event/GetChannelEvent.hpp"
#include "../Event/GetMemberInfoEvent.hpp"
#include "../Event/PartEvent.hpp"
#include "../Event/GetChannelEvent.hpp"
#include "../Event/GetMessageEvent.hpp"
#include "../Event/ChannelStreamEvent.hpp"
#include "../Event/UserStreamEvent.hpp"
#include "../Event/DisconnectEvent.hpp"
#include "Task/IRCTask.hpp"
#include "IRCCommand.hpp"
#include "IRCEventFactory.hpp"

namespace CornStarch
{
namespace IRC
{
class CIRCConnection: public IConnection
{
    // イベントファクトリー
    CIRCEventFactory m_eventFactory;
    // チャンネル名の検証
    wxString getValidateChannelName(const wxString& channel);
    // IRCクライアント
	CIRCClient *m_client;
	// イベントハンドラ
	wxEvtHandler* m_handler;
	// サービスID
	int m_connectionId;
	// チャンネル参加済みの一覧
	vector<CChannelData*> m_channels;

	// IRCのホスト
	wxString m_host;

	void invokeEvent(CConnectionEventBase* event);
public:
	CIRCConnection();
	virtual ~CIRCConnection(void);

	//override 初期化を行う
	void init(int connectionId, wxEvtHandler* handler);

	//override メッセージを投稿するタスク(別スレッド)を開始する
	void startPostMessageTask(const IUser* user, const wxString& message,
			const wxString& channel);

	//override チャンネルのメッセージを取得するタスク(別スレッド)を開始する
	void startGetMessageTask(const IUser* user, const wxString& channel);

	//override チャンネルのメンバーを取得するタスク(別スレッド)を開始する
	void startGetMemberTask(const IUser* user, const wxString& channel);

	//override ユーザの所属するチャンネル一覧を取得するタスク(別スレッド)を開始する
	void startGetChannelTask(const IUser* user);

	//override チャンネルから離脱するタスク(別スレッド)を開始する
	void startPartTask(const IUser* user, const wxString& channel);

	//override チャンネルに参加するタスク(別スレッド)を開始する
	void startJoinTask(const IUser* user, const wxString& channel);

	//override メンバーの情報を取得するタスク(別スレッド)を開始する
	void startGetMemberInfoTask(const IUser* user, const wxString& userName);

	//override ニックネームを変更するタスク(別スレッド)を開始する
	void startNickChangeTask(const IUser* user, const wxString& nick);

	//override トピックを変更するタスク(別スレッド)を開始する
	void startChangeTopicTask(const IUser* user, const wxString& topic);

	//override ユーザが正規の人かどうか判断するタスク(別スレッド)を開始する
	void startAuthTask(const IUser* user);

	//override ストリーム通信タスク(別スレッド)を開始
	void startStreamTask(const IUser* user);

	// ホストを取得
    wxString getHost() const;

    // ホストを設定
    void setHost(const wxString& host);

    // メッセージ取得
    void onMessageReceived( CMessageData* message);
    // 切断時
    void onDisconnected();
    // 接続開始時
    void onConnected();
    //　接続失敗時
    void onConnectionFailed();

};
}
} /* namespace CornStarch */
#endif /* IRCCONNECTION_H_ */
