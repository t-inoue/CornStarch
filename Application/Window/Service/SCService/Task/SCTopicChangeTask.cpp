#include "SCTopicChangeTask.hpp"

using namespace std;

namespace CornStarch
{;
namespace StarChat
{;

CSCTopicChangeTask::CSCTopicChangeTask(void)
{
}


CSCTopicChangeTask::~CSCTopicChangeTask(void)
{
}



// StarChatに対してリクエストを送信する
void CSCTopicChangeTask::sendRequestToSC(CSCClient* client)
{
    // GETリクエストの送信
    client->sendChangeTopicRequest(m_channel, m_topic, m_basic);
}

// HTTPレスポンスを解析してイベントを作成する
void CSCTopicChangeTask::notifyMessage(const string& responseBody)
{
}

}
}
