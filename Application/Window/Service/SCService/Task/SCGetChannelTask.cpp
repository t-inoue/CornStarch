#include "SCGetChannelTask.hpp"

using namespace std;

namespace CornStarch
{;
namespace StarChat
{;

CSCGetChannelTask::CSCGetChannelTask(void)
{
}


CSCGetChannelTask::~CSCGetChannelTask(void)
{
}


//////////////////////////////////////////////////////////////////////


// 初期化を行う
void CSCGetChannelTask::init(int connectionId,wxEvtHandler* handler, const wxString& userName,
    const wxString& basic)
{
    CSCTask::init(connectionId,handler, basic);
    m_userName = userName;
}


//////////////////////////////////////////////////////////////////////


// StarChatに対してリクエストを送信する
void CSCGetChannelTask::sendRequestToSC(CSCClient* client)
{
    // GETリクエストの送信
    client->sendGetChannelsRequest(m_userName, m_basic);
}

// HTTPレスポンスを解析してイベントを作成する
CConnectionEventBase* CSCGetChannelTask::parseHttpResponse(const string& responseBody)
{
    // イベントの初期化
    CGetChannelEvent* event = new CGetChannelEvent();

    CSCJsonParser parser;
    event->setChannels(parser.getChannels(responseBody)); // 値取得
    event->SetEventType(myEVT_THREAD_GET_CHANNEL); // イベントの種類をセット
    return event;
}

}
}