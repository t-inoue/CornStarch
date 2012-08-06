#include "SCGetMemberTask.hpp"

using namespace std;

namespace CornStarch
{;
namespace StarChat
{;

CSCGetMemberTask::CSCGetMemberTask(void)
{
}


CSCGetMemberTask::~CSCGetMemberTask(void)
{
}



// StarChatに対してリクエストを送信する
void CSCGetMemberTask::sendRequestToSC(CSCClient* client)
{
    // GETリクエストの送信
    client->sendGetMembersRequest(m_channel, m_basic);
}

// HTTPレスポンスを解析してイベントを作成する
void CSCGetMemberTask::notifyMessage(const string& responseBody)
{

    CSCJsonParser parser;
    CSCMessageData message;
    message.m_type = CSCMessageType::GET_MEMBERS;
    message.m_members= parser.getMembers(responseBody);
    message.m_channel = m_channel;
    m_observer->onMessageReceived(&message);

}

}
}
