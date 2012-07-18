#include "JoinEvent.hpp"


CJoinEvent::CJoinEvent(void) : m_channel(NULL)
{
}


CJoinEvent::~CJoinEvent(void)
{
    delete m_channel;
}


//////////////////////////////////////////////////////////////////////


// チャンネルをセット
void CJoinEvent::setChannel(const CChannelData& channel)
{
    // メモリ領域の確保
    if (m_channel == NULL){
        m_channel = new CChannelData();
    }

    // 値のコピー
    *m_channel = channel;
}

// チャンネルを取得
CChannelData CJoinEvent::getChannel(void) const
{
    return *m_channel;
}
