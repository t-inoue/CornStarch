#pragma once
#include "SCTask.hpp"

namespace CornStarch
{
;
// イベントの宣言
wxDECLARE_EVENT(myEVT_THREAD_GET_MEMBER, CGetMemberEvent);


namespace StarChat
{
;

// メンバー取得を別スレッドで取得するためのタスク
class CSCGetMemberTask: public CSCTask
{
private:
    wxString m_channel;
public:
    CSCGetMemberTask(void);
    ~CSCGetMemberTask(void);

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
