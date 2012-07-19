
#include "SCConnectionContents.h"
#include "SCConnection.hpp"
#include "SCUser.hpp"

CSCConnectionContents::CSCConnectionContents() {

}

CSCConnectionContents::~CSCConnectionContents() {
}

void CSCConnectionContents::init(wxEvtHandler* handler)
{
	CConnectionContents::init(handler);

    // スターチャットの通信
    m_connect = new CSCConnection();
    m_connect->init(m_handler);

    // スターチャットのユーザー
    m_user = new CSCUser();
    m_user->init();
    m_user->setChannel("");

    // 認証
    wxString basicKey = m_user->getBasicKey();
    wxString nameKey = m_user->getNameKey();
    if (m_persist->isKeySaved(basicKey) && m_persist->isKeySaved(nameKey)){

        // 保存されてデータから読み込み。
        m_user->setUserName(m_persist->loadValue(nameKey));
        m_user->setBasic(m_persist->loadValue(basicKey));

        // 認証を開始
        m_connect->startAuthTask(m_handler, m_user->getUserName(), m_user->getBasic());
    }
}
