#pragma once
#include "SCTask.hpp"
#include "GetMemberInfoEvent.hpp"

// イベントの宣言
wxDECLARE_EVENT(myEVT_THREAD_GET_MEMBER_INFO, CGetMemberInfoEvent);

// メンバーの情報を取得するためのタスク
class CSCGetMemberInfoTask : public CSCTask
{
private:
    wxString m_username; // ユーザ名

public:
    CSCGetMemberInfoTask(void);
    ~CSCGetMemberInfoTask(void);

    // 初期化を行う
    void init(wxEvtHandler* handler, const wxString& username, 
        const wxString& basic);

private:

    // StarChatに対してリクエストを送信する
    void sendRequestToSC(CSCClient* client);

    // HTTPレスポンスを解析してイベントを作成する
    wxThreadEvent* parseHttpResponse(const std::string& responseBody);
};

