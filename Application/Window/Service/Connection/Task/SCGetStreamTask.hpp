#pragma once
#include "SCTask.hpp"
#include "Event/MsgStreamEvent.hpp"
#include "Event/ChannelStreamEvent.hpp"
#include "Event/JoinStreamEvent.hpp"
#include "Event/PartStreamEvent.hpp"
#include "Event/UserStreamEvent.hpp"

namespace CornStarch
{;

// イベントの宣言
wxDECLARE_EVENT(myEVT_THREAD_STREAM_MSG_ADD, CMsgStreamEvent);
wxDECLARE_EVENT(myEVT_THREAD_STREAM_CH_JOIN, CJoinStreamEvent);
wxDECLARE_EVENT(myEVT_THREAD_STREAM_CH_PART, CPartStreamEvent);
wxDECLARE_EVENT(myEVT_THREAD_STREAM_CH_UPDATE, CChannelStreamEvent);
wxDECLARE_EVENT(myEVT_THREAD_STREAM_USER_UPDATE, CUserStreamEvent);

namespace StarChat
{;

// ストリームを受信するためのタスク
class CSCGetStreamTask : public CSCTask
{
private:
    wxString m_userName; // ユーザ名

public:
    CSCGetStreamTask(void);
    ~CSCGetStreamTask(void);

    // 初期化を行う
    void init(int connectionId,wxEvtHandler* handler, const wxString& userName,
        const wxString& basic);

private:

    // Run実行時に呼ばれる本体
    ExitCode Entry(void);

    // Streamの内容からイベントを作成する
    CConnectionEventBase* parseStream(const std::string& json);
};

}
}