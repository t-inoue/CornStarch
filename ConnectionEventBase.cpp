
#include "ConnectionEventBase.hpp"

CConnectionEventBase::CConnectionEventBase()
{

}
 CConnectionEventBase::CConnectionEventBase(wxEventType eventType, int id) : wxThreadEvent(eventType, id)
{
}
CConnectionEventBase::~CConnectionEventBase()
{

}

