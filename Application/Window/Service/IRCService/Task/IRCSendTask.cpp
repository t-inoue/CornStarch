#include "IRCSendTask.hpp"
#include "../IRCCommand.hpp"

namespace CornStarch
{
;
namespace IRC
{
;

CIRCSendTask::CIRCSendTask(wxThreadKind kind) :
        CIRCTask(kind)
{

}

CIRCSendTask::~CIRCSendTask()
{
}
// Run実行時に呼ばれる本体
wxThread::ExitCode CIRCSendTask::Entry(void)
{
    while (m_client->isSocketConnected()){
        // Queueから取得
        wxString buffer;
        m_client->getCommandQueue()->ReceiveTimeout(100, buffer);
        if (buffer != ""){
            m_client->sendCommand(buffer);
            if(buffer == IRCCommand::QUIT)
            {
                break;
            }
        }
        wxUsleep(100);
    }

    // 成功時
    return (wxThread::ExitCode) 0;
}

}
} /* namespace CornStarch */
