#include "IRCService.h"

namespace CornStarch
{
namespace IRC
{
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
}
}
