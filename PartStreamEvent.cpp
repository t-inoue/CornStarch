#include "PartStreamEvent.hpp"

using namespace std;

CPartStreamEvent::CPartStreamEvent(void)
{
}


CPartStreamEvent::~CPartStreamEvent(void)
{
}


//////////////////////////////////////////////////////////////////////


// チャンネル名をセット
void CPartStreamEvent::setChannelName(const wxString& channel)
{
    m_channel = channel;
}

// ユーザ名をセット
void CPartStreamEvent::setUserName(const wxString& userName)
{
    m_user = userName;
}

// チャンネル名を取得
wxString CPartStreamEvent::getChannelName(void) const
{
    return m_channel;
}

// ユーザ名を取得
wxString CPartStreamEvent::getUserName(void) const
{
    return m_user;
}
