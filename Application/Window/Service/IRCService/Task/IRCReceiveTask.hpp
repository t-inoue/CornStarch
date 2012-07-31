
#ifndef IRCRECEIVETASK_HPP_
#define IRCRECEIVETASK_HPP_

#include "IRCTask.hpp"

namespace CornStarch
{;
namespace IRC
{;
class CIRCReceiveTask: public CIRCTask
{

public:
    CIRCReceiveTask(wxThreadKind kind = wxTHREAD_DETACHED);
    virtual ~CIRCReceiveTask();
    wxThread::ExitCode Entry(void);
    void pong(const wxString& value);
};
}
} /* namespace CornStarch */
#endif /* IRCRECEIVETASK_HPP_ */
