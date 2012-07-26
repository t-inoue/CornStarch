#include "SCAuthTask.hpp"

using namespace std;

namespace CornStarch
{;
namespace StarChat
{;

CSCAuthTask::CSCAuthTask(void)
{
}


CSCAuthTask::~CSCAuthTask(void)
{
}


//////////////////////////////////////////////////////////////////////


// 初期化を行う
void CSCAuthTask::init(int connectionId,wxEvtHandler* handler, const wxString& userName,
    const wxString& basic)
{
    CSCTask::init(connectionId,handler, basic);
    m_userName = userName;
}


//////////////////////////////////////////////////////////////////////


// StarChatに対してリクエストを送信する
void CSCAuthTask::sendRequestToSC(CSCClient* client)
{
    // GETリクエストの送信
    client->sendPingRequest(m_userName, m_basic);
}

// HTTPレスポンスを解析してイベントを作成する
CConnectionEventBase* CSCAuthTask::parseHttpResponse(const string& responseBody)
{
    // レスポンスボディの内容を基に、イベントをセットする
    CSCJsonParser parser;
    CAuthEvent* event = new CAuthEvent();
    event->setAuthResult(parser.isPingSucceeded(responseBody)); // 値取得
    event->SetEventType(myEVT_THREAD_GET_PING); // イベントの種類をセット
    return event;
}

}
}