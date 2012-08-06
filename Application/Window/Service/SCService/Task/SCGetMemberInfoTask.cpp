#include "SCGetMemberInfoTask.hpp"

using namespace std;

namespace CornStarch
{;
namespace StarChat
{;

CSCGetMemberInfoTask::CSCGetMemberInfoTask(void)
{
}


CSCGetMemberInfoTask::~CSCGetMemberInfoTask(void)
{
}

// StarChatに対してリクエストを送信する
void CSCGetMemberInfoTask::sendRequestToSC(CSCClient* client)
{
    // GETリクエストの送信
    client->sendGetMemInfoRequest(m_username, m_basic);
}

// HTTPレスポンスを解析してイベントを作成する
void CSCGetMemberInfoTask::notifyMessage(const string& responseBody)
{
    CSCJsonParser parser;
    CSCMessageData message;
    message.m_type = CSCMessageType::GET_MEMBER;
    message.m_member = parser.getMember(responseBody);
    m_observer->onMessageReceived(&message);
}

}
}
