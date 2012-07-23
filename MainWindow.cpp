﻿#include "DefineEventTable.hpp" // イベントテーブル
#include "MainWindow.hpp"
#include "SCConnectionContents.h"
#include "IRCConnectionContents.h"
#include "StringUtility.h"

using namespace std;

//////////////////////////////////////////////////////////////////////

CMainWindow::CMainWindow(void) :
		m_view(NULL), m_logHolder(NULL), m_contents(NULL), m_serverIdLog(0), m_currentServerId(
				0)
{
}

CMainWindow::~CMainWindow(void)
{
	delete m_view;
	delete m_logHolder;

	int size = (int) m_contents.size();
	for (int i = 0; i < size; i++)
	{
		delete m_contents[i];
	}
}

//////////////////////////////////////////////////////////////////////

// 初期化を行う
void CMainWindow::init(void)
{
	// viewの初期化
	m_view = new CMainView();
	m_view->init(this);
	SetMenuBar(m_view->getMenuBar()); // メニューバー

	// ログ保持部の初期化
	m_logHolder = new CMainLogHolder();

	// イベントハンドラの初期化
	initHandle();
}

//////////////////////////////////////////////////////////////////////
CConnectionContents* CMainWindow::getConnectionContents(int connectionId)
{
	vector<CConnectionContents*>::iterator it = m_contents.begin();
	while (it != m_contents.end())
	{
		if ((*it)->getId() == connectionId)
		{
			return *it;
		}
		++it;
	}
	return NULL;
}

// 画面操作に関するイベントハンドラを設定する
void CMainWindow::initHandle(void)
{
	// エンターキー押下時
	this->Connect(m_view->getPostPaneID(), wxEVT_COMMAND_TEXT_ENTER,
			wxCommandEventHandler(CMainWindow::onEnter));
}

// Modelがあれば画面を更新する
void CMainWindow::updateAllView(int connectionId, const wxString& channel)
{
	updateMessageView(connectionId, channel);
	updateMemberView(connectionId, channel);
	updateChannelView(connectionId, channel);
}

// メッセージ画面を更新する(Modelがある場合)
void CMainWindow::updateMessageView(int connectionId, const wxString& channel)
{
	if (connectionId == m_currentServerId)
	{
		CConnectionContents* contents = getConnectionContents(connectionId);
		contents->onUpdateMessageView(channel);

		// メッセージを表示
		m_view->displayMessages(contents->getMessages(channel),
				contents->getNickTable());
	}
}
// メンバー画面を更新する(Modelがある場合)
void CMainWindow::updateMemberView(int connectionId, const wxString& channel)
{
	if (connectionId == m_currentServerId)
	{
		CConnectionContents* contents = getConnectionContents(connectionId);
		contents->onUpdateMemberView(channel);

		// メンバーを表示
		m_view->displayMembers(contents->getMembers(channel));
		m_view->displayMessages(contents->getMessages(channel),
				contents->getNickTable());
	}
}

// チャンネル画面とタイトルバーを更新する(Modelがある場合)
void CMainWindow::updateChannelView(int connectionId, const wxString& channel)
{
	CConnectionContents* contents = getConnectionContents(connectionId);
	contents->onUpdateChannelView();

	// チャンネルを表示
	displayTitle(channel, contents->getTopic(channel));


	m_view->displayChannels(m_contents);

	m_view->setSelectedChannel(contents->getCurrentChannel());
}

// タイトルバーにタイトルを表示する
void CMainWindow::displayTitle(const wxString& channel, const wxString& topic)
{
	wxString tpc = topic;
	// 改行を消してタイトルを表示
	tpc.Replace("\r\n", " ");
	tpc.Replace("\n", " ");
	this->SetTitle("【" + channel + "】" + tpc);
}

//////////////////////////////////////////////////////////////////////

// 終了
void CMainWindow::onQuit(wxCommandEvent& event)
{
	Close(true);
}

// ユーザ登録(SC)
void CMainWindow::onSCRegister(wxCommandEvent& event)
{

	// 認証ダイアログを表示
	if (m_view->showModalSCAuthDlg() != wxID_OK)
	{
		return;
	}
	CConnectionContents* contents = new CSCConnectionContents(); //new CornStarch::IRC::CIRCConnectionContents();//
	addNewConneection(contents);
}

// ユーザ登録(IRC)
void CMainWindow::onIRCRegister(wxCommandEvent& event)
{
	// 認証ダイアログを表示
	if (m_view->showModalIRCAuthDlg() != wxID_OK)
	{
		return;
	}

	// ここでIRCサーバの追加を行う
	CConnectionContents* contents =
			new CornStarch::IRC::CIRCConnectionContents(); //
	addNewConneection(contents);
}
void CMainWindow::addNewConneection(CConnectionContents* connnection)
{
	connnection->setId(m_serverIdLog);
	connnection->init(GetEventHandler());
	m_contents.push_back(connnection);
	m_serverIdLog++;
	// コンテンツを更新
	connnection->registerUser(m_view->getDlgUserName(), m_view->getDlgPassword());
}
// ログアウトメニュー
void CMainWindow::onLogout(wxCommandEvent& event)
{
	// 永続化している情報を削除
	//m_contents->logout();
	Close();
}

// チャンネルに参加メニュー
void CMainWindow::onJoin(wxCommandEvent& event)
{

	CConnectionContents* contents = getConnectionContents(m_currentServerId);
	// 未ログインの時
	if (!contents->isUserLogin())
	{
		return;
	}

	// ダイアログを表示
	if (m_view->showModalChannelDlg() != wxID_OK)
	{
		return;
	}

	// チャンネル参加タスクの開始
	contents->joinChannel(m_view->getDlgChannelName());
}

// チャンネルから離脱メニュー
void CMainWindow::onPart(wxCommandEvent& event)
{
	CConnectionContents* contents = getConnectionContents(m_currentServerId);
	// 未ログインの時
	if (!contents->isUserLogin())
	{
		return;
	}

	// ダイアログを表示
	if (m_view->showModalChannelDlg() != wxID_OK)
	{
		return;
	}

	// チャンネル離脱タスクを開始
	contents->partChannel(m_view->getDlgChannelName());
}

// 表示を更新
void CMainWindow::onUpdateDisplay(wxCommandEvent& event)
{
	vector<CConnectionContents*>::iterator it = m_contents.begin();
	while (it != m_contents.end())
	{
		// 保持しているデータを初期化
		(*it)->reconnect();
		(*it)->clearChannels();
		(*it)->clearNickTable();
		++it;
	}

	CConnectionContents* contents = getConnectionContents(m_currentServerId);
	// 表示を更新
	updateAllView(m_currentServerId, contents->getCurrentChannel());
}

//////////////////////////////////////////////////////////////////////

// 投稿ペインでEnterキーを押下
void CMainWindow::onEnter(wxCommandEvent& event)
{
	CConnectionContents* contents = getConnectionContents(m_currentServerId);
	// 何も文がないとき
	wxString body = event.GetString();
	if (body == "")
	{
		return;
	}

	// 未ログインの時
	if (!contents->isUserLogin())
	{
		m_view->clearPostPaneText();
		return;
	}

	// コンテンツの更新
	CMessageData message = contents->generateMessage(body);
	contents->postMessage(message);
	m_logHolder->pushMessageLog(message, contents->getNickName());

	// 表示の更新
	m_view->clearPostPaneText();
	m_view->displayLogs(m_logHolder->getLogs());
	updateMessageView(m_currentServerId, contents->getCurrentChannel());
}

// チャンネル選択時
void CMainWindow::onChannelSelected(CChannelSelectEvent& event)
{
    // 選択したのがサーバ名だったとき
    if (event.isServerSelected()){
        return;
    }

	// サーバーIDとチャンネル名を取得
    wxString channel = event.getString();
    m_currentServerId = event.getServerId();

    // 選択したコンテンツを取得
	CConnectionContents* contents = getConnectionContents(m_currentServerId);

    // コンテンツの更新
	contents->selectChannel(channel);

	// 画面表示を更新
	wxString ch = contents->getCurrentChannel();
	displayTitle(ch, contents->getTopic(ch));
	updateMessageView(m_currentServerId, contents->getCurrentChannel());
	updateMemberView(m_currentServerId, contents->getCurrentChannel());
}


//////////////////////////////////////////////////////////////////////


// メッセージ投稿終了時
void CMainWindow::onFinishPostMessage(wxThreadEvent& event)
{
}

// 認証情報の受信時
void CMainWindow::onGetAuth(CAuthEvent& event)
{
	// 認証に失敗
	if (!event.isAuthSucceeded())
	{
		wxMessageBox("認証に失敗しました");
		return;
	}

	CConnectionContents* contents = getConnectionContents(
			event.getConnectionId());
	// コンテンツの更新
	contents->onAuthSucceeed();

	// 画面表示の更新
	updateAllView(event.getConnectionId(), contents->getCurrentChannel());
}

// メッセージ一覧受信時
void CMainWindow::onGetMessages(CGetMessageEvent& event)
{
	CConnectionContents* contents = getConnectionContents(
			event.getConnectionId());
	// メッセージを追加
	contents->onGetMessages(event.getMessages());

	// 表示の更新
	updateMessageView(event.getConnectionId(), contents->getCurrentChannel());
}

// メンバー一覧受信時
void CMainWindow::onGetMembers(CGetMemberEvent& event)
{
	CConnectionContents* contents = getConnectionContents(
			event.getConnectionId());
	// メンバーの追加
	contents->onGetMembers(event.getMembers());

	// 表示の更新
	updateMemberView(event.getConnectionId(), contents->getCurrentChannel());
}

// チャンネル一覧受信時
void CMainWindow::onGetChannels(CGetChannelEvent& event)
{
	{
		CConnectionContents* contents = getConnectionContents(
				event.getConnectionId());
		// チャンネルの追加
		contents->onGetChannels(event.getChannels());

		// 表示の更新
		updateChannelView(event.getConnectionId(),
				contents->getCurrentChannel());
		updateMemberView(event.getConnectionId(),
				contents->getCurrentChannel());
		updateMessageView(event.getConnectionId(),
				contents->getCurrentChannel());
	}
}
// チャンネル参加時
void CMainWindow::onJoinChannel(CJoinEvent& event)
{
	CConnectionContents* contents = getConnectionContents(
			event.getConnectionId());
	contents->onJoinChannel(event.GetString());
}

// チャンネル離脱時
void CMainWindow::onPartChannel(CPartEvent& event)
{
	CConnectionContents* contents = getConnectionContents(
			event.getConnectionId());

	contents->onPartChannel(event.GetString());

	// 表示の更新
	updateAllView(event.getConnectionId(), contents->getCurrentChannel());
}

// メンバー情報の受信時
void CMainWindow::onGetMemberInfo(CGetMemberInfoEvent& event)
{
	CConnectionContents* contents = getConnectionContents(
			event.getConnectionId());
	// データ更新
	CMemberData data = event.getMember();
	contents->onGetMemberStatus(data);
	m_logHolder->onUpdateNickName(data);

	// 表示を更新
	updateMemberView(event.getConnectionId(), contents->getCurrentChannel());
	updateMessageView(event.getConnectionId(), contents->getCurrentChannel());
	m_view->displayLogs(m_logHolder->getLogs());
}

// メッセージストリーム受信時
void CMainWindow::onMsgStream(CMsgStreamEvent& event)
{
	CConnectionContents* contents = getConnectionContents(
			event.getConnectionId());
	CMessageData data = event.getMessage();
	bool myPost = contents->isPostedThisClient(data);

	contents->onGetMessageStream(data);
	if (!myPost)
	{
		m_logHolder->pushMessageLog(data,
				contents->getMemberNick(data.m_username));
	}

	// メッセージをログ一覧に表示
	m_view->displayLogs(m_logHolder->getLogs()); // ログペイン
	if (contents->getCurrentChannel() == data.m_channel)
	{
		updateMessageView(event.getConnectionId(), data.m_channel);
	}

	// 通知があったとき && 自分以外の人から
	if (contents->isUserCalled(data.m_body) && !myPost)
	{
        m_view->messageNotify("通知", "呼ばれました");
	}
}

// チャンネル参加ストリーム受信時
void CMainWindow::onJoinStream(CJoinStreamEvent& event)
{
	CConnectionContents* contents = getConnectionContents(
			event.getConnectionId());
	// 処理待ちに追加
	CSubscribeData data(event.getChannelName(), event.getUserName());
	contents->onGetJoinStream(data.m_channel, data.m_username);
	m_logHolder->pushJoinLog(data, contents->getMemberNick(data.m_username));

	// 表示の更新
	m_view->displayLogs(m_logHolder->getLogs()); // ログペイン
	if (data.m_channel == contents->getCurrentChannel())
	{
		updateMemberView(event.getConnectionId(), data.m_channel);
	}
}

// チャンネル離脱ストリーム受信時
void CMainWindow::onPartStream(CPartStreamEvent& event)
{
	CConnectionContents* contents = getConnectionContents(
			event.getConnectionId());
	CSubscribeData data(event.getChannelName(), event.getUserName());
	wxString name = event.getUserName();
	wxString channel = event.getChannelName();

	// データ更新
	contents->onGetPartStream(channel, name);
	m_logHolder->pushPartLog(data, contents->getMemberNick(data.m_username));

	// 表示の更新
	m_view->displayLogs(m_logHolder->getLogs()); // ログペイン
	if (channel == contents->getCurrentChannel())
	{
		updateMemberView(event.getConnectionId(), channel);
	}
}

// チャンネル更新ストリーム受信時
void CMainWindow::onChannelStream(CChannelStreamEvent& event)
{
	CConnectionContents* contents = getConnectionContents(
			event.getConnectionId());
	// データ更新
	CChannelData channel = event.getChannel();
	contents->onGetChannelStream(channel);
	m_logHolder->pushTopicLog(channel);

	// 表示の更新
	m_view->displayLogs(m_logHolder->getLogs()); // ログペイン

	// 現在のチャンネルならばタイトルを更新
	if (channel.m_name == contents->getCurrentChannel())
	{
		displayTitle(channel.m_name, channel.m_topic);
	}
}

// ユーザ情報更新ストリーム受信時
void CMainWindow::onUserStream(CUserStreamEvent& event)
{
	CConnectionContents* contents = getConnectionContents(
			event.getConnectionId());
	// データ更新
	CMemberData member = event.getMember();
	contents->onGetUserStream(member);
	m_logHolder->pushChangeNickLog(member);

	// 表示の更新
	updateMemberView(event.getConnectionId(), contents->getCurrentChannel()); // メンバーペイン
	updateMessageView(event.getConnectionId(), contents->getCurrentChannel()); // メッセージペイン
	m_view->displayLogs(m_logHolder->getLogs()); // ログペイン
}
