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
void CSCPostMessageTask::init(wxEvtHandler* handler, const wxString& channel,
    const wxString& basic)
{
    CSCTask::init(handler, basic);
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
wxThreadEvent* CSCPostMessageTask::parseHttpResponse(const string& responseBody)
{
    // 処理終了イベントを送信
    wxThreadEvent* event = new wxThreadEvent();
    event->SetEventType(myEVT_THREAD_POST_MESSAGE);
    return event;
}
