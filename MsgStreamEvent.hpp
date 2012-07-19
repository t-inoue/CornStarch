#pragma once
#include "header.hpp"
#include "StreamData.hpp"
#include "ConnectionEventBase.hpp"

// メッセージ受信時のイベント
class CMsgStreamEvent : public CConnectionEventBase
{
private:
    CMessageData* m_message;

public:
    CMsgStreamEvent(void);
    ~CMsgStreamEvent(void);

    // メッセージを取得する
    CMessageData getMessage(void) const;

    // メッセージをセットする
    void setMessage(const CMessageData& message);
};

