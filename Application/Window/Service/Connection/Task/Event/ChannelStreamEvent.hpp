#pragma once
#include "../../../../../DataStruct/ChannelData.hpp"
#include "ConnectionEventBase.hpp"

namespace CornStarch
{;

// チャンネル情報更新時のイベント
class CChannelStreamEvent : public CConnectionEventBase
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

}