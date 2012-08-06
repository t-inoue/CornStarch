#pragma once
#include "SCTask.hpp"

namespace CornStarch
{
;
namespace StarChat
{
;

// ニックネーム変更を行うためのタスク
class CSCNickChangeTask: public CSCTask
{
private:
    wxString m_nick;
    wxString m_name;

public:
    CSCNickChangeTask(void);
    ~CSCNickChangeTask(void);

    wxString getName() const
    {
        return m_name;
    }

    void setName(wxString name)
    {
        m_name = name;
    }

    wxString getNick() const
    {
        return m_nick;
    }

    void setNick(wxString nick)
    {
        m_nick = nick;
    }

private:
    void sendRequestToSC(CSCClient* client);
    void notifyMessage(const std::string& responseBody);
};

}
}
