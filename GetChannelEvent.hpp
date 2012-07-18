#pragma once
#include "header.hpp"
#include "vector"
#include "ChannelData.hpp"

// チャンネル受信時のイベント
class CGetChannelEvent : public wxThreadEvent
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

