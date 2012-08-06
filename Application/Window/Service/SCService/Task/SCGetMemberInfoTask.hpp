#pragma once
#include "SCTask.hpp"

namespace CornStarch
{
;
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
