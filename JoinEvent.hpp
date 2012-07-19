#pragma once
#include "header.hpp"
#include "ChannelData.hpp"
#include "ConnectionEventBase.hpp"

// チャンネル参加時のイベント
class CJoinEvent : public CConnectionEventBase
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

