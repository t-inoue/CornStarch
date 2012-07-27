﻿#include "SCTask.hpp"

using namespace std;

namespace CornStarch
{;
namespace StarChat
{;

CSCTask::CSCTask(void)
{
}


CSCTask::~CSCTask(void)
{
}


//////////////////////////////////////////////////////////////////////


// 初期化を行う
void CSCTask::init(int connectionId,wxEvtHandler* handler, const wxString& basic)
{
    m_handler = handler;
    m_basic = basic;
    m_connectionId = connectionId;
}


//////////////////////////////////////////////////////////////////////


// Run実行時に呼ばれる本体
wxThread::ExitCode CSCTask::Entry(void)
{
    // 通信クライアントの初期化
    CSCClient* client = new CSCClient();
    client->init();
    client->setHost(m_host);

    // 接続
    string body;
    if (client->connect()){

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
        body = client->recvHttpResponseBody();
    }

    // 通信クライアントを消す
    client->close();
    delete client;

    // スレッドが停止されていたら終了
    if (TestDestroy()){
        return (wxThread::ExitCode)-1;
    }

    // HTTPレスポンスから(newされた)Eventを取得
    CConnectionEventBase* event = parseHttpResponse(body);
    if (event != NULL){
    	event->setConnectionId(m_connectionId);
        // HTTPレスポンスを解析して、ハンドラにイベントを送る
        wxQueueEvent(m_handler, event);
    }

    // 成功時
    return (wxThread::ExitCode)0;
}

}
}