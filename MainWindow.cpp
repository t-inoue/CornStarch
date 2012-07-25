#include "DefineEventTable.hpp" // イベントテーブル
#include "MainWindow.hpp"
#include "SCService.h"
#include "IRCService.h"
#include "StringUtility.h"

using namespace std;

//////////////////////////////////////////////////////////////////////

//<<<<<<< HEAD
//CMainWindow::CMainWindow(void) :
//		m_view(NULL), m_logHolder(NULL), m_serialize(NULL), m_serverIdLog(0),
//            m_currentServiceId(0)
//=======
CMainWindow::CMainWindow(void) : m_view(NULL), m_logHolder(NULL),
    m_serialize(NULL), m_uniqueServiceId(0), m_currentServiceId(0)
//>>>>>>> regSerial
{
}

CMainWindow::~CMainWindow(void)
{
//<<<<<<< HEAD
//	// ファイルに保存
//	m_serialize->saveService(m_services);
//
//	delete m_view;
//	delete m_logHolder;
//	delete m_serialize;
//=======
    // ファイルに保存
    //m_serialize->saveService(m_contents);
    m_persist->saveService(m_services);

	delete m_view;
	delete m_logHolder;
    delete m_serialize;
    delete m_persist;
//>>>>>>> regSerial

	map<int, CChatServiceBase*>::iterator it = m_services.begin();
	while (it != m_services.end()){
		delete (*it).second;
		++it;
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

//<<<<<<< HEAD
//	// サービスのシリアライズ
//	m_serialize = new CServiceSerializer();
//	m_serialize->init();
//	m_serialize->loadService(GetEventHandler(), m_services);
//	m_currentServiceId = 1000;
//=======
    // シリアライズされたサービスを読み込み
    //m_serialize = new CServiceSerializer();
    //m_serialize->init();
    //m_serialize->loadService(GetEventHandler(), m_contents, m_uniqueServiceId);

    m_persist = new CMyPersistent();
    m_persist->init();
    m_persist->loadService(GetEventHandler(), m_services, m_uniqueServiceId);
//>>>>>>> regSerial
}

//////////////////////////////////////////////////////////////////////
CChatServiceBase* CMainWindow::getService(int serviceId)
{
	map<int, CChatServiceBase*>::iterator it = m_services.find(serviceId);
	if (it != m_services.end()){
		return (*it).second;
	}
	return NULL;
}

// 画面操作に関するイベントハンドラを設定する
void CMainWindow::initHandle(void)
{
	// エンターキー押下時
	this->Connect(m_view->getPostPaneID(), wxEVT_COMMAND_TEXT_ENTER,
	        wxCommandEventHandler(CMainWindow::onEnter));

	// メンバーがダブルクリックされたとき
	this->Connect(m_view->getMemPaneID(), wxEVT_COMMAND_LISTBOX_DOUBLECLICKED,
	        wxCommandEventHandler(CMainWindow::onMemberSelected));
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
	if (connectionId == m_currentServiceId){
		CChatServiceBase* contents = getService(connectionId);
		contents->onUpdateMessageView(channel);

		// メッセージを表示
		m_view->displayMessages(contents->getMessages(channel),
		        contents->getNickTable());
	}
}
// メンバー画面を更新する(Modelがある場合)
void CMainWindow::updateMemberView(int connectionId, const wxString& channel)
{
	if (connectionId == m_currentServiceId){
		CChatServiceBase* contents = getService(connectionId);
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
	CChatServiceBase* contents = getService(connectionId);
	contents->onUpdateChannelView();

	// チャンネルを表示
	displayTitle(channel, contents->getTopic(channel));

	m_view->displayChannels(m_services);

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
	if (m_view->showModalSCAuthDlg() != wxID_OK){
		return;
	}
	CChatServiceBase* contents = new CSCService(); //new CornStarch::IRC::CIRCConnectionContents();//
	addNewService(contents);
}

// ユーザ登録(IRC)
void CMainWindow::onIRCRegister(wxCommandEvent& event)
{
	// 認証ダイアログを表示
	if (m_view->showModalIRCAuthDlg() != wxID_OK){
		return;
	}

	// ここでIRCサーバの追加を行う
	CChatServiceBase* contents = new CornStarch::IRC::CIRCService(); //
	addNewService(contents);
}
void CMainWindow::addNewService(CChatServiceBase* service)
{
//<<<<<<< HEAD
//	service->setId(m_serverIdLog);
//	m_serverIdLog++;
//	service->init(GetEventHandler());
//	service->setHost(m_view->getDlgHostName());
//	m_services.insert(
//	        map<int, CChatServiceBase*>::value_type(service->getId(), service));
//=======
	service->setId(m_uniqueServiceId);
	m_uniqueServiceId++;
	service->init(GetEventHandler());
	service->setHost(m_view->getDlgHostName());
	m_services.insert(
	        map<int, CChatServiceBase*>::value_type(service->getId(), service));
//>>>>>>> regSerial
	// コンテンツを更新
	service->registerUser(m_view->getDlgUserName(), m_view->getDlgPassword());
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

	CChatServiceBase* contents = getService(m_currentServiceId);
	// 未ログインの時
	if (!contents->isUserLogin()){
		return;
	}

	// ダイアログを表示
	if (m_view->showModalChannelDlg() != wxID_OK){
		return;
	}

	// チャンネル参加タスクの開始
	contents->joinChannel(m_view->getDlgChannelName());
}

// チャンネルから離脱メニュー
void CMainWindow::onPart(wxCommandEvent& event)
{
	CChatServiceBase* contents = getService(m_currentServiceId);
	// 未ログインの時
	if (!contents->isUserLogin()){
		return;
	}

	// ダイアログを表示
	if (m_view->showModalChannelDlg() != wxID_OK){
		return;
	}

	// チャンネル離脱タスクを開始
	contents->partChannel(m_view->getDlgChannelName());
}

// 表示を更新
void CMainWindow::onUpdateDisplay(wxCommandEvent& event)
{
	map<int, CChatServiceBase*>::iterator it = m_services.begin();
	while (it != m_services.end()){
		// 保持しているデータを初期化
		(*it).second->reconnect();
		(*it).second->clearChannels();
		(*it).second->clearNickTable();
		++it;
	}

	CChatServiceBase* contents = getService(m_currentServiceId);
	// 表示を更新
	updateAllView(m_currentServiceId, contents->getCurrentChannel());
}

// ニックネーム変更
void CMainWindow::onNickChange(wxCommandEvent& event)
{
	// 未ログインの時
	CChatServiceBase* contents = getService(m_currentServiceId);
	if (!contents->isUserLogin()){
		return;
	}

	// ニックネーム変更ダイアログを表示
	if (m_view->showModalNickDlg() != wxID_OK){
		return;
	}

	// データ更新
	contents->onNickChange(m_view->getNickName());
}

// トピック変更
void CMainWindow::onChangeTopic(wxCommandEvent& event)
{
	// 未ログインの時
	CChatServiceBase* contents = getService(m_currentServiceId);
	if (!contents->isUserLogin()){
		return;
	}

	// トピック変更ダイアログを表示
	if (m_view->showModalTopicDlg() != wxID_OK){
		return;
	}

	// データ更新
	contents->onChangeTopic(m_view->getTopic());
}

//////////////////////////////////////////////////////////////////////

// 投稿ペインでEnterキーを押下
void CMainWindow::onEnter(wxCommandEvent& event)
{
	CChatServiceBase* contents = getService(m_currentServiceId);
	// 何も文がないとき
	wxString body = event.GetString();
	if (body == ""){
		return;
	}

	// 未ログインの時
	if (!contents->isUserLogin()){
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
	updateMessageView(m_currentServiceId, contents->getCurrentChannel());
}

// メンバーがダブルクリック
void CMainWindow::onMemberSelected(wxCommandEvent& event)
{
	CChatServiceBase* contents = getService(m_currentServiceId);

	wxString name = contents->getMemberRealName(event.GetString());
	wxMessageBox("本名は" + name + "です");
}

// チャンネル選択時
void CMainWindow::onChannelSelected(CChannelSelectEvent& event)
{
	// 選択したのがサーバ名だったとき
	if (event.isServerSelected()){
		m_currentServiceId = event.getServerId();
		return;
	}

	// サーバーIDとチャンネル名を取得
	wxString channel = event.getString();
	m_currentServiceId = event.getServerId();

	// 選択したコンテンツを取得
	CChatServiceBase* contents = getService(m_currentServiceId);

	// コンテンツの更新
	contents->selectChannel(channel);

	// 画面表示を更新
	wxString ch = contents->getCurrentChannel();
	displayTitle(ch, contents->getTopic(ch));
	updateMessageView(m_currentServiceId, contents->getCurrentChannel());
	updateMemberView(m_currentServiceId, contents->getCurrentChannel());
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
	if (!event.isAuthSucceeded()){
		wxMessageBox("認証に失敗しました");
		m_services.erase(event.getConnectionId());

		return;
	}

	CChatServiceBase* contents = getService(event.getConnectionId());
	// コンテンツの更新
	contents->onAuthSucceeed();

	// 画面表示の更新
	updateAllView(event.getConnectionId(), contents->getCurrentChannel());
}

// メッセージ一覧受信時
void CMainWindow::onGetMessages(CGetMessageEvent& event)
{
	CChatServiceBase* contents = getService(event.getConnectionId());
	// メッセージを追加
	contents->onGetMessages(event.getMessages());

	// 表示の更新
	updateMessageView(event.getConnectionId(), contents->getCurrentChannel());
}

// メンバー一覧受信時
void CMainWindow::onGetMembers(CGetMemberEvent& event)
{
	CChatServiceBase* contents = getService(event.getConnectionId());
	// メンバーの追加
	contents->onGetMembers(event.getMembers());

	// 表示の更新
	updateMemberView(event.getConnectionId(), contents->getCurrentChannel());
}

// チャンネル一覧受信時
void CMainWindow::onGetChannels(CGetChannelEvent& event)
{

	CChatServiceBase* contents = getService(event.getConnectionId());
	// チャンネルの追加
	contents->onGetChannels(event.getChannels());

	// 表示の更新
	updateChannelView(event.getConnectionId(), contents->getCurrentChannel());
	updateMemberView(event.getConnectionId(), contents->getCurrentChannel());
	updateMessageView(event.getConnectionId(), contents->getCurrentChannel());

}
// チャンネル参加時
void CMainWindow::onJoinChannel(CJoinEvent& event)
{
	CChatServiceBase* contents = getService(event.getConnectionId());
	contents->onJoinChannel(event.GetString());
}

// チャンネル離脱時
void CMainWindow::onPartChannel(CPartEvent& event)
{
	CChatServiceBase* contents = getService(event.getConnectionId());

	contents->onPartChannel(event.GetString());

	// 表示の更新
	updateAllView(event.getConnectionId(), contents->getCurrentChannel());
}

// メンバー情報の受信時
void CMainWindow::onGetMemberInfo(CGetMemberInfoEvent& event)
{
	CChatServiceBase* contents = getService(event.getConnectionId());
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
	CChatServiceBase* contents = getService(event.getConnectionId());
	CMessageData data = event.getMessage();
	bool myPost = contents->isPostedThisClient(data);

	contents->onGetMessageStream(data);
	if (!myPost){
		m_logHolder->pushMessageLog(data,
		        contents->getMemberNick(data.m_username));
	}

	// メッセージをログ一覧に表示
	m_view->displayLogs(m_logHolder->getLogs()); // ログペイン
	if (contents->getCurrentChannel() == data.m_channel){
		updateMessageView(event.getConnectionId(), data.m_channel);
	}

	// 通知があったとき && 自分以外の人から
	if (contents->isUserCalled(data.m_body) && !myPost){
		m_view->messageNotify("通知", "呼ばれました");
	}
}

// チャンネル参加ストリーム受信時
void CMainWindow::onJoinStream(CJoinStreamEvent& event)
{
	CChatServiceBase* contents = getService(event.getConnectionId());
	// 処理待ちに追加
	CSubscribeData data(event.getChannelName(), event.getUserName());
	contents->onGetJoinStream(data.m_channel, data.m_username);
	m_logHolder->pushJoinLog(data, contents->getMemberNick(data.m_username));

	// 表示の更新
	m_view->displayLogs(m_logHolder->getLogs()); // ログペイン
	if (data.m_channel == contents->getCurrentChannel()){
		updateMemberView(event.getConnectionId(), data.m_channel);
	}
}

// チャンネル離脱ストリーム受信時
void CMainWindow::onPartStream(CPartStreamEvent& event)
{
	CChatServiceBase* contents = getService(event.getConnectionId());
	CSubscribeData data(event.getChannelName(), event.getUserName());
	wxString name = event.getUserName();
	wxString channel = event.getChannelName();

	// データ更新
	contents->onGetPartStream(channel, name);
	m_logHolder->pushPartLog(data, contents->getMemberNick(data.m_username));

	// 表示の更新
	m_view->displayLogs(m_logHolder->getLogs()); // ログペイン
	if (channel == contents->getCurrentChannel()){
		updateMemberView(event.getConnectionId(), channel);
	}
}

// チャンネル更新ストリーム受信時
void CMainWindow::onChannelStream(CChannelStreamEvent& event)
{
	CChatServiceBase* contents = getService(event.getConnectionId());
	// データ更新
	CChannelData channel = event.getChannel();
	contents->onGetChannelStream(channel);
	m_logHolder->pushTopicLog(channel);

	// 表示の更新
	m_view->displayLogs(m_logHolder->getLogs()); // ログペイン

	// 現在のチャンネルならばタイトルを更新
	if (channel.m_name == contents->getCurrentChannel()){
		displayTitle(channel.m_name, channel.m_topic);
	}
}

// ユーザ情報更新ストリーム受信時
void CMainWindow::onUserStream(CUserStreamEvent& event)
{
	CChatServiceBase* contents = getService(event.getConnectionId());
	// データ更新
	CMemberData member = event.getMember();
	contents->onGetUserStream(member);
	m_logHolder->pushChangeNickLog(member);

	// 表示の更新
	updateMemberView(event.getConnectionId(), contents->getCurrentChannel()); // メンバーペイン
	updateMessageView(event.getConnectionId(), contents->getCurrentChannel()); // メッセージペイン
	m_view->displayLogs(m_logHolder->getLogs()); // ログペイン
}
