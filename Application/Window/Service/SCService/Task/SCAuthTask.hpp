#pragma once
#include "SCTask.hpp"

namespace CornStarch
{
;
// イベントの宣言
wxDECLARE_EVENT(myEVT_THREAD_GET_PING, CAuthEvent);

namespace StarChat
{
;

// StarChatのユーザ認証を行うためのタスク
class CSCAuthTask: public CSCTask
{
private:

    wxString m_userName;
    ;

public:
    CSCAuthTask(void);
    ~CSCAuthTask(void);

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
