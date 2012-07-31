

#ifndef IRCSENDTASK_HPP_
#define IRCSENDTASK_HPP_
#include "IRCTask.hpp"

namespace CornStarch
{;
namespace IRC
{;
class CIRCSendTask : public CIRCTask
{
public:
    CIRCSendTask(wxThreadKind kind = wxTHREAD_DETACHED);
    virtual ~CIRCSendTask();
    wxThread::ExitCode Entry(void);
};
}
} /* namespace CornStarch */
#endif /* IRCSENDTASK_HPP_ */
