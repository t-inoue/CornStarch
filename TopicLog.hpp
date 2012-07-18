#pragma once
#include "ChatLog.hpp"
#include "ChannelData.hpp"

// トピック変更のログ
class CTopicLog : public CChatLog
{
private:
    CChannelData* m_channel;

public:
    CTopicLog(void);
    ~CTopicLog(void);

    // 初期化を行う
    void init(const CChannelData& channel);

    // ログを取得する
    CChannelData getLog(void) const;
};

