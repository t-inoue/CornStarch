#include "SCGetMemberInfoTask.hpp"

using namespace std;

CSCGetMemberInfoTask::CSCGetMemberInfoTask(void)
{
}


CSCGetMemberInfoTask::~CSCGetMemberInfoTask(void)
{
}


//////////////////////////////////////////////////////////////////////


// 初期化を行う
void CSCGetMemberInfoTask::init(int connectionId,wxEvtHandler* handler, const wxString& username,
    const wxString& basic)
{
    CSCTask::init(connectionId,handler, basic);
    m_username = username;
}


//////////////////////////////////////////////////////////////////////


// StarChatに対してリクエストを送信する
void CSCGetMemberInfoTask::sendRequestToSC(CSCClient* client)
{
    // GETリクエストの送信
    client->sendGetMemInfoRequest(m_username, m_basic);
}

// HTTPレスポンスを解析してイベントを作成する
CConnectionEventBase* CSCGetMemberInfoTask::parseHttpResponse(const string& responseBody)
{
    // イベントの初期化
    CGetMemberInfoEvent* event = new CGetMemberInfoEvent();

    CSCJsonParser parser;
    event->setMember(parser.getMember(responseBody)); // 値取得
    event->SetEventType(myEVT_THREAD_GET_MEMBER_INFO); // イベントの種類をセット
    return event;
}
