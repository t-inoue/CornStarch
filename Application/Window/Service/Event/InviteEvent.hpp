#ifndef INVITEEVENT_HPP_
#define INVITEEVENT_HPP_
#include "ConnectionEventBase.hpp"

namespace CornStarch
{

class CInviteEvent: public CConnectionEventBase
{
public:
    CInviteEvent();
    virtual ~CInviteEvent();
};

} /* namespace CornStarch */
#endif /* INVITEEVENT_HPP_ */
