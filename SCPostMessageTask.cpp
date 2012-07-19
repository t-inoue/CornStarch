#include "SCPostMessageTask.hpp"

using namespace std;

CSCPostMessageTask::CSCPostMessageTask(void)
{
}


CSCPostMessageTask::~CSCPostMessageTask(void)
{
}


//////////////////////////////////////////////////////////////////////

// 初期化を行う
void CSCPostMessageTask::init(int connectionId,wxEvtHandler* handler, const wxString& channel,
    const wxString& basic)
{
    CSCTask::init(connectionId,handler, basic);
    m_channel = channel;
}

// 投稿するメッセージをセット
void CSCPostMessageTask::setMessage(const wxString& message)
{
    m_postMessage = message;
}


//////////////////////////////////////////////////////////////////////


// StarChatに対してリクエストを送信する
void CSCPostMessageTask::sendRequestToSC(CSCClient* client)
{
    client->postMessageRequest(m_postMessage, m_channel, m_basic);
}

// HTTPレスポンスを解析してイベントを作成する
CConnectionEventBase* CSCPostMessageTask::parseHttpResponse(const string& responseBody)
{
    // 処理終了イベントを送信
	CConnectionEventBase* event = new CConnectionEventBase();
    event->SetEventType(myEVT_THREAD_POST_MESSAGE);
    return event;
}
