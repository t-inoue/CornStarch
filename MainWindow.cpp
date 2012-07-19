#include "DefineEventTable.hpp" // イベントテーブル
#include "MainWindow.hpp"
#include "SCConnectionContents.h"
#include "IRCConnectionContents.h"

using namespace std;


//////////////////////////////////////////////////////////////////////


CMainWindow::CMainWindow(void) : m_view(NULL), m_logHolder(NULL),
    m_contents(NULL)
{
}


CMainWindow::~CMainWindow(void)
{
    delete m_view;
    delete m_logHolder;

    delete m_contents;
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

	// StarChatコンテンツの初期化
	m_contents = new CornStarch::IRC::CIRCConnectionContents();//new CSCConnectionContents();//
	m_contents->init(GetEventHandler());

    // イベントハンドラの初期化
    initHandle();
}


//////////////////////////////////////////////////////////////////////


// 画面操作に関するイベントハンドラを設定する
void CMainWindow::initHandle(void)
{
    // エンターキー押下時
    this->Connect(m_view->getPostPaneID(), wxEVT_COMMAND_TEXT_ENTER,
        wxCommandEventHandler(CMainWindow::onEnter));

    // チャンネルリスト選択時
    this->Connect(m_view->getCnPaneID(), wxEVT_COMMAND_LISTBOX_SELECTED,
        wxCommandEventHandler(CMainWindow::onChannel));
}

// Modelがあれば画面を更新する
void CMainWindow::updateAllView(const wxString& channel)
{
    updateMessageView(channel);
    updateMemberView(channel);
    updateChannelView(channel);
}

// メッセージ画面を更新する(Modelがある場合)
void CMainWindow::updateMessageView(const wxString& channel)
{
    m_contents->onUpdateMessageView(channel);

    // メッセージを表示
    m_view->displayMessages(m_contents->getMessages(channel), m_contents->getNickTable());
}

// メンバー画面を更新する(Modelがある場合)
void CMainWindow::updateMemberView(const wxString& channel)
{
    m_contents->onUpdateMemberView(channel);

    // メンバーを表示
    m_view->displayMembers(m_contents->getMembers(channel));
    m_view->displayMessages(m_contents->getMessages(channel), m_contents->getNickTable());
}

// チャンネル画面とタイトルバーを更新する(Modelがある場合)
void CMainWindow::updateChannelView(const wxString& channel)
{
    m_contents->onUpdateChannelView();

    // チャンネルを表示
    displayTitle(channel, m_contents->getTopic(channel));
    m_view->displayChannels(m_contents->getChannels());
    m_view->setSelectedChannel(m_contents->getCurrentChannel());
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

// ユーザ登録
void CMainWindow::onRegister(wxCommandEvent& event)
{
    // ログイン済みの時
    if (m_contents->isUserLogin()){
        wxMessageBox("ログイン済みです");
        return;
    }

    // 認証ダイアログを表示
    if (m_view->showModalAuthDlg() != wxID_OK){
        return;
    }

    // コンテンツを更新
    m_contents->registerUser(m_view->getDlgUserNameAsString(), m_view->getDlgPasswordAsString());
}

// ログアウトメニュー
void CMainWindow::onLogout(wxCommandEvent& event)
{
    // 永続化している情報を削除
    m_contents->logout();
    Close();
}

// チャンネルに参加メニュー
void CMainWindow::onJoin(wxCommandEvent& event)
{
    // 未ログインの時
    if (!m_contents->isUserLogin()){
        return;
    }

    // ダイアログを表示
    if (m_view->showModalChannelDlg() != wxID_OK){
        return;
    }

    // チャンネル参加タスクの開始
    m_contents->joinChannel(m_view->getDlgChannelNameAsString());
}

// チャンネルから離脱メニュー
void CMainWindow::onPart(wxCommandEvent& event)
{
    // 未ログインの時
    if (!m_contents->isUserLogin()){
        return;
    }

    // ダイアログを表示
    if (m_view->showModalChannelDlg() != wxID_OK){
        return;
    }

    // チャンネル離脱タスクを開始
    m_contents->partChannel(m_view->getDlgChannelNameAsString());
}

// 表示を更新
void CMainWindow::onUpdateDisplay(wxCommandEvent& event)
{
    // 保持しているデータを初期化
    m_contents->reconnect();
    m_contents->clearChannels();
    m_contents->clearNickTable();

    // 表示を更新
    updateAllView(m_contents->getCurrentChannel());
}


//////////////////////////////////////////////////////////////////////


// 投稿ペインでEnterキーを押下
void CMainWindow::onEnter(wxCommandEvent& event)
{
    // 何も文がないとき
    wxString body = event.GetString();
    if (body == ""){
        return;
    }

    // 未ログインの時
    if (!m_contents->isUserLogin()){
        m_view->clearPostPaneText();
        return;
    }

    // コンテンツの更新
    CMessageData message = m_contents->generateMessage(body);
    m_contents->postMessage(message);
    m_logHolder->pushMessageLog(message, m_contents->getNickName());

    // 表示の更新
    m_view->clearPostPaneText();
    m_view->displayLogs(m_logHolder->getLogs());
    updateMessageView(m_contents->getCurrentChannel());
}

// チャンネル選択時
void CMainWindow::onChannel(wxCommandEvent& event)
{
    // コンテンツの更新
    m_contents->selectChannel(event.GetString());

    // 画面表示を更新
    wxString ch = m_contents->getCurrentChannel();
    displayTitle(ch, m_contents->getTopic(ch));
    updateMessageView(m_contents->getCurrentChannel());
    updateMemberView(m_contents->getCurrentChannel());
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
        return;
    }

    // コンテンツの更新
    m_contents->onAuthSucceeed();

    // 画面表示の更新
    updateAllView(m_contents->getCurrentChannel());
}

// メッセージ一覧受信時
void CMainWindow::onGetMessages(CGetMessageEvent& event)
{
    // メッセージを追加
    m_contents->onGetMessages(event.getMessages());

    // 表示の更新
    updateMessageView(m_contents->getCurrentChannel());
}

// メンバー一覧受信時
void CMainWindow::onGetMembers(CGetMemberEvent& event)
{
    // メンバーの追加
    m_contents->onGetMembers(event.getMembers());

    // 表示の更新
    updateMemberView(m_contents->getCurrentChannel());
}

// チャンネル一覧受信時
void CMainWindow::onGetChannels(CGetChannelEvent& event)
{
    // チャンネルの追加
    m_contents->onGetChannels(event.getChannels());

    // 表示の更新
    updateChannelView(m_contents->getCurrentChannel());
    updateMemberView(m_contents->getCurrentChannel());
    updateMessageView(m_contents->getCurrentChannel());
}

// チャンネル参加時
void CMainWindow::onJoinChannel(CJoinEvent& event)
{
    m_contents->onJoinChannel(event.GetString());
}

// チャンネル離脱時
void CMainWindow::onPartChannel(wxThreadEvent& event)
{
    m_contents->onPartChannel(event.GetString());

    // 表示の更新
    updateAllView(m_contents->getCurrentChannel());
}

// メンバー情報の受信時
void CMainWindow::onGetMemberInfo(CGetMemberInfoEvent& event)
{
    // データ更新
    CMemberData data = event.getMember();
    m_contents->onGetMemberStatus(data);
    m_logHolder->onUpdateNickName(data);

    // 表示を更新
    updateMemberView(m_contents->getCurrentChannel());
    updateMessageView(m_contents->getCurrentChannel());
    m_view->displayLogs(m_logHolder->getLogs());
}

// メッセージストリーム受信時
void CMainWindow::onMsgStream(CMsgStreamEvent& event)
{
    CMessageData data = event.getMessage();
    bool myPost = m_contents->isPostedThisClient(data);

    m_contents->onGetMessageStream(data);
    if (!myPost){
        m_logHolder->pushMessageLog(data, m_contents->getMemberNick(data.m_username));
    }

    // メッセージをログ一覧に表示
    m_view->displayLogs(m_logHolder->getLogs()); // ログペイン
    if (m_contents->getCurrentChannel() == data.m_channel){
        updateMessageView(data.m_channel);
    }

    // 通知があったとき && 自分以外の人から
    if (m_contents->isUserCalled(data.m_body) && !myPost){
        wxMessageBox("通知", "呼ばれました", wxOK);
    }
}

// チャンネル参加ストリーム受信時
void CMainWindow::onJoinStream(CJoinStreamEvent& event)
{
    // 処理待ちに追加
    CSubscribeData data (event.getChannelName(), event.getUserName());
    m_contents->onGetJoinStream(data.m_channel, data.m_username);
    m_logHolder->pushJoinLog(data, m_contents->getMemberNick(data.m_username));

    // 表示の更新
    m_view->displayLogs(m_logHolder->getLogs()); // ログペイン
    if (data.m_channel == m_contents->getCurrentChannel()){
        updateMemberView(data.m_channel);
    }
}

// チャンネル離脱ストリーム受信時
void CMainWindow::onPartStream(CPartStreamEvent& event)
{
    CSubscribeData data (event.getChannelName(), event.getUserName());
    wxString name = event.getUserName();
    wxString channel = event.getChannelName();

    // データ更新
    m_contents->onGetPartStream(channel, name);
    m_logHolder->pushPartLog(data, m_contents->getMemberNick(data.m_username));

    // 表示の更新
    m_view->displayLogs(m_logHolder->getLogs()); // ログペイン
    if (channel == m_contents->getCurrentChannel()){
        updateMemberView(channel);
    }
}

// チャンネル更新ストリーム受信時
void CMainWindow::onChannelStream(CChannelStreamEvent& event)
{
    // データ更新
    CChannelData channel = event.getChannel();
    m_contents->onGetChannelStream(channel);
    m_logHolder->pushTopicLog(channel);

    // 表示の更新
    m_view->displayLogs(m_logHolder->getLogs()); // ログペイン

    // 現在のチャンネルならばタイトルを更新
    if (channel.m_name == m_contents->getCurrentChannel()){
        displayTitle(channel.m_name, channel.m_topic);
    }
}

// ユーザ情報更新ストリーム受信時
void CMainWindow::onUserStream(CUserStreamEvent& event)
{
    // データ更新
    CMemberData member = event.getMember();
    m_contents->onGetUserStream(member);
    m_logHolder->pushChangeNickLog(member);

    // 表示の更新
    updateMemberView(m_contents->getCurrentChannel()); // メンバーペイン
    updateMessageView(m_contents->getCurrentChannel()); // メッセージペイン
    m_view->displayLogs(m_logHolder->getLogs()); // ログペイン
}
