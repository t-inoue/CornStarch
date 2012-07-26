#pragma once
#include "SCTask.hpp"

namespace CornStarch
{;
namespace StarChat
{;

// トピックを変更するためのタスク
class CSCTopicChangeTask : public CSCTask
{
private:
    wxString m_channel; // チャンネル名
    wxString m_topic; // 新トピック

public:
    CSCTopicChangeTask(void);
    ~CSCTopicChangeTask(void);

    // 初期化を行う
    void init(int connectionId, wxEvtHandler* handler, const wxString& channel,
        const wxString& topic, const wxString& basic);

private:

    // StarChatに対してリクエストを送信する
    void sendRequestToSC(CSCClient* client);

    // HTTPレスポンスを解析してイベントを作成する
    CConnectionEventBase* parseHttpResponse(const std::string& responseBody);
};

}
}