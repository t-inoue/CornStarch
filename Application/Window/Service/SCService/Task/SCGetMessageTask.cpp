#include "SCGetMessageTask.hpp"

using namespace std;

namespace CornStarch
{;
namespace StarChat
{;

CSCGetMessageTask::CSCGetMessageTask(void)
{
}


CSCGetMessageTask::~CSCGetMessageTask(void)
{
}


//////////////////////////////////////////////////////////////////////


// 初期化を行う
void CSCGetMessageTask::init(int connectionId,wxEvtHandler* handler, const wxString& channel,
    const wxString& basic)
{
    CSCTask::init(connectionId,handler, basic);
    m_channel = channel;
}


//////////////////////////////////////////////////////////////////////


// StarChatに対してリクエストを送信する
void CSCGetMessageTask::sendRequestToSC(CSCClient* client)
{
    // GETリクエストの送信
    client->sendGetMessagesRequest(m_channel, m_basic);
}

// HTTPレスポンスを解析してイベントを作成する
CConnectionEventBase* CSCGetMessageTask::parseHttpResponse(const string& responseBody)
{
    // イベントの初期化
    CGetMessageEvent* event = new CGetMessageEvent();

    CSCJsonParser parser;
    event->setMessages(parser.getMessages(responseBody)); // 値取得
    event->SetEventType(myEVT_THREAD_GET_MESSAGE); // イベントの種類をセット
    return event;
}

}
}