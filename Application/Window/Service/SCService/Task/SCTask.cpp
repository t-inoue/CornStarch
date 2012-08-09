#include "SCTask.hpp"

using namespace std;

namespace CornStarch
{
;
namespace StarChat
{
;

CSCTask::CSCTask(wxThreadKind kind) :
        wxThread(kind)
{
}

CSCTask::~CSCTask(void)
{
}

//////////////////////////////////////////////////////////////////////

// 初期化を行う
void CSCTask::init(IMessageConnectionObserver* observer, const wxString& basic)
{
    m_basic = basic;
    m_observer = observer;
}

//////////////////////////////////////////////////////////////////////

// Run実行時に呼ばれる本体
wxThread::ExitCode CSCTask::Entry(void)
{
    // 通信クライアントの初期化
    CSCClient* client = new CSCClient();
    client->init();
    client->setHost(m_host);
    client->setPort(m_port);
    // 接続
    string body;
    if (client->connect()){

        // リクエストを送信する
        sendRequestToSC(client);

        // 通信が可能となるまで待機
        if (client->waitRecv(5000, 5) == false){
            m_observer->onDisconnected();
            // 通信クライアントを消す
            client->close();
            delete client;
            return (wxThread::ExitCode) -1;
        }

        // レスポンスボディを受信する
        body = client->recvHttpResponseBody();
    }

    // 通信クライアントを消す
    client->close();
    delete client;

    // スレッドが停止されていたら終了
    if (TestDestroy()){
        return (wxThread::ExitCode) -1;
    }
    notifyMessage(body);

    // 成功時
    return (wxThread::ExitCode) 0;
}

}
}
