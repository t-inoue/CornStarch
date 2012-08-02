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
    wxEvtHandler* m_handler; // 処理終了を受け取るハンドラ
    int m_connectionId; // コネクションのID

    vector<wxThread*> m_continueThreads;
    void invokeContinueThreads();
public:
    CIRCTask(wxThreadKind kind = wxTHREAD_DETACHED);
    virtual ~CIRCTask();
    virtual wxThread::ExitCode Entry(void)=0;
    void init(int connectionId,wxEvtHandler* handler, CIRCClient* client);
    void continueWith(wxThread *thread);
    void OnExit();
};
}
} /* namespace CornStarch */
#endif /* IRCTASK_HPP_ */
