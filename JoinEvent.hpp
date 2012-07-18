#pragma once
#include "header.hpp"
#include "ChannelData.hpp"

// チャンネル参加時のイベント
class CJoinEvent : public wxThreadEvent
{
private:
    CChannelData* m_channel;

public:
    CJoinEvent(void);
    ~CJoinEvent(void);

    // チャンネルをセット
    void setChannel(const CChannelData& channel);

    // チャンネルを取得
    CChannelData getChannel(void) const;
};

