#pragma once
#include "SCTask.hpp"

namespace CornStarch
{
;


namespace StarChat
{
;

// チャンネルを別スレッドで取得するためのタスク
class CSCGetChannelTask: public CSCTask
{
private:
    wxString m_userName;

public:
    CSCGetChannelTask(void);
    ~CSCGetChannelTask(void);

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
