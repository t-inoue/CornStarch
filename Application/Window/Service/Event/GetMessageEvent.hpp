#pragma once
#include <vector>
#include "ConnectionEventBase.hpp"

namespace CornStarch
{;

// メッセージ受信時のイベント
class CGetMessageEvent : public CConnectionEventBase
{
private:
    std::vector<CMessageData*> m_messages; // メッセージ
    wxString m_channel; // チャンネル名
public:
    CGetMessageEvent(void);
    ~CGetMessageEvent(void);

    // メッセージをセット
    void setMessages(const std::vector<CMessageData*>& messages);

    // メッセージを取得
    std::vector<CMessageData*> getMessages(void) const;

    wxString getChannel() const
    {
        return m_channel;
    }

    void setChannel(wxString channel)
    {
        m_channel = channel;
    }
};

}
