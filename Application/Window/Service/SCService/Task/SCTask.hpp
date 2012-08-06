#pragma once
#include <wx/wxprec.h>
#include <wx/wx.h>
#include "../SCClient.hpp"
#include "../SCJsonParser.hpp"
#include "../SCMessageData.hpp"


namespace CornStarch
{;
namespace StarChat
{;

// スターチャットと通信を行うためのクラス
class CSCTask : public wxThread
{
protected:
    IMessageConnectionObserver* m_observer;

    wxString m_basic; // basic認証用文字列
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
    // 初期化を行う
    void init(IMessageConnectionObserver* observer, const wxString& basic);


protected:

    // Run実行時に呼ばれる本体
    virtual ExitCode Entry(void);

    // StarChatに対してリクエストを送信する
    virtual void sendRequestToSC(CSCClient* client) {};

    // HTTPレスポンスを解析してメッセージを通知する
    virtual void notifyMessage(const std::string& responseBody) {};
};

}
}
