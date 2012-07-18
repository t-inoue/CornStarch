#include "MsgStreamEvent.hpp"


CMsgStreamEvent::CMsgStreamEvent(void) : m_message(NULL)
{
}


CMsgStreamEvent::~CMsgStreamEvent(void)
{
    delete m_message;
}


//////////////////////////////////////////////////////////////////////


// ストリームを取得する
CMessageData CMsgStreamEvent::getMessage(void) const
{
    return *m_message;
}

// ストリームをセットする
void CMsgStreamEvent::setMessage(const CMessageData& message)
{
    if (m_message == NULL){
        m_message = new CMessageData();
    }

    *m_message = message;
}