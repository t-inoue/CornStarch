#include "GetStreamEvent.hpp"


CGetStreamEvent::CGetStreamEvent(void)
{
}


CGetStreamEvent::~CGetStreamEvent(void)
{
}


//////////////////////////////////////////////////////////////////////


// ストリームを取得する
CStreamData CGetStreamEvent::getStreamData(void) const
{
    return m_stream;
}

// ストリームをセットする
void CGetStreamEvent::setStreamData(const CStreamData& stream)
{
    m_stream = stream;
}