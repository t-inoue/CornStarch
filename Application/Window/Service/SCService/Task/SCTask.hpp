#pragma once
#include <wx/wxprec.h>
#include <wx/wx.h>
#include "../SCClient.hpp"
#include "../SCJsonParser.hpp"
#include "../../Event/ConnectionEventBase.hpp"
#include "../../Event/PartEvent.hpp"
#include "../../Event/AuthEvent.hpp"
#include "../../Event/JoinEvent.hpp"
#include "../../Event/MsgStreamEvent.hpp"
#include "../../Event/ChannelStreamEvent.hpp"
#include "../../Event/JoinStreamEvent.hpp"
#include "../../Event/PartStreamEvent.hpp"
#include "../../Event/UserStreamEvent.hpp"
#include "../../Event/GetMessageEvent.hpp"
#include "../../Event/GetMemberEvent.hpp"
#include "../../Event/GetMemberInfoEvent.hpp"
#include "../../Event/GetChannelEvent.hpp"

namespace CornStarch
{;
namespace StarChat
{;

// スターチャットと通信を行うためのクラス
class CSCTask : public wxThread
{
protected:

    wxEvtHandler* m_handler; // 処理終了を受け取るハンドラ
    wxString m_basic; // basic認証用文字列
    int m_connectionId; // コネクションのID
    wxString m_host;
public:
    CSCTask(wxThreadKind king = wxTHREAD_DETACHED);
    virtual ~CSCTask(void);

    // ホストを取得します。
	wxString getHost() const
	{
		return m_host;
	}
	// ホストを設定します。
	void setHost(wxString host)
	{
		m_host = host;
	}
protected:

    // 初期化を行う
    void init(int connectionId,wxEvtHandler* handler, const wxString& basic);

protected:

    // Run実行時に呼ばれる本体
    virtual ExitCode Entry(void);

    // StarChatに対してリクエストを送信する
    virtual void sendRequestToSC(CSCClient* client) {};

    // HTTPレスポンスを解析してイベントを作成する
    virtual CConnectionEventBase* parseHttpResponse(const std::string& responseBody) {return NULL;};
};

}
}
