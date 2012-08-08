#include "SCAuthTask.hpp"

using namespace std;

namespace CornStarch
{
;
namespace StarChat
{
;

CSCAuthTask::CSCAuthTask(void)
{
}

CSCAuthTask::~CSCAuthTask(void)
{
}

// StarChatに対してリクエストを送信する
void CSCAuthTask::sendRequestToSC(CSCClient* client)
{
    // GETリクエストの送信
    client->sendPingRequest(m_userName, m_basic);
}

// HTTPレスポンスを解析してイベントを作成する
void CSCAuthTask::notifyMessage(const string& responseBody)
{
    CSCJsonParser parser;
    bool isSucceed = parser.isPingSucceeded(responseBody);
    if (isSucceed){
        m_observer->onConnected();
    }
    else
    {
        m_observer->onConnectionFailed();
    }
}
}
}
