#pragma once
#include "header.hpp"
#include "vector"
#include "MessageData.hpp"

// メッセージ受信時のイベント
class CGetMessageEvent : public wxThreadEvent
{
private:
    std::vector<CMessageData*> m_messages; // メッセージ

public:
    CGetMessageEvent(void);
    ~CGetMessageEvent(void);

    // メッセージをセット
    void setMessages(const std::vector<CMessageData*>& messages);

    // メッセージを取得
    std::vector<CMessageData*> getMessages(void) const;
};

