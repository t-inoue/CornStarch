#include "ViewDialog.hpp"

namespace CornStarch
{
;

CViewDialog::CViewDialog(void) :
        m_authDlg(NULL), m_channelDlg(NULL)//, m_cancelAuthDlg(NULL)
{
}

CViewDialog::~CViewDialog(void)
{
}

//////////////////////////////////////////////////////////////////////

// 初期化を行う
void CViewDialog::init(wxWindow* parent)
{
    m_parent = parent;
}

// チャンネル名指定用ダイアログを表示
int CViewDialog::showModalChannelDlg(void)
{
    m_channelDlg = new CChannelDialog();
    m_channelDlg->init(m_parent, "チャンネル名を指定");
    return m_channelDlg->ShowModal();
}

// サーバー追加ダイアログを表示(SC)
int CViewDialog::showModalAuthDlg(void)
{
    m_authDlg = new CAuthDialog();
    m_authDlg->init(m_parent, "サーバー登録");
    return m_authDlg->ShowModal();
}


// ニックネーム変更ダイアログを表示
int CViewDialog::showModalNickDlg(void)
{
    m_nickDlg = new CNickChangeDialog();
    m_nickDlg->init(m_parent, "ニックネームを指定");
    return m_nickDlg->ShowModal();
}

// トピック変更ダイアログを表示
int CViewDialog::showModalTopicDlg(void)
{
    m_topicDlg = new CChangeTopicDialog();
    m_topicDlg->init(m_parent, "トピックを指定");
    return m_topicDlg->ShowModal();
}
CChatServiceBase* CViewDialog::getNewServiceFromDialog(void) const
{
    return m_authDlg->getNewService();
}

// チャンネル名を取得
wxString CViewDialog::getChannelName(void) const
{
    return m_channelDlg->getChannelName();
}


// ニックネームを取得
wxString CViewDialog::getNickName(void) const
{
    return m_nickDlg->getNickName();
}

// トピック名を取得
wxString CViewDialog::getTopic(void) const
{
    return m_topicDlg->getTopic();
}

}
