#include "IRCService.hpp"

namespace CornStarch
{;
namespace IRC
{;
CIRCService::CIRCService()
{
}

CIRCService::~CIRCService()
{
}

void CIRCService::init(wxEvtHandler* handler)
{

	CChatServiceBase::init(handler);

	m_connect = new CIRCConnection();
	m_connect->init(m_id, m_handler);

	m_user = new CIRCUser();
	m_user->init();
	m_user->setChannel("");

    // IRCのチャットタイプ
    m_type = CChatServiceBase::IRC;

}
void CIRCService::onAuthSucceeed(void)
{
    CChatServiceBase::onAuthSucceeed();
    vector<wxString>::iterator it = savedChannels.begin();
    while (it != savedChannels.end()){
        joinChannel(*it);
        it++;
    }
}

//再接続します。
void CIRCService::reconnect(void)
{
    // 通信を初期化
    CIRCConnection *newConnection = new CIRCConnection;

    newConnection->init(m_id, m_handler);
    newConnection->setHost(m_connect->getHost());

    // 前回接続済みのユーザーがサーバー側で切断の完了になってない場合があるので、ユーザー名を変更。
    m_user->setUserName(m_user->getUserName()+"_");
    this->setSavedChannels(getChannels());
    delete m_connect;
    m_connect = newConnection;
    regUser(m_user->getUserName(),m_user->getBasic());
}
}
}
