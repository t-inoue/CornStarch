#pragma once
#include "SCClient.hpp"
#include "header.hpp"
#include "SCJsonParser.hpp"

// スターチャットと通信を行うためのクラス
class CSCTask : public wxThread
{
protected:

    wxEvtHandler* m_handler; // 処理終了を受け取るハンドラ
    wxString m_basic; // basic認証用文字列

public:
    CSCTask(void);
    virtual ~CSCTask(void);

protected:

    // 初期化を行う
    void init(wxEvtHandler* handler, const wxString& basic);

protected:

    // Run実行時に呼ばれる本体
    virtual ExitCode Entry(void);

    // StarChatに対してリクエストを送信する
    virtual void sendRequestToSC(CSCClient* client){}

    // HTTPレスポンスを解析してイベントを作成する
    virtual wxThreadEvent* parseHttpResponse(const std::string& responseBody){return NULL;}
};
