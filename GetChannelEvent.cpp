#include "GetChannelEvent.hpp"

using namespace std;

CGetChannelEvent::CGetChannelEvent(void)
{
}


CGetChannelEvent::~CGetChannelEvent(void)
{
    // チャンネル要素の削除
    int size = (int)m_channels.size();
    for (int i = 0; i < size; i++){
        delete m_channels[i];
    }
}


//////////////////////////////////////////////////////////////////////


// チャンネルをセット
void CGetChannelEvent::setChannels(const vector<CChannelData*>& channels)
{
    m_channels = channels;
}

// チャンネルを取得
vector<CChannelData*> CGetChannelEvent::getChannels(void) const
{
    return m_channels;
}
