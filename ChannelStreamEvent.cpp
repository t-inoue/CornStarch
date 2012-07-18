#include "ChannelStreamEvent.hpp"

using namespace std;

CChannelStreamEvent::CChannelStreamEvent(void) : m_channelData(NULL)
{
}


CChannelStreamEvent::~CChannelStreamEvent(void)
{
    delete m_channelData;
}


//////////////////////////////////////////////////////////////////////


// チャンネルを取得する
CChannelData CChannelStreamEvent::getChannel(void) const
{
    return *m_channelData;
}

// チャンネルをセットする
void CChannelStreamEvent::setChannel(const CChannelData& channel)
{
    if (m_channelData == NULL){
        m_channelData = new CChannelData();
    }

    *m_channelData = channel;
}