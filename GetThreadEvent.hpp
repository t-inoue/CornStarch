#pragma once
#include "header.hpp"
#include "ChannelData.hpp"
#include "MessageData.hpp"
#include "MemberData.hpp"
#include <vector>

// GET時にハンドルさせるイベント
class CGetThreadEvent : public wxThreadEvent
{

private:
    std::vector<CChannelData*> m_channels; // チャンネル
    std::vector<CMemberData*> m_members; // メンバー
    std::vector<CMessageData*> m_messages; // メッセージ
    bool m_ping; // ping送信の成否

public:
    CGetThreadEvent(wxEventType eventType = wxEVT_THREAD, int id = wxID_ANY);
    ~CGetThreadEvent(void);

    // チャンネルをセット
    void setChannels(const std::vector<CChannelData*>& channels);

    // メンバーをセット
    void setMembers(const std::vector<CMemberData*>& members);

    // メッセージをセット
    void setMessages(const std::vector<CMessageData*>& messages);

    // pingの成否をセット
    void setPingResult(bool ping);

    // チャンネルを取得
    std::vector<CChannelData*> getChannels(void) const;

    // メンバーを取得
    std::vector<CMemberData*> getMembers(void) const;

    // メッセージを取得
    std::vector<CMessageData*> getMessages(void) const;

    // pingの成否を取得
    bool isPingSucceeded(void) const;

    // 複製を返す
    CGetThreadEvent* clone(void) const;

};

