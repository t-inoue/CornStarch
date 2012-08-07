
#include "KickLog.hpp"
namespace CornStarch
{
;

CKickLog::CKickLog()
{
}

CKickLog::~CKickLog()
{
}

void CKickLog::init(const wxString& name, const wxString& channel)
{
    this->m_channel = channel;
    this->m_username = name;
    this->m_type = LOG_KICK;
}
}
