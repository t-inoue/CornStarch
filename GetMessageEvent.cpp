#include "GetMessageEvent.hpp"

using namespace std;

CGetMessageEvent::CGetMessageEvent(void)
{
}


CGetMessageEvent::~CGetMessageEvent(void)
{
    // メッセージの削除
    int size = (int)m_messages.size();
    for (int i = 0; i < size; i++){
        delete m_messages[i];
    }
}


//////////////////////////////////////////////////////////////////////


// メッセージをセット
void CGetMessageEvent::setMessages(const vector<CMessageData*>& messages)
{
    m_messages = messages;
}

// メッセージを取得
vector<CMessageData*> CGetMessageEvent::getMessages(void) const
{
    return m_messages;
}

