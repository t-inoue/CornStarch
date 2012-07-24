#include "SCNickChangeTask.hpp"

using namespace std;

CSCNickChangeTask::CSCNickChangeTask(void)
{
}


CSCNickChangeTask::~CSCNickChangeTask(void)
{
}


//////////////////////////////////////////////////////////////////////


// 初期化を行う
void CSCNickChangeTask::init(int connectionId, wxEvtHandler* handler, const wxString& nick,
    const wxString& name, const wxString& basic)
{
    CSCTask::init(connectionId, handler, basic);
    m_nick = nick;
    m_name = name;
}


//////////////////////////////////////////////////////////////////////


// StarChatに対してリクエストを送信する
void CSCNickChangeTask::sendRequestToSC(CSCClient* client)
{
    // GETリクエストの送信
    client->sendChangeNickRequest(m_name, m_nick, m_basic);
}

// HTTPレスポンスを解析してイベントを作成する
CConnectionEventBase* CSCNickChangeTask::parseHttpResponse(const string& responseBody)
{
    return NULL;
}
