#pragma once
#include "SCTask.hpp"

// イベントの宣言
wxDECLARE_EVENT(myEVT_THREAD_DELETE_PART, wxThreadEvent);

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
    void init(wxEvtHandler* handler, const wxString& userName,
        const wxString& channel, const wxString& basic);

private:

    // StarChatに対してリクエストを送信する
    void sendRequestToSC(CSCClient* client);

    // HTTPレスポンスを解析してイベントを作成する
    wxThreadEvent* parseHttpResponse(const std::string& responseBody);
};

