#pragma once
#include <vector>
#include "ConnectionEventBase.hpp"

namespace CornStarch
{;

// チャンネル受信時のイベント
class CGetChannelEvent : public CConnectionEventBase
{
private:
    std::vector<CChannelData*> m_channels; // チャンネル

public:
    CGetChannelEvent(void);
    ~CGetChannelEvent(void);

    // チャンネルをセット
    void setChannels(const std::vector<CChannelData*>& channels);

    // チャンネルを取得
    std::vector<CChannelData*> getChannels(void) const;
};

}