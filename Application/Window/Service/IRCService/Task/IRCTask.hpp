#ifndef IRCTASK_HPP_
#define IRCTASK_HPP_
#include "../../../../header.hpp"
#include <wx/wxprec.h>
#include <wx/wx.h>
#include "../IRCClient.hpp"

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
public:
    CIRCTask(wxThreadKind kind = wxTHREAD_DETACHED);
    virtual ~CIRCTask();
    virtual wxThread::ExitCode Entry(void)=0;
    void init(int connectionId,wxEvtHandler* handler, CIRCClient* client);
};
}
} /* namespace CornStarch */
#endif /* IRCTASK_HPP_ */
