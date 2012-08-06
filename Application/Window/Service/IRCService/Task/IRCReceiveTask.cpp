#include "IRCReceiveTask.hpp"
#include "../IRCParser.hpp"
#include "../IRCCommand.hpp"
#include  "../StringUtility.hpp"

namespace CornStarch
{
;

namespace IRC
{
;
CIRCReceiveTask::CIRCReceiveTask(wxThreadKind kind) :
        CIRCTask(kind), m_receiveBuffer(""), m_isConnectedToIRCService(false)
{

}

CIRCReceiveTask::~CIRCReceiveTask()
{
}
// Run実行時に呼ばれる本体
wxThread::ExitCode CIRCReceiveTask::Entry(void)
{
    CIRCParser parser;
    //　ソケットが切断されているか、自分で終了しようとしていればループ終了
    while (m_client->isSocketConnected() && this->TestDestroy() == false){
        m_receiveBuffer += m_client->recieveData();
        if (m_receiveBuffer != ""
                && m_receiveBuffer.Find("\n") != wxString::npos){
            vector<wxString> messages = CStringUtility::split(m_receiveBuffer,
                    "\n");
            int messageSize = messages.size();
            for (int index = 0; index < messages.size(); index++){
                 if (messages[index].find(IRCCommand::_ERROR) == 0){ // エラー
                    break;
                } else{
                    // イベント生成
                    CIRCMessageData message = parser.parse(messages[index]);
                    if(message.m_statusCode == IRCCommand::OK)
                    {
                        m_isConnectedToIRCService = true;
                        m_client->getObserver()->onConnected();
                    }
                    m_client->getObserver()->onMessageReceived(&message);
                }
            }
            m_receiveBuffer = "";
        }
        // IRCプロトコルの最大値を超えるメッセージを受信している場合は、バッファをクリアする。
        if (m_receiveBuffer.Length() > 512){
            m_receiveBuffer = "";
        }
        wxUsleep(100);
    }
    // 故意でない切断時
    if (this->TestDestroy() == false){
        if (m_isConnectedToIRCService){ // IRCに接続中
            m_client->getObserver()->onDisconnected();
        } else // IRCに接続できていない
        {
            m_client->getObserver()->onConnectionFailed();
        }
    }
    // 成功時
    return (wxThread::ExitCode) 0;
}
}
} /* namespace CornStarch */
