#pragma once
#include "header.hpp"
#include <string>

// チャンネルから誰かが離脱した際のイベント
class CPartStreamEvent : public wxThreadEvent
{
private:
    wxString m_channel; // チャンネル名
    wxString m_user; // ユーザ名

public:
    CPartStreamEvent(void);
    ~CPartStreamEvent(void);

    // チャンネル名をセット
    void setChannelName(const wxString& channel);

    // ユーザ名をセット
    void setUserName(const wxString& userName);

    // チャンネル名を取得
    wxString getChannelName(void) const;

    // ユーザ名を取得
    wxString getUserName(void) const;
};

