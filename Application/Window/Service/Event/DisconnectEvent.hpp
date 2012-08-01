
#ifndef DISCONNECTEVENT_HPP_
#define DISCONNECTEVENT_HPP_
#include "ConnectionEventBase.hpp"

namespace CornStarch
{

class CDisconnectEvent: public CConnectionEventBase
{
public:
    CDisconnectEvent();
    virtual ~CDisconnectEvent();
};

} /* namespace CornStarch */
#endif /* DISCONNECTEVENT_HPP_ */
