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



// StarChatに対してリクエストを送信する
void CSCGetChannelTask::sendRequestToSC(CSCClient* client)
{
    // GETリクエストの送信
    client->sendGetChannelsRequest(m_userName, m_basic);
}

// HTTPレスポンスを解析してイベントを作成する
void CSCGetChannelTask::notifyMessage(const string& responseBody)
{
    CSCJsonParser parser;
    CSCMessageData message;
    message.m_type = CSCMessageType::GET_CHANNEL;
    message.m_channels = parser.getChannels(responseBody);
    m_observer->onMessageReceived(&message);
//    // イベントの初期化
//    CGetChannelEvent* event = new CGetChannelEvent();
//
//    event->setChannels(parser.getChannels(responseBody)); // 値取得
//    event->SetEventType(myEVT_THREAD_GET_CHANNEL); // イベントの種類をセット
//    return event;
}

}
}
