#pragma once
#include "SCTask.hpp"

namespace CornStarch
{
;

namespace StarChat
{
;

// メッセージ取得を別スレッドで取得するためのタスク
class CSCGetMessageTask: public CSCTask
{
private:
    wxString m_channel;

public:
    CSCGetMessageTask(void);
    ~CSCGetMessageTask(void);

    wxString getChannel() const
    {
        return m_channel;
    }

    void setChannel(wxString channel)
    {
        m_channel = channel;
    }

private:
    void sendRequestToSC(CSCClient* client);
    void notifyMessage(const std::string& responseBody);
};

}
}
