#ifndef SCEVENTFACTORY_HPP_
#define SCEVENTFACTORY_HPP_
#include "../Event/ConnectionEventBase.hpp"
#include "SCMessageData.hpp"
namespace CornStarch
{
namespace StarChat
{
class CSCEventFactory
{
public:
    CSCEventFactory();
    virtual ~CSCEventFactory();

    CConnectionEventBase* Create(CSCMessageData message);

};
}
}
#endif /* SCEVENTFACTORY_HPP_ */
