#pragma once
#include "SCTask.hpp"
#include "PartEvent.hpp"

namespace CornStarch
{;

// イベントの宣言
wxDECLARE_EVENT(myEVT_THREAD_DELETE_PART, CPartEvent);

namespace StarChat
{;

// チャンネルから離脱するためのタスク
class CSCPartChannelTask : public CSCTask
{
private:
    wxString m_userName; // ユーザ名
    wxString m_channel; // チャンネル名

public:
    CSCPartChannelTask(void);
    ~CSCPartChannelTask(void);

    // 初期化を行う
    void init(int connectionId,wxEvtHandler* handler, const wxString& userName,
        const wxString& channel, const wxString& basic);

private:

    // StarChatに対してリクエストを送信する
    void sendRequestToSC(CSCClient* client);

    // HTTPレスポンスを解析してイベントを作成する
    CConnectionEventBase* parseHttpResponse(const std::string& responseBody);
};

}
}