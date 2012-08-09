
#ifndef CONNECTIONSTATUSCHECKER_H_
#define CONNECTIONSTATUSCHECKER_H_
#include "IMessageConnectionObserver.hpp"
namespace CornStarch
{

class CConnectionStatusChecker
{
    IMessageConnectionObserver* m_observer;
    int m_checkCount;
    int m_currentCount;
public:
    CConnectionStatusChecker(IMessageConnectionObserver* observer,int checkCount  = 300);
    virtual ~CConnectionStatusChecker();
    void refreshCount();
    void tick();
};

} /* namespace CornStarch */
#endif /* CONNECTIONSTATUSCHECKER_H_ */
