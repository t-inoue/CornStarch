#include "IRCTask.hpp"

namespace CornStarch
{;
namespace IRC
{;
CIRCTask::CIRCTask(wxThreadKind kind): wxThread(kind)
{
}

CIRCTask::~CIRCTask()
{
}

void CIRCTask::init(int connectionId, wxEvtHandler* handler, CIRCClient* client)
{
    m_connectionId = connectionId;
    m_handler = handler;
    m_client = client;
}

}
} /* namespace CornStarch */
