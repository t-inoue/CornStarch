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


//////////////////////////////////////////////////////////////////////


// 初期化を行う
void CSCGetMemberTask::init(int connectionId,wxEvtHandler* handler, const wxString& channel,
    const wxString& basic)
{
    CSCTask::init(connectionId,handler, basic);
    m_channel = channel;
}


//////////////////////////////////////////////////////////////////////


// StarChatに対してリクエストを送信する
void CSCGetMemberTask::sendRequestToSC(CSCClient* client)
{
    // GETリクエストの送信
    client->sendGetMembersRequest(m_channel, m_basic);
}

// HTTPレスポンスを解析してイベントを作成する
CConnectionEventBase* CSCGetMemberTask::parseHttpResponse(const string& responseBody)
{
    // イベントの初期化
    CGetMemberEvent* event = new CGetMemberEvent();

    CSCJsonParser parser;
    event->setMembers(parser.getMembers(responseBody)); // 値取得
    event->SetEventType(myEVT_THREAD_GET_MEMBER); // イベントの種類をセット
    return event;
}

}
}