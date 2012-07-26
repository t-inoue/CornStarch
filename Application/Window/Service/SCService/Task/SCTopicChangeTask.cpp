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


//////////////////////////////////////////////////////////////////////


// 初期化を行う
void CSCTopicChangeTask::init(int connectionId, wxEvtHandler* handler, const wxString& channel,
    const wxString& topic, const wxString& basic)
{
    CSCTask::init(connectionId, handler, basic);
    m_channel = channel;
    m_topic = topic;
}


//////////////////////////////////////////////////////////////////////


// StarChatに対してリクエストを送信する
void CSCTopicChangeTask::sendRequestToSC(CSCClient* client)
{
    // GETリクエストの送信
    client->sendChangeTopicRequest(m_channel, m_topic, m_basic);
}

// HTTPレスポンスを解析してイベントを作成する
CConnectionEventBase* CSCTopicChangeTask::parseHttpResponse(const string& responseBody)
{
    return NULL;
}

}
}