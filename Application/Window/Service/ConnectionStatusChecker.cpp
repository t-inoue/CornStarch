#include "ConnectionStatusChecker.h"

namespace CornStarch
{

CConnectionStatusChecker::CConnectionStatusChecker(
        IMessageConnectionObserver* observer, int checkCount)
{
    m_observer = observer;
    m_checkCount = checkCount;
}

CConnectionStatusChecker::~CConnectionStatusChecker()
{
}

void CConnectionStatusChecker::refreshCount()
{
    m_currentCount = m_checkCount;
}
void CConnectionStatusChecker::tick()
{
    m_currentCount--;
    if(m_currentCount == 0)
    {
        m_observer->onCheckServiceStatus();
        refreshCount();
    }
}

} /* namespace CornStarch */
