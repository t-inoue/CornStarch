#pragma once
#include "header.hpp"
#include "ChannelData.hpp"

// チャンネル情報更新時のイベント
class CChannelStreamEvent : public wxThreadEvent
{
private:
    CChannelData* m_channelData; // チャンネル情報

public:
    CChannelStreamEvent(void);
    ~CChannelStreamEvent(void);

    // チャンネルを取得する
    CChannelData getChannel(void) const;

    // チャンネルをセットする
    void setChannel(const CChannelData& channel);
};

