#include "DefineEventTable.hpp" // イベントテーブル
#include "MainWindow.hpp"

using namespace std;

namespace CornStarch
{
;

//////////////////////////////////////////////////////////////////////

CMainWindow::CMainWindow(void) :
        m_view(NULL), m_logHolder(NULL), m_serialize(NULL), m_uniqueServiceId(
                0), m_currentServiceId(0)
{
}

CMainWindow::~CMainWindow(void)
{
    // ファイルに保存
    m_serialize->saveService(m_services);

    delete m_view;
    delete m_logHolder;
    delete m_serialize;

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

    // シリアライズされたサービスを読み込み
    m_serialize = new CServiceSerializer();
    m_serialize->init();
    m_serialize->loadService(GetEventHandler(), m_services, m_uniqueServiceId);

}

//////////////////////////////////////////////////////////////////////

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
        CChatServiceBase* service = getService(connectionId);
        service->onUpdateMessageView(channel);

        // メッセージを表示
        m_view->displayMessages(service->getMessages(channel),
                service->getNickTable());
    }
}

// メンバー画面を更新する(Modelがある場合)
void CMainWindow::updateMemberView(int connectionId, const wxString& channel)
{
    if (connectionId == m_currentServiceId){
        CChatServiceBase* service = getService(connectionId);
        service->onUpdateMemberView(channel);

        // メンバーを表示
        m_view->displayMembers(service->getMembers(channel));
    }
}

// チャンネル画面とタイトルバーを更新する(Modelがある場合)
void CMainWindow::updateChannelView(int connectionId, const wxString& channel)
{
    CChatServiceBase* service = getService(connectionId);
    service->onUpdateChannelView();

    // チャンネルを表示
    displayTitle(channel, service->getTopic(channel), connectionId);
    m_view->displayChannels(m_services);
    m_view->setSelectedChannel(service->getCurrentChannel());
}

// タイトルバーにタイトルを表示する
void CMainWindow::displayTitle(const wxString& channel, const wxString& topic,
        int serviceId)
{
    // 現在見ているサーバではなかったら
    if (serviceId != m_currentServiceId){
        return;
    }

    CChatServiceBase* service = getService(serviceId);

    // チャンネル名が空の時、サーバ名を表示
    if (channel == ""){
        SetTitle(
                "(" + service->getNickName() + ")<" + service->getHost() + ">");
        return;
    }

    // 改行を消してタイトルを表示
    wxString tpc = topic;
    tpc.Replace("\r\n", " ");
    tpc.Replace("\n", " ");
    this->SetTitle("(" + service->getNickName() + ")【" + channel + "】" + tpc);
}

// すべての画面をクリアする。
void CMainWindow::clearAllView()
{
    m_view->clearChannels();
    m_view->clearMembers();
    m_view->clearMessages();
}

// IDからサービスを取得する
CChatServiceBase* CMainWindow::getService(int serviceId)
{
    map<int, CChatServiceBase*>::iterator it = m_services.find(serviceId);
    if (it != m_services.end()){
        return (*it).second;
    }
    return NULL;
}

//////////////////////////////////////////////////////////////////////

// 終了
void CMainWindow::onQuit(wxCommandEvent& event)
{
    Close(true);
}

// サービス登録
void CMainWindow::onServiceRegister(wxCommandEvent& event)
{
    // 認証ダイアログを表示
    if (m_view->showModalAuthDlg() != wxID_OK){
        return;
    }
    // ここでIRCサーバの追加を行う
    CChatServiceBase* contents = m_view->getNewServiceFromDialog();
    if (contents != NULL){
        addNewService(contents);
    }
}

void CMainWindow::addNewService(CChatServiceBase* service)
{
    service->setId(m_uniqueServiceId);
    m_uniqueServiceId++;
    service->init(GetEventHandler());
    m_services.insert(
            map<int, CChatServiceBase*>::value_type(service->getId(), service));

    service->connect();
}

// チャンネルに参加メニュー
void CMainWindow::onJoin(wxCommandEvent& event)
{
    showAddChannleDialog(m_currentServiceId);
}

// サーバー削除
void CMainWindow::onDeleteService(wxCommandEvent& event)
{
    deleteService(m_currentServiceId);
}

// チャンネルから離脱メニュー
void CMainWindow::onPart(wxCommandEvent& event)
{
    CChatServiceBase* contents = getService(m_currentServiceId);
    if (contents == NULL){
        return;
    }

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
    updateService(m_currentServiceId);
}

void CMainWindow::updateService(int serviceId)
{
    CChatServiceBase* service = getService(serviceId);
    if (service != NULL){
        //　再接続
        service->reconnect();
        service->clearChannels();
        service->clearNickTable();

        // 表示を更新
        if (serviceId == m_currentServiceId){
            updateAllView(m_currentServiceId, service->getCurrentChannel());
        } else{
            m_view->displayChannels(m_services);
        }
    }
}
// サービスを切断する
void CMainWindow::disconnect(int serviceId)
{
    CChatServiceBase* service = getService(serviceId);
    if (service != NULL){
        service->disconnect();
        m_view->displayChannels(m_services);
    }
}
// ニックネーム変更
void CMainWindow::onNickChange(wxCommandEvent& event)
{
    showChangeNicknameDialog(m_currentServiceId);
}

// トピック変更
void CMainWindow::onChangeTopic(wxCommandEvent& event)
{
    showChangeTopicDialog(m_currentServiceId);
}

//////////////////////////////////////////////////////////////////////

// 投稿ペインでEnterキーを押下
void CMainWindow::onEnter(wxCommandEvent& event)
{
    CChatServiceBase* contents = getService(m_currentServiceId);

    if (contents == NULL || contents->getCurrentChannel() == ""
            || contents->IsConnected() == false){
        return;
    }

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

    m_view->addMessage(&message, contents->getNickTable());
}

// メンバーがダブルクリック
void CMainWindow::onMemberSelected(wxCommandEvent& event)
{
    CChatServiceBase* contents = getService(m_currentServiceId);

    wxString name = contents->getMemberRealName(event.GetString());
    wxMessageBox("名前：" + name, event.GetString() + "のユーザ情報");
}

// チャンネル選択時
void CMainWindow::onChannelSelected(CChannelSelectEvent& event)
{

    // 選択したコンテンツを取得
    CChatServiceBase* contents = getService(event.getServerId());
    // 選択したのがサーバ名だったとき
    if (event.isServerSelected()){
        m_currentServiceId = event.getServerId();
        m_view->clearMessages();
        m_view->clearMembers();
        displayTitle("", "", m_currentServiceId);

        contents->selectChannel("");
        return;
    }

    // サーバーIDとチャンネル名を取得
    wxString channel = event.getChannelName();
    m_currentServiceId = event.getServerId();

    // コンテンツの更新
    contents->selectChannel(channel);

    // 画面表示を更新
    wxString ch = channel;
    displayTitle(ch, contents->getTopic(ch), event.getServerId());
    updateMessageView(m_currentServiceId, contents->getCurrentChannel());
    updateMemberView(m_currentServiceId, contents->getCurrentChannel());
}

// チャンネルペインを右クリック時
void CMainWindow::onChannelRightClicked(CChannelSelectEvent& event)
{
    enum
    {
        Id_DeleteServer = 1, Id_AddChannel = 2, Id_DeleteChannel = 3,
        Id_ChangeTopic = 4, Id_ChangeNickname = 5, Id_Refresh = 6,
        Id_Disconnect = 7
    };

    int serviceId = event.getServerId();
    CChatServiceBase* service = getService(serviceId);

    wxMenu menu;
    menu.Append(Id_DeleteServer, "サーバの削除");
    menu.Append(Id_Refresh, "サーバの再読み込み");
    if (service->IsConnected()){
        menu.Append(Id_Disconnect, "サーバの切断");
        menu.AppendSeparator();
        menu.Append(Id_AddChannel, "チャンネルの追加");
        if (event.isServerSelected() == false){
            menu.Append(Id_DeleteChannel, "チャンネルの削除");
            menu.Append(Id_ChangeTopic, "トピックの変更");
        }
        menu.Append(Id_ChangeNickname, "ニックネームの変更");
    }

    wxString channel = event.getChannelName();
    switch (this->GetPopupMenuSelectionFromUser(menu)) {
    case Id_DeleteServer:
        deleteService(serviceId);
        break;
    case Id_AddChannel:
        showAddChannleDialog(serviceId);
        break;
    case Id_DeleteChannel:
        deleteChannel(serviceId, channel);
        break;
    case Id_ChangeTopic:
        showChangeTopicDialog(serviceId);
        break;
    case Id_ChangeNickname:
        showChangeNicknameDialog(serviceId);
        break;
    case Id_Refresh:
        updateService(serviceId);
        break;
    case Id_Disconnect:
        disconnect(serviceId);
        break;
    }
}

//////////////////////////////////////////////////////////////////////

// メッセージ投稿終了時
void CMainWindow::onFinishPostMessage(wxThreadEvent& event)
{
}

// 認証情報の受信時
void CMainWindow::onGetAuth(CAuthEvent& event)
{
    // サービスIDが不明な場合
    CChatServiceBase* service = getService(event.getConnectionId());
    if (service == NULL){
        return;
    }

    // 認証に失敗
    if (!event.isAuthSucceeded()){

        wxMessageBox("接続に失敗しました");

        // サービスの削除
        m_services.erase(event.getConnectionId());
        delete service;

        // 表示の更新
        m_view->displayChannels(m_services);

    } else{
        // コンテンツの更新
        service->onAuthSucceeed();
        service->setConnected(true);

        // 表示の更新
        updateAllView(event.getConnectionId(), service->getCurrentChannel());
    }

}

// 切断情報の受信時
void CMainWindow::onDisconnect(CDisconnectEvent& event)
{
    CChatServiceBase* service = getService(event.getConnectionId());
    if (service != NULL){
        disconnect(event.getConnectionId());
        wxMessageBox(
                wxString::Format(wxT("サーバー[%s]切断されました。再接続を行う際は更新してください。"),
                        service->getHost()));

    }
}
// メッセージ一覧受信時
void CMainWindow::onGetMessages(CGetMessageEvent& event)
{
    CChatServiceBase* contents = getService(event.getConnectionId());
    if (contents != NULL){
        // メッセージを追加
        contents->onGetMessages(event.getMessages());

        // 表示の更新
        updateMessageView(event.getConnectionId(),
                contents->getCurrentChannel());
    }
}

// メンバー一覧受信時
void CMainWindow::onGetMembers(CGetMemberEvent& event)
{
    CChatServiceBase* contents = getService(event.getConnectionId());
    if (contents != NULL){
        // メンバーの追加
        contents->onGetMembers(event.getMembers());
        if (m_currentServiceId == event.getConnectionId()
                && contents->getCurrentChannel() == event.getChannel()){
            // 表示の更新
            updateMemberView(event.getConnectionId(),
                    contents->getCurrentChannel());
        }
    }
}

// チャンネル一覧受信時
void CMainWindow::onGetChannels(CGetChannelEvent& event)
{
    CChatServiceBase* contents = getService(event.getConnectionId());
    if (contents != NULL){
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
    CChatServiceBase* service = getService(event.getConnectionId());
    CMessageData data = event.getMessage();
    bool myPost = service->isPostedThisClient(data);

    service->onGetMessageStream(data);
    if (!myPost){
        m_logHolder->pushMessageLog(data,
                service->getMemberNick(data.m_username));
    }

    // メッセージをログ一覧に表示
    m_view->displayLogs(m_logHolder->getLogs()); // ログペイン
    if (service->getCurrentChannel() == data.m_channel){
        // メッセージを表示
        m_view->addMessage(&data, service->getNickTable());
        //updateMessageView(event.getConnectionId(), data.m_channel);
    }

    // 通知があったとき && 自分以外の人から
    if (service->isUserCalled(data.m_body) && !myPost){
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
    if (contents != NULL){
        CSubscribeData data(event.getChannelName(), event.getUserName());
        wxString name = event.getUserName();
        wxString channel = event.getChannelName();

        // データ更新
        contents->onGetPartStream(channel, name);
        m_logHolder->pushPartLog(data,
                contents->getMemberNick(data.m_username));

        // 表示の更新
        m_view->displayLogs(m_logHolder->getLogs()); // ログペイン
        if (channel == contents->getCurrentChannel() || channel == ""){
            updateMemberView(event.getConnectionId(),
                    contents->getCurrentChannel());
        }
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
        displayTitle(channel.m_name, channel.m_topic, event.getConnectionId());
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
    wxString ch = contents->getCurrentChannel();
    displayTitle(ch, contents->getTopic(ch), event.getConnectionId());
    updateMemberView(event.getConnectionId(), contents->getCurrentChannel()); // メンバーペイン
    updateMessageView(event.getConnectionId(), contents->getCurrentChannel()); // メッセージペイン
    m_view->displayLogs(m_logHolder->getLogs()); // ログペイン
}
// チャンネル更新ストリーム受信時
void CMainWindow::onInvite(CInviteEvent& event)
{

    CChatServiceBase* service = getService(event.getConnectionId());
    if (service != NULL){
        m_logHolder->pushInviteLog(event.getChannel(), event.getUser());
        // 表示の更新
        m_view->displayLogs(m_logHolder->getLogs()); // ログペイン

        wxMessageDialog dialog(this,
                wxString::Format(wxT("チャンネル[%s]に招待されました。参加しますか？"),
                        event.getChannel()), "確認", wxOK | wxCANCEL);
        if (dialog.ShowModal() == wxID_OK){
            service->joinChannel(event.getChannel());
        }
    }

}

// ユーザ情報更新ストリーム受信時
void CMainWindow::onKick(CKickEvent& event)
{
    CChatServiceBase* service = getService(event.getConnectionId());
    if (service != NULL){
        if (event.getUser() == service->getUserName()){
            wxMessageDialog dialog(this,
                    wxString::Format(wxT("チャンネル[%s]からキックされました。"),
                            event.getChannel()), "確認", wxOK);
            if (dialog.ShowModal() == wxID_OK){
                service->partChannel(event.getChannel());
            }
        } else{
            service->onGetPartStream(event.getChannel(), event.getUser());
            m_logHolder->pushKickLog(event.getChannel(), event.getUser());
            updateMemberView(event.getConnectionId(), event.getChannel());
            // 表示の更新
            m_view->displayLogs(m_logHolder->getLogs()); // ログペイン
        }
    }
}

// サービスを削除する。
void CMainWindow::deleteService(int serviceId)
{
    CChatServiceBase* service = getService(serviceId);
    if (service != NULL){
        wxMessageDialog dialog(this,
                wxString::Format(wxT("サーバー[%s]の削除をしてもよろしいですか？"),
                        service->getHost()), "確認", wxOK | wxCANCEL);

        if (dialog.ShowModal() == wxID_OK){
            delete service;
            m_services.erase(serviceId);
            // 画面表示の更新
            clearAllView();
            m_view->displayChannels(m_services);
        }
    }
}

// チャンネルを削除する
void CMainWindow::deleteChannel(int serviceId, wxString channel)
{
    CChatServiceBase* contents = getService(serviceId);
    if (contents != NULL){
        contents->partChannel(channel);
    }
}

// チャンネル追加ダイアログを表示する
void CMainWindow::showAddChannleDialog(int serviceId)
{
    CChatServiceBase* contents = getService(serviceId);
    if (contents == NULL){
        return;
    }
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

// トピック変更ダイアログを表示する
void CMainWindow::showChangeTopicDialog(int serviceId)
{
    // 未ログインの時
    CChatServiceBase* contents = getService(m_currentServiceId);

    if (contents == NULL){
        return;
    }

    if (!contents->isUserLogin()){
        return;
    }
    if (contents->getCurrentChannel() == ""){
        return;
    }
    // トピック変更ダイアログを表示
    if (m_view->showModalTopicDlg() != wxID_OK){
        return;
    }

    // データ更新
    contents->onChangeTopic(m_view->getTopic());
}

// ニックネーム変更ダイアログを表示する。
void CMainWindow::showChangeNicknameDialog(int serviceId)
{ // 未ログインの時
    CChatServiceBase* contents = getService(serviceId);
    if (contents == NULL){
        return;
    }
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

}
