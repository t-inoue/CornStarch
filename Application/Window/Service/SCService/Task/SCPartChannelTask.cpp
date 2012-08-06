#include "SCPartChannelTask.hpp"

using namespace std;

namespace CornStarch
{;
namespace StarChat
{;

CSCPartChannelTask::CSCPartChannelTask(void)
{
}


CSCPartChannelTask::~CSCPartChannelTask(void)
{
}


// StarChatに対してリクエストを送信する
void CSCPartChannelTask::sendRequestToSC(CSCClient* client)
{
    client->sendPartRequest(m_channel, m_userName, m_basic);
}

// HTTPレスポンスを解析してイベントを作成する
void CSCPartChannelTask::notifyMessage(const string& responseBody)
{
    CSCMessageData message;
    message.m_type = CSCMessageType::PART_REPLY;
    message.m_channel = m_channel;
    m_observer->onMessageReceived(&message);

}

}
}
