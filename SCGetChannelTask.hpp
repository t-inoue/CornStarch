#pragma once
#include "SCTask.hpp"
#include "GetChannelEvent.hpp"

// イベントの宣言
wxDECLARE_EVENT(myEVT_THREAD_GET_CHANNEL, CGetChannelEvent);

// チャンネルを別スレッドで取得するためのタスク
class CSCGetChannelTask : public CSCTask
{
private:
    wxString m_userName; // ユーザ名

public:
    CSCGetChannelTask(void);
    ~CSCGetChannelTask(void);

    // 初期化を行う
    void init(wxEvtHandler* handler, const wxString& userName, 
        const wxString& basic);

private:

    // StarChatに対してリクエストを送信する
    void sendRequestToSC(CSCClient* client);

    // HTTPレスポンスを解析してイベントを作成する
    wxThreadEvent* parseHttpResponse(const std::string& responseBody);
};

