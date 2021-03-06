﻿#include "MainPanel.hpp"

using namespace std;

namespace CornStarch
{;

CMainPanel::CMainPanel(void) :
		m_msgPane(NULL), m_memBox(NULL), m_cnBox(NULL), m_postPane(NULL), m_recordPane(
		        NULL)
{
}

CMainPanel::~CMainPanel(void)
{
}

//////////////////////////////////////////////////////////////////////

// 初期化を行う
void CMainPanel::init(wxWindow* parent)
{
	// 分割ウィンドウを作成する
	CSplitPanel::init(parent);

	// メッセージ表示ペインの初期化
	if (m_msgPane == NULL){
		m_msgPane = new CPaneMsg();
		m_msgPane->init(getMsgPane());
	}

	// メンバー表示ペインの初期化
	if (m_memBox == NULL){
		m_memBox = new CPaneMember();
		m_memBox->init(getMemPane());
	}

	// チャンネル表示ペインの初期化
	if (m_cnBox == NULL){
		m_cnBox = new CPaneCn();
		m_cnBox->init(getCnPane());
	}

	// メッセージ投稿ペインの初期化
	if (m_postPane == NULL){
		m_postPane = new CPanePost();
		m_postPane->init(getPostPane());
	}

	// メッセージ一覧表示ペインの初期化
	if (m_recordPane == NULL){
		m_recordPane = new CPaneRecord();
		m_recordPane->init(getRecordPane());
	}

	// 分割ウィンドウにセットする
	split();

}

// メッセージペインにメッセージを表示
void CMainPanel::displayMessages(const vector<CMessageData*>& messages,
        const map<wxString, wxString>& nickTable)
{
	m_msgPane->Show(false);
	m_msgPane->displayMessages(messages, nickTable);
	m_msgPane->Show(true);

}
void CMainPanel::addMessage(const CMessageData* message,
      const std::map<wxString, wxString>& nickTable)
{
    m_msgPane->addMessage(message,nickTable);
    m_msgPane->clearUnreadBackgroundColor();
}

void CMainPanel::addUnreadMessage(const CMessageData* message)
{
    m_cnBox->addUnreadMessage(message);
}
// メンバーペインにメンバーを表示
void CMainPanel::displayMembers(const vector<CMemberData*>& members)
{
	m_memBox->Show(false);
	m_memBox->displayMembers(members);
	m_memBox->Show(true);
}

// チャンネルペインにチャンネルを表示
void CMainPanel::displayChannels(
        const std::map<int, CChatServiceBase*>& services)
{
	m_cnBox->Show(false);
	m_cnBox->displayChannels(services);
	m_cnBox->Show(true);

}

// メッセージペインをクリアする。
void CMainPanel::clearMessages(void)
{
	m_msgPane->Clear();
}

// メンバーペインをクリアする
void CMainPanel::clearMembers(void)
{
	m_memBox->Clear();
}

// チャンネルペインをクリアする
void CMainPanel::clearChannels(void)
{
	wxTreeItemId rootId = m_cnBox->GetRootItem();
	m_cnBox->DeleteChildren(rootId);
}

// ログ一覧ペインにログを表示
void CMainPanel::displayLogs(const std::vector<CChatLog*>& logs)
{
	m_recordPane->displayLogs(logs);
}

//////////////////////////////////////////////////////////////////////

// 投稿ペインの文字列をクリアする
void CMainPanel::clearPostPaneText(void)
{
	m_postPane->SetValue(wxEmptyString);
}

// 選択済みチャンネルを決める
void CMainPanel::setSelectedChannel(const wxString& channel)
{
	m_cnBox->setStringSelection(channel);
}

// 投稿ペインのIDを取得する
wxWindowID CMainPanel::getPostPaneID(void) const
{
	return m_postPane->GetId();
}

// チャンネルペインのIDを取得する
wxWindowID CMainPanel::getCnPaneID(void) const
{
	return m_cnBox->GetId();
}

// メンバーペインのIDを取得する
wxWindowID CMainPanel::getMemPaneID(void) const
{
	return m_memBox->GetId();
}

//////////////////////////////////////////////////////////////////////

// 画面分割を行う
void CMainPanel::split(void)
{
	m_spMsg->SplitHorizontally(m_msgPane, m_postPane);
	m_spHorL->SplitHorizontally(m_spMsg, m_recordPane);
	m_spHorR->SplitHorizontally(m_memBox, m_cnBox);
	this->SplitVertically(m_spHorL, m_spHorR);
}

}
