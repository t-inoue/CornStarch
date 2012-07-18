#include "GetThreadEvent.hpp"

using namespace std;

CGetThreadEvent::CGetThreadEvent(wxEventType eventType, int id)
    : wxThreadEvent(eventType, id)
{
}


CGetThreadEvent::~CGetThreadEvent(void)
{
}


//////////////////////////////////////////////////////////////////////


// チャンネルをセット
void CGetThreadEvent::setChannels(const vector<CChannelData*>& channels)
{
    m_channels = channels;
}

// メンバーをセット
void CGetThreadEvent::setMembers(const vector<CMemberData*>& members)
{
    m_members = members;
}

// メッセージをセット
void CGetThreadEvent::setMessages(const vector<CMessageData*>& messages)
{
    m_messages = messages;
}

// pingの成否をセット
void CGetThreadEvent::setPingResult(bool ping)
{
    m_ping = ping;
}

// チャンネルを取得
vector<CChannelData*> CGetThreadEvent::getChannels(void) const
{
    return m_channels;
}

// メンバーを取得
vector<CMemberData*> CGetThreadEvent::getMembers(void) const
{
    return m_members;
}

// メッセージを取得
vector<CMessageData*> CGetThreadEvent::getMessages(void) const
{
    return m_messages;
}

// pingの成否を取得
bool CGetThreadEvent::isPingSucceeded(void) const
{
    return m_ping;
}

// 複製を返す
CGetThreadEvent* CGetThreadEvent::clone(void) const
{
    return new CGetThreadEvent(*this);
}