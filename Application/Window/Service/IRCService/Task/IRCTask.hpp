#ifndef IRCTASK_HPP_
#define IRCTASK_HPP_
#include <wx/wxprec.h>
#include <wx/wx.h>
#include "../IRCClient.hpp"
#include "../../Event/DisconnectEvent.hpp"

namespace CornStarch
{;
namespace IRC
{;
class CIRCTask : public wxThread
{

protected:
    CIRCClient* m_client;
    vector<wxThread*> m_continueThreads;
    void invokeContinueThreads();
public:
    CIRCTask(wxThreadKind kind = wxTHREAD_DETACHED);
    virtual ~CIRCTask();
    virtual wxThread::ExitCode Entry(void)=0;
    void init(CIRCClient* client);
    void continueWith(wxThread *thread);
    void OnExit();
};
}
} /* namespace CornStarch */
#endif /* IRCTASK_HPP_ */
