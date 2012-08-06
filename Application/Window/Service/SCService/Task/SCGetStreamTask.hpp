#pragma once
#include "SCTask.hpp"
#include "../SCMessageData.hpp"

namespace CornStarch
{
;
// イベントの宣言
wxDECLARE_EVENT(myEVT_THREAD_STREAM_MSG_ADD, CMsgStreamEvent);
wxDECLARE_EVENT(myEVT_THREAD_STREAM_CH_JOIN, CJoinStreamEvent);
wxDECLARE_EVENT(myEVT_THREAD_STREAM_CH_PART, CPartStreamEvent);
wxDECLARE_EVENT(myEVT_THREAD_STREAM_CH_UPDATE, CChannelStreamEvent);
wxDECLARE_EVENT(myEVT_THREAD_STREAM_USER_UPDATE, CUserStreamEvent);
wxDECLARE_EVENT(myEVT_THREAD_DISCONNECT, CDisconnectEvent);

namespace StarChat
{
;

// ストリームを受信するためのタスク
class CSCGetStreamTask: public CSCTask
{
private:
    wxString m_userName;

public:
    CSCGetStreamTask(void);
    ~CSCGetStreamTask(void);

    wxString getUserName() const
    {
        return m_userName;
    }

    void setUserName(wxString userName)
    {
        m_userName = userName;
    }

private:
    ExitCode Entry(void);
    CSCMessageData parseStream(const std::string& json);
};

}
}
