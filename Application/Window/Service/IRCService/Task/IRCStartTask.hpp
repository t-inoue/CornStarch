#ifndef IRCLOGINTASK_HPP_
#define IRCLOGINTASK_HPP_

#include "IRCTask.hpp"

namespace CornStarch
{;
namespace IRC
{;

class CIRCStartTask:public CIRCTask
{
    wxString m_userName;
    wxString m_password;
public:
    CIRCStartTask(wxThreadKind kind = wxTHREAD_DETACHED);
    virtual ~CIRCStartTask();
    wxThread::ExitCode Entry(void);

    wxString getPassword() const
    {
        return m_password;
    }

    void setPassword(wxString password)
    {
        m_password = password;
    }

    wxString getUserName() const
    {
        return m_userName;
    }

    void setUserName(wxString userName)
    {
        m_userName = userName;
    }

};
}
} /* namespace CornStarch */
#endif /* IRCLOGINTASK_HPP_ */
