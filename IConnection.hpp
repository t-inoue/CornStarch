#ifndef IConnection_H_
#define IConnection_H_

using namespace std;

class IConnection {
public:
	IConnection() {
	}
	virtual ~IConnection() {
	}
	// 初期化を行う
	virtual void init(wxEvtHandler* handler) = 0;

	// メッセージを投稿するタスク(別スレッド)を開始する
	virtual void startPostMessageTask(wxEvtHandler* handler,
			const wxString& message, const wxString& channel,
			const wxString& basic) = 0;

	// チャンネルのメッセージを取得するタスク(別スレッド)を開始する
	virtual void startGetMessageTask(wxEvtHandler* handler,
			const wxString& channel, const wxString& basic) = 0;

	// チャンネルのメンバーを取得するタスク(別スレッド)を開始する
	virtual void startGetMemberTask(wxEvtHandler* handler,
			const wxString& channel, const wxString& basic) = 0;

	// ユーザの所属するチャンネル一覧を取得するタスク(別スレッド)を開始する
	virtual void startGetChannelTask(wxEvtHandler* handler,
			const wxString& userName, const wxString& basic) = 0;

	// チャンネルから離脱するタスク(別スレッド)を開始する
	virtual void startPartTask(wxEvtHandler* handler,
			const wxString& channel, const wxString& userName,
			const wxString& basic) = 0;

	// チャンネルに参加するタスク(別スレッド)を開始する
	virtual void startJoinTask(wxEvtHandler* handler,
			const wxString& channel, const wxString& userName,
			const wxString& basic) = 0;

	// メンバーの情報を取得するタスク(別スレッド)を開始する
	virtual void startGetMemberInfoTask(wxEvtHandler* handler,
			const wxString& userName, const wxString& basic) = 0;

	// ユーザが正規の人かどうか判断するタスク(別スレッド)を開始する
	virtual void startAuthTask(wxEvtHandler* handler,
			const wxString& userName, const wxString& basic) = 0;

	// ストリーム通信タスク(別スレッド)を開始
	virtual void startStreamTask(wxEvtHandler* handler,
			const wxString& userName, const wxString& basic) = 0;

	// 認証用タスク(別スレッド)を削除する
	virtual void deleteAuthTask(void) = 0;
};

#endif /* IConnection_H_ */
