#include "AuthEvent.hpp"

namespace CornStarch
{;

CAuthEvent::CAuthEvent(void)
{
}


CAuthEvent::~CAuthEvent(void)
{
}


//////////////////////////////////////////////////////////////////////


// 認証の成否をセット
void CAuthEvent::setAuthResult(bool auth)
{
    m_auth = auth;
}

// 認証の成否を取得
bool CAuthEvent::isAuthSucceeded(void) const
{
    return m_auth;
}

}