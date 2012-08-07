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
    // IRCとの接続が完了しているか
    bool m_isConnectedToIRCService;
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
