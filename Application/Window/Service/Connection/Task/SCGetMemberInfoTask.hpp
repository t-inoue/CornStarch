#pragma once
#include "SCTask.hpp"
#include "Event/GetMemberInfoEvent.hpp"

namespace CornStarch
{;

// イベントの宣言
wxDECLARE_EVENT(myEVT_THREAD_GET_MEMBER_INFO, CGetMemberInfoEvent);

namespace StarChat
{;

// メンバーの情報を取得するためのタスク
class CSCGetMemberInfoTask : public CSCTask
{
private:
    wxString m_username; // ユーザ名

public:
    CSCGetMemberInfoTask(void);
    ~CSCGetMemberInfoTask(void);

    // 初期化を行う
    void init(int connectionId,wxEvtHandler* handler, const wxString& username,
        const wxString& basic);

private:

    // StarChatに対してリクエストを送信する
    void sendRequestToSC(CSCClient* client);

    // HTTPレスポンスを解析してイベントを作成する
    CConnectionEventBase* parseHttpResponse(const std::string& responseBody);
};

}
}