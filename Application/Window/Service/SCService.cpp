#include "SCService.h"

namespace CornStarch
{;
namespace StarChat
{;

CSCService::CSCService() {

}

CSCService::~CSCService() {
}

void CSCService::init(wxEvtHandler* handler)
{
	CChatServiceBase::init(handler);

    // スターチャットの通信
    m_connect = new CSCConnection();
    m_connect->init(this->m_id, m_handler);

    // スターチャットのユーザー
    m_user = new CSCUser();
    m_user->init();
    m_user->setChannel("");

    // チャットのタイプ
    m_type = CChatServiceBase::STAR_CHAT;
}

}
}