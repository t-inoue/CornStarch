#pragma once
#include "header.hpp"
#include "StreamData.hpp"

// メッセージ受信時のイベント
class CMsgStreamEvent : public wxThreadEvent
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

