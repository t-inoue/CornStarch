#include "SCService.hpp"

namespace CornStarch
{
;
namespace StarChat
{
;

CSCService::CSCService()
{
    m_connect = new CSCConnection();
    m_user = new CSCUser();
}

CSCService::~CSCService()
{
}

void CSCService::init(wxEvtHandler* handler)
{
    CChatServiceBase::init(handler);

    // スターチャットの通信
    m_connect->init(this->m_id, m_handler);

    // スターチャットのユーザー
    m_user->init();
    m_user->setChannel("");

    // チャットのタイプ
    m_type = CChatServiceBase::STAR_CHAT;
}

// 再接続を行う
void CSCService::reconnect(void)
{
    if (m_state ==CChatServiceBase::DISCONNECT){
        // 通信を初期化
        CSCConnection *newConnection = new CSCConnection();
        newConnection->setHost(m_connect->getHost());
        newConnection->init(m_id, m_handler);

        delete m_connect;
        m_connect = NULL;
        m_connect = newConnection;

        registerUser(m_user->getUserName(), m_user->getBasic());
        connect();
    }
}
}
}
