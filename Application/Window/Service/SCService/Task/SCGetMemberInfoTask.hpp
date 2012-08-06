#pragma once
#include "SCTask.hpp"

namespace CornStarch
{
;
// イベントの宣言
wxDECLARE_EVENT(myEVT_THREAD_GET_MEMBER_INFO, CGetMemberInfoEvent);

namespace StarChat
{
;
// メンバーの情報を取得するためのタスク
class CSCGetMemberInfoTask: public CSCTask
{
private:
    wxString m_username;

public:
    CSCGetMemberInfoTask(void);
    ~CSCGetMemberInfoTask(void);

    wxString getUsername() const
    {
        return m_username;
    }

    void setUsername(wxString username)
    {
        m_username = username;
    }

private:
    void sendRequestToSC(CSCClient* client);
    void notifyMessage(const std::string& responseBody);
};

}
}
