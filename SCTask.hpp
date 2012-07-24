#pragma once
#include "SCClient.hpp"
#include "header.hpp"
#include "SCJsonParser.hpp"
#include "ConnectionEventBase.hpp"

// スターチャットと通信を行うためのクラス
class CSCTask : public wxThread
{
protected:

    wxEvtHandler* m_handler; // 処理終了を受け取るハンドラ
    wxString m_basic; // basic認証用文字列
    int m_connectionId; // コネクションのID
    wxString m_host;
public:
    CSCTask(void);
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
