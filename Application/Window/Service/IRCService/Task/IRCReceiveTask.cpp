#include "IRCReceiveTask.hpp"
#include "../IRCParser.hpp"
#include "../IRCCommand.hpp"
#include  "../StringUtility.hpp"
#include "../../Event/AuthEvent.hpp"
namespace CornStarch
{
;

wxDECLARE_EVENT(myEVT_THREAD_GET_PING, CAuthEvent);
namespace IRC
{
;
CIRCReceiveTask::CIRCReceiveTask(wxThreadKind kind) :
        CIRCTask(kind)
{

}

CIRCReceiveTask::~CIRCReceiveTask()
{
}

void CIRCReceiveTask::pong(const wxString& value)
{
    wxString content(wxString::Format(wxT("%s %s"), IRCCommand::PONG, value));
    m_client->addCommandQueue(content);
}
// Run実行時に呼ばれる本体
wxThread::ExitCode CIRCReceiveTask::Entry(void)
{
    CIRCParser parser;
    while (m_client->isSocketConnected()){
        wxString buffer = m_client->recieveData(); //  receive();
        if (buffer != ""){
            std::string str(buffer);
            vector<wxString> messages = CStringUtility::split(str, "\n");
            for (int i = 0; i < messages.size(); i++){
                // PING応答
                if (messages[i].find(IRCCommand::PING) == 0){
                    wxString pingValue =
                            CStringUtility::split(messages[i], ":")[1];
                    pong(pingValue);
                } else if (messages[i].find(IRCCommand::ERROR) == 0){
                    break;
                } else{
                    // イベント生成
                    CConnectionEventBase* event = parser.parse(messages[i]);
                    if (event != NULL){
                        event->setConnectionId(m_connectionId);
                        wxQueueEvent(m_handler, event);
                    }
                }
            }
        }
        wxUsleep(100);
    }
    if (m_client->isClosing() != true){
        // 故意でない切断時
        CAuthEvent* event = new CAuthEvent();
        event->setAuthResult(false);
        event->SetEventType(myEVT_THREAD_GET_PING); // イベントの種類をセット
        event->setConnectionId(m_connectionId);
        wxQueueEvent(m_handler, event);
    }
    // 成功時
    return (wxThread::ExitCode) 0;
}
}
} /* namespace CornStarch */
