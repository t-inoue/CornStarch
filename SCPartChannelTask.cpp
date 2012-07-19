#include "SCPartChannelTask.hpp"

using namespace std;

CSCPartChannelTask::CSCPartChannelTask(void)
{
}


CSCPartChannelTask::~CSCPartChannelTask(void)
{
}


//////////////////////////////////////////////////////////////////////


// 行う処理をセット
void CSCPartChannelTask::init(int connectionId,wxEvtHandler* handler, const wxString& userName,
    const wxString& channel, const wxString& basic)
{
    CSCTask::init(connectionId,handler, basic);
    m_userName = userName;
    m_channel = channel;
}


//////////////////////////////////////////////////////////////////////


// StarChatに対してリクエストを送信する
void CSCPartChannelTask::sendRequestToSC(CSCClient* client)
{
    client->sendPartRequest(m_channel, m_userName, m_basic);
}

// HTTPレスポンスを解析してイベントを作成する
CConnectionEventBase* CSCPartChannelTask::parseHttpResponse(const string& responseBody)
{
    // イベントの初期化
	CConnectionEventBase* event = new CConnectionEventBase();
    event->SetEventType(myEVT_THREAD_DELETE_PART); // イベントの種類をセット
    event->SetString(m_channel);
    return event;
}
