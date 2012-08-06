#include "SCNickChangeTask.hpp"

using namespace std;

namespace CornStarch
{;
namespace StarChat
{;

CSCNickChangeTask::CSCNickChangeTask(void)
{
}


CSCNickChangeTask::~CSCNickChangeTask(void)
{
}



// StarChatに対してリクエストを送信する
void CSCNickChangeTask::sendRequestToSC(CSCClient* client)
{
    // GETリクエストの送信
    client->sendChangeNickRequest(m_name, m_nick, m_basic);
}

// HTTPレスポンスを解析してイベントを作成する
void CSCNickChangeTask::notifyMessage(const string& responseBody)
{
}

}
}
