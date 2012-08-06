#ifndef KICKEVENT_HPP_
#define KICKEVENT_HPP_
#include "ConnectionEventBase.hpp"
namespace CornStarch
{
class CKickEvent: public CConnectionEventBase
{
public:
    CKickEvent();
    virtual ~CKickEvent();
};
}
#endif /* KICKEVENT_HPP_ */
