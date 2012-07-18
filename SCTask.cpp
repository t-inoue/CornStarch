#include "SCTask.hpp"

using namespace std;

CSCTask::CSCTask(void)
{
}


CSCTask::~CSCTask(void)
{
}


//////////////////////////////////////////////////////////////////////


// 初期化を行う
void CSCTask::init(wxEvtHandler* handler, const wxString& basic)
{
    m_handler = handler;
    m_basic = basic;
}


//////////////////////////////////////////////////////////////////////


// Run実行時に呼ばれる本体
wxThread::ExitCode CSCTask::Entry(void)
{
    // 通信クライアントの初期化
    CSCClient* client = new CSCClient();
    client->init();

    // 接続
    client->connect();

    // リクエストを送信する
    sendRequestToSC(client);

    // 通信が可能となるまで待機
    while(!client->waitRecv()){

        // スレッド廃棄要求が来たら終了
        if (TestDestroy()){

            // 通信クライアントを消す
            client->close();
            delete client;
            return (wxThread::ExitCode)-1;
        }
    }

    // レスポンスボディを受信する
    string body = client->recvHttpResponseBody();

    // 通信クライアントを消す
    client->close();
    delete client;

    // スレッドが停止されていたら終了
    if (TestDestroy()){
        return (wxThread::ExitCode)-1;
    }

    // HTTPレスポンスから(newされた)Eventを取得
    wxThreadEvent* event = parseHttpResponse(body);
    if (event != NULL){
        // HTTPレスポンスを解析して、ハンドラにイベントを送る
        wxQueueEvent(m_handler, event);
    }

    // 成功時
    return (wxThread::ExitCode)0;
}
