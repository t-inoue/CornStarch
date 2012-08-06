#include "SCJoinChannelTask.hpp"

using namespace std;

namespace CornStarch
{;
namespace StarChat
{;

CSCJoinChannelTask::CSCJoinChannelTask(void)
{
}


CSCJoinChannelTask::~CSCJoinChannelTask(void)
{
}




// StarChatに対してリクエストを送信する
void CSCJoinChannelTask::sendRequestToSC(CSCClient* client)
{
    client->sendJoinRequest(m_channel, m_userName, m_basic);
}

// HTTPレスポンスを解析してイベントを作成する
void CSCJoinChannelTask::notifyMessage(const string& responseBody)
{
     CSCMessageData message;
     message.m_type = CSCMessageType::JOIN_REPLY;
     message.m_channel = m_channel;
     m_observer->onMessageReceived(&message);

}

}
}
