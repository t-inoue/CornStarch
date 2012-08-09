#include "IRCReceiveTask.hpp"
#include "../IRCParser.hpp"
#include "../IRCCommand.hpp"
#include  "../StringUtility.hpp"
#include "../../ConnectionStatusChecker.h"

namespace CornStarch
{
;

namespace IRC
{
;
CIRCReceiveTask::CIRCReceiveTask(wxThreadKind kind) :
        CIRCTask(kind), m_receiveBuffer("")
{

}

CIRCReceiveTask::~CIRCReceiveTask()
{
}
// Run実行時に呼ばれる本体
wxThread::ExitCode CIRCReceiveTask::Entry(void)
{
    // Statusチェックの間隔計測
    CConnectionStatusChecker checker(m_client->getObserver());
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
                    if (message.m_statusCode == IRCCommand::OK){
                        m_client->setConnectedToIrcService(true);
                        m_client->getObserver()->onConnected();
                    }
                    m_client->getObserver()->onMessageReceived(&message);
                }
            }
            m_receiveBuffer = "";

            // サーバーのステータスチェック計測のリセット
            checker.refreshCount();
        }
        // IRCプロトコルの最大値を超えるメッセージを受信している場合は、バッファをクリアする。
        if (m_receiveBuffer.Length() > 512){
            m_receiveBuffer = "";
        }

        // サーバーのステータスチェック
        checker.tick();
        wxUsleep(100);
    }
    if (this->TestDestroy() == false){
        if (m_client->isConnectedToIrcService()){ // IRCに接続中
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
