#ifndef IRCRECEIVETASK_HPP_
#define IRCRECEIVETASK_HPP_

#include "IRCTask.hpp"
#include "../IRCMessageData.hpp"
#include "../../Event/ConnectionEventBase.hpp"

namespace CornStarch
{
;
namespace IRC
{
;
class CIRCReceiveTask: public CIRCTask
{
private:
    // 受信データのバッファ
    wxString m_receiveBuffer;
public:
    CIRCReceiveTask(wxThreadKind kind = wxTHREAD_DETACHED);
    virtual ~CIRCReceiveTask();
    wxThread::ExitCode Entry(void);
};
}
} /* namespace CornStarch */
#endif /* IRCRECEIVETASK_HPP_ */
