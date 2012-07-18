#pragma once
#include "SCTask.hpp"
#include "AuthEvent.hpp"

// イベントの宣言
wxDECLARE_EVENT(myEVT_THREAD_GET_PING, CAuthEvent);

// StarChatのユーザ認証を行うためのタスク
class CSCAuthTask : public CSCTask
{
private:

    wxString m_userName; // ユーザ名

public:
    CSCAuthTask(void);
    ~CSCAuthTask(void);

    // 初期化を行う
    void init(wxEvtHandler* handler, const wxString& userName, 
        const wxString& basic);

private:

    // StarChatに対してリクエストを送信する
    void sendRequestToSC(CSCClient* client);

    // HTTPレスポンスを解析してイベントを作成する
    wxThreadEvent* parseHttpResponse(const std::string& responseBody);
};

