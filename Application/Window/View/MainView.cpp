#include "MainView.hpp"

using namespace std;

namespace CornStarch
{
;

CMainView::CMainView(void) :
        m_menuBar(NULL), m_panel(NULL), m_dialog(NULL), m_notifier(NULL)
{
}

CMainView::~CMainView(void)
{
    delete m_dialog;
    delete m_notifier;
}

//////////////////////////////////////////////////////////////////////

// 初期化を行う
void CMainView::init(wxWindow* parent)
{
    // メニューバーを初期化
    if (m_menuBar == NULL){
        m_menuBar = new CMainMenuBar();
        m_menuBar->init();
    }

    // 画面パネルを初期化
    if (m_panel == NULL){
        m_panel = new CMainPanel();
        m_panel->init(parent);
    }

    // ダイアログを初期化
    if (m_dialog == NULL){
        m_dialog = new CViewDialog();
        m_dialog->init(parent);
    }

    // 通知クラスを初期化
    if (m_notifier == NULL){
        m_notifier = new CMainNotifier();
        m_notifier->init();
    }
}

//////////////////////////////////////////////////////////////////////

// 投稿ペインのIDを取得する
wxWindowID CMainView::getPostPaneID(void) const
{
    return m_panel->getPostPaneID();
}

// チャンネルペインのIDを取得する
wxWindowID CMainView::getCnPaneID(void) const
{
    return m_panel->getCnPaneID();
}

// メンバーペインのIDを取得する
wxWindowID CMainView::getMemPaneID(void) const
{
    return m_panel->getMemPaneID();
}

// 指定したチャンネルを選択済み項目にする
void CMainView::setSelectedChannel(const wxString& channelName)
{
    m_panel->setSelectedChannel(channelName);
}

// メッセージ一覧を表示する
void CMainView::displayMessages(const vector<CMessageData*>& messages,
        const map<wxString, wxString>& nickTable)
{
    m_panel->displayMessages(messages, nickTable);
}
void CMainView::addMessage(const CMessageData* message,
        const std::map<wxString, wxString>& nickTable)
{
    m_panel->addMessage(message, nickTable);
}

void CMainView::addUnreadMessage(const CMessageData* message)
{
    m_panel->addUnreadMessage(message);
}

// メンバー一覧を表示する
void CMainView::displayMembers(const vector<CMemberData*>& members)
{
    m_panel->displayMembers(members);
}

// チャンネル一覧を表示する
void CMainView::displayChannels(
        const std::map<int, CChatServiceBase*>& services)
{
    m_panel->displayChannels(services);
}

// 投稿用ペインの文字を消す
void CMainView::clearPostPaneText(void)
{
    m_panel->clearPostPaneText();
}

// ログ一覧にログを表示する
void CMainView::displayLogs(const std::vector<CChatLog*>& logs)
{
    m_panel->displayLogs(logs);
}

// メッセージ一覧をクリアします。
void CMainView::clearMessages(void)
{
    m_panel->clearMessages();
}

// メンバー一覧をクリアします。
void CMainView::clearMembers(void)
{
    m_panel->clearMembers();
}

// チャンネル一覧をクリアします。
void CMainView::clearChannels(void)
{
    m_panel->clearChannels();
}

//////////////////////////////////////////////////////////////////////

// メニューバーを取得する
CMainMenuBar* CMainView::getMenuBar(void) const
{
    return m_menuBar;
}

//////////////////////////////////////////////////////////////////////

// メッセージボックスを表示する
void CMainView::showMsgBox(const wxString& message)
{
    wxMessageBox(message);
}

// 認証ダイアログを表示する(SC)
int CMainView::showModalAuthDlg(void)
{
    return m_dialog->showModalAuthDlg();
}

// チャンネル名指定用ダイアログを表示する
int CMainView::showModalChannelDlg(void)
{
    return m_dialog->showModalChannelDlg();
}

// ニックネーム変更ダイアログを表示
int CMainView::showModalNickDlg(void)
{
    return m_dialog->showModalNickDlg();
}

// トピック変更ダイアログを表示
int CMainView::showModalTopicDlg(void)
{
    return m_dialog->showModalTopicDlg();
}
CChatServiceBase* CMainView::getNewServiceFromDialog(void) const
{
    return m_dialog->getNewServiceFromDialog();
}
// チャンネル名を取得する
wxString CMainView::getDlgChannelName(void) const
{
    return m_dialog->getChannelName();
}

// ニックネームを取得
wxString CMainView::getNickName(void) const
{
    return m_dialog->getNickName();
}

// トピック名を取得
wxString CMainView::getTopic(void) const
{
    return m_dialog->getTopic();
}

//////////////////////////////////////////////////////////////////////

// メッセージを通知する
void CMainView::messageNotify(const wxString& title, const wxString& message)
{
    m_notifier->messageNotify(title, message);
}

}
