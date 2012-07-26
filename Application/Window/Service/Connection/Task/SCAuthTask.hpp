#pragma once
#include "SCTask.hpp"
#include "Event/AuthEvent.hpp"

namespace CornStarch
{;

// イベントの宣言
wxDECLARE_EVENT(myEVT_THREAD_GET_PING, CAuthEvent);

namespace StarChat
{;

// StarChatのユーザ認証を行うためのタスク
class CSCAuthTask : public CSCTask
{
private:

    wxString m_userName; // ユーザ名

public:
    CSCAuthTask(void);
    ~CSCAuthTask(void);

    // 初期化を行う
    void init(int connectionId,wxEvtHandler* handler, const wxString& userName,
        const wxString& basic);

private:

    // StarChatに対してリクエストを送信する
    void sendRequestToSC(CSCClient* client);

    // HTTPレスポンスを解析してイベントを作成する
    CConnectionEventBase* parseHttpResponse(const std::string& responseBody);
};

}
}