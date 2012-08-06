#include "SCPostMessageTask.hpp"

using namespace std;

namespace CornStarch
{;
namespace StarChat
{;

CSCPostMessageTask::CSCPostMessageTask(void)
{
}


CSCPostMessageTask::~CSCPostMessageTask(void)
{
}

// 投稿するメッセージをセット
void CSCPostMessageTask::setMessage(const wxString& message)
{
    m_postMessage = message;
}
// 投稿するチャンネルをセット
void CSCPostMessageTask::setChannel(const wxString& channel)
{
    m_channel = channel;
}

//////////////////////////////////////////////////////////////////////


// StarChatに対してリクエストを送信する
void CSCPostMessageTask::sendRequestToSC(CSCClient* client)
{
    client->postMessageRequest(m_postMessage, m_channel, m_basic);
}

// HTTPレスポンスを解析してイベントを作成する
void CSCPostMessageTask::notifyMessage(const string& responseBody)
{
    CSCMessageData message;
    message.m_type = CSCMessageType::MESSAGE_REPLY;
    m_observer->onMessageReceived(&message);
}

}
}
