#include "ConnectionEventBase.hpp"

namespace CornStarch
{;

CConnectionEventBase::CConnectionEventBase()
{

}
CConnectionEventBase::CConnectionEventBase(wxEventType eventType, int id) : wxThreadEvent(eventType, id)
{
}
CConnectionEventBase::~CConnectionEventBase()
{

}

}