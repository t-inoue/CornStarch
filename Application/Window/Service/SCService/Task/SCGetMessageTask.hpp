#pragma once
#include "SCTask.hpp"

namespace CornStarch
{;

// イベントの宣言
wxDECLARE_EVENT(myEVT_THREAD_GET_MESSAGE, CGetMessageEvent);

namespace StarChat
{;

// メッセージ取得を別スレッドで取得するためのタスク
class CSCGetMessageTask : public CSCTask
{
private:
    wxString m_channel; // チャンネル名

public:
    CSCGetMessageTask(void);
    ~CSCGetMessageTask(void);

    // 初期化を行う
    void init(int connectionId,wxEvtHandler* handler, const wxString& channel,
        const wxString& basic);

private:

    // StarChatに対してリクエストを送信する
    void sendRequestToSC(CSCClient* client);

    // HTTPレスポンスを解析してイベントを作成する
    CConnectionEventBase* parseHttpResponse(const std::string& responseBody);
};

}
}