#pragma once
#include "SCTask.hpp"

namespace CornStarch
{
;


// イベントの宣言
wxDECLARE_EVENT(myEVT_THREAD_PUT_JOIN, CJoinEvent);

namespace StarChat
{
;

// チャンネルに参加するためのタスク
class CSCJoinChannelTask: public CSCTask
{
private:
    wxString m_userName;

    wxString m_channel;

public:
    CSCJoinChannelTask(void);
    ~CSCJoinChannelTask(void);

    wxString getChannel() const
    {
        return m_channel;
    }

    void setChannel(wxString channel)
    {
        m_channel = channel;
    }

    wxString getUserName() const
    {
        return m_userName;
    }

    void setUserName(wxString userName)
    {
        m_userName = userName;
    }

private:
    void sendRequestToSC(CSCClient* client);
    void notifyMessage(const std::string& responseBody);
};

}
}
