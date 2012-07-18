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
void CSCGetMemberInfoTask::init(wxEvtHandler* handler, const wxString& username,
    const wxString& basic)
{
    CSCTask::init(handler, basic);
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
wxThreadEvent* CSCGetMemberInfoTask::parseHttpResponse(const string& responseBody)
{
    // イベントの初期化
    CGetMemberInfoEvent* event = new CGetMemberInfoEvent();

    CSCJsonParser parser;
    event->setMember(parser.getMember(responseBody)); // 値取得
    event->SetEventType(myEVT_THREAD_GET_MEMBER_INFO); // イベントの種類をセット
    return event;
}
