#include "InviteLog.hpp"
namespace CornStarch
{
;

CInviteLog::CInviteLog()
{
}

CInviteLog::~CInviteLog()
{
}
void CInviteLog::init(const wxString& name, const wxString& channel)
{
    this->m_channel = channel;
    this->m_username = name;
    this->m_type = LOG_INVITE;
}
}

