#include "SCJoinChannelTask.hpp"

using namespace std;

CSCJoinChannelTask::CSCJoinChannelTask(void)
{
}


CSCJoinChannelTask::~CSCJoinChannelTask(void)
{
}


//////////////////////////////////////////////////////////////////////


// 行う処理をセット
void CSCJoinChannelTask::init(wxEvtHandler* handler, const wxString& userName,
    const wxString& channel, const wxString& basic)
{
    CSCTask::init(handler, basic);
    m_userName = userName;
    m_channel = channel;
}


//////////////////////////////////////////////////////////////////////


// StarChatに対してリクエストを送信する
void CSCJoinChannelTask::sendRequestToSC(CSCClient* client)
{
    client->sendJoinRequest(m_channel, m_userName, m_basic);
}

// HTTPレスポンスを解析してイベントを作成する
wxThreadEvent* CSCJoinChannelTask::parseHttpResponse(const string& responseBody)
{
    // イベントの初期化
    CJoinEvent* event = new CJoinEvent();
    event->SetEventType(myEVT_THREAD_PUT_JOIN); // イベントの種類をセット
    event->SetString(m_channel.c_str()); // 新チャンネル名
    return event;
}
