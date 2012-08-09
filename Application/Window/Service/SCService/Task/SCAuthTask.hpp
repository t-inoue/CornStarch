#pragma once
#include "SCTask.hpp"

namespace CornStarch
{
;
// イベントの宣言
wxDECLARE_EVENT(myEVT_THREAD_GET_PING, CAuthEvent);

wxDECLARE_EVENT(myEVT_THREAD_INVITE, CInviteEvent);
wxDECLARE_EVENT(myEVT_THREAD_KICK, CKickEvent);
namespace StarChat
{
;

// StarChatのユーザ認証を行うためのタスク
class CSCAuthTask: public CSCTask
{
private:

    wxString m_userName;
    bool m_isPing;

public:
    CSCAuthTask(void);
    ~CSCAuthTask(void);

    bool isPing() const
    {
        return m_isPing;
    }

    void setPing(bool isPing)
    {
        m_isPing = isPing;
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
