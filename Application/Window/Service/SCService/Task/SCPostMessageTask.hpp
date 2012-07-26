#pragma once
#include "SCTask.hpp"

namespace CornStarch
{;

// イベントの宣言
wxDECLARE_EVENT(myEVT_THREAD_POST_MESSAGE, wxThreadEvent);

namespace StarChat
{;


// 別スレッドでコメントの投稿を行う
class CSCPostMessageTask : public CSCTask
{
private:

    wxString m_postMessage; // 投稿するメッセージ
    wxString m_channel; // チャンネル名

public:
    CSCPostMessageTask(void);
    ~CSCPostMessageTask(void);

    // 初期化を行う
    void init(int connectionId,wxEvtHandler* handler, const wxString& channel,
        const wxString& basic);

    // 投稿するメッセージをセット
    void setMessage(const wxString& message);

private:

    // StarChatに対してリクエストを送信する
    void sendRequestToSC(CSCClient* client);

    // HTTPレスポンスを解析してイベントを作成する
    CConnectionEventBase* parseHttpResponse(const std::string& responseBody);
};

}
}