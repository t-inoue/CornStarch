#include "ViewDialog.hpp"


CViewDialog::CViewDialog(void)
    : m_authDlg(NULL), m_channelDlg(NULL), m_cancelAuthDlg(NULL)
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

// ユーザ認証ダイアログを表示
int CViewDialog::showModalAuthDlg(void)
{
    m_authDlg = new CAuthDialog();
    m_authDlg->init(m_parent, "ユーザ認証");
    return m_authDlg->ShowModal();
}

// ユーザ認証キャンセル用ダイアログを表示
int CViewDialog::showModalAuthCancelDlg(void)
{
    m_cancelAuthDlg = new wxDialog(m_parent, wxID_ANY, "ユーザ認証をキャンセル");
    return m_cancelAuthDlg->ShowModal();
}

// ユーザ認証キャンセル用ダイアログを消す
void CViewDialog::destroyAuthCancelDlg(void)
{
    if (m_cancelAuthDlg != NULL){
        m_cancelAuthDlg->Destroy();
        m_cancelAuthDlg = NULL;
    }
}

// チャンネル名を取得
wxString CViewDialog::getChannelName(void) const
{
    return m_channelDlg->getChannelName();
}

// ユーザ名を取得
wxString CViewDialog::getUserName(void) const
{
    return m_authDlg->getName();
}

// パスワードを取得
wxString CViewDialog::getPassword(void) const
{
    return m_authDlg->getPass();
}
