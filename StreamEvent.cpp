#include "StreamEvent.hpp"


CStreamEvent::CStreamEvent(wxEventType eventType, int id)
    : wxThreadEvent(eventType, id)
{
}


CStreamEvent::~CStreamEvent(void)
{
}


//////////////////////////////////////////////////////////////////////


// ストリームを取得する
CStreamData CStreamEvent::getStreamData(void) const
{
    return m_stream;
}

// ストリームをセットする
void CStreamEvent::setStreamData(const CStreamData& stream)
{
    m_stream = stream;
}