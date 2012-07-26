#pragma once
#include "SCTask.hpp"

namespace CornStarch
{;
namespace StarChat
{;

// ニックネーム変更を行うためのタスク
class CSCNickChangeTask : public CSCTask
{
private:
    wxString m_nick; // ニックネーム
    wxString m_name; // 本名

public:
    CSCNickChangeTask(void);
    ~CSCNickChangeTask(void);

    // 初期化を行う
    void init(int connectionId, wxEvtHandler* handler, const wxString& nick, 
        const wxString& name, const wxString& basic);

private:

    // StarChatに対してリクエストを送信する
    void sendRequestToSC(CSCClient* client);

    // HTTPレスポンスを解析してイベントを作成する
    CConnectionEventBase* parseHttpResponse(const std::string& responseBody);
};

}
}