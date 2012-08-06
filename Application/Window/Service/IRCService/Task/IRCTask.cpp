#include "IRCTask.hpp"

namespace CornStarch
{
;
namespace IRC
{
;
CIRCTask::CIRCTask(wxThreadKind kind) :
        wxThread(kind)
{
}

CIRCTask::~CIRCTask()
{
}

void CIRCTask::init(CIRCClient* client)
{
    m_client = client;
}
void CIRCTask::continueWith(wxThread* thread)
{
    m_continueThreads.push_back(thread);
}
void CIRCTask::invokeContinueThreads()
{
    vector<wxThread*>::iterator it = m_continueThreads.begin();
    while (it != m_continueThreads.end()){
        if ((*it)->Create() != wxTHREAD_NO_ERROR){
            delete (*it);
            it++;
            continue;
        }
        // 別スレッドを走らせる
        if ((*it)->Run() != wxTHREAD_NO_ERROR){
            delete (*it);
        }
        it++;
    }
}
void CIRCTask::OnExit()
{
    if (this->TestDestroy() == false){
        invokeContinueThreads();
    }
}
}
} /* namespace CornStarch */
