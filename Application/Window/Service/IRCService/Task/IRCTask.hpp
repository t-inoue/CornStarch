#ifndef IRCTASK_HPP_
#define IRCTASK_HPP_
#include "../../../../header.hpp"
#include <wx/wxprec.h>
#include <wx/wx.h>

namespace CornStarch
{

class IRCTask : public wxThread
{
public:
    IRCTask();
    virtual ~IRCTask();
    wxThread::ExitCode Entry(void);
};

} /* namespace CornStarch */
#endif /* IRCTASK_HPP_ */
