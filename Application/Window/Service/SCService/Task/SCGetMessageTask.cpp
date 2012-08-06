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


// StarChatに対してリクエストを送信する
void CSCGetMessageTask::sendRequestToSC(CSCClient* client)
{
    // GETリクエストの送信
    client->sendGetMessagesRequest(m_channel, m_basic);
}

// HTTPレスポンスを解析してイベントを作成する
void CSCGetMessageTask::notifyMessage(const string& responseBody)
{
    CSCJsonParser parser;
     CSCMessageData message;
     message.m_type = CSCMessageType::GET_MESSAGES;
     message.m_messages = parser.getMessages(responseBody);
     message.m_channel = m_channel;
     m_observer->onMessageReceived(&message);
}

}
}
