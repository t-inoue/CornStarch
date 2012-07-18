#pragma once
#include "SocketClient.hpp"
#include "sstream"

// HTTP通信を行うためのクライアントクラス
class CHttpClient : public CSocketClient
{

protected:

    static const wxString HTTP_PORT; // ポート番号
    static const wxString HOST_NAME; // ホスト名
    static const wxString HTTP_VER; // HTTP/1.1

public:

    CHttpClient(void);
    virtual ~CHttpClient(void);

    // 初期化を行う
    void init(void);

    // HTTPレスポンスを受信して、Bodyを返す
    std::string recvHttpResponseBody(void);

protected:

    // HTTPリクエストメソッドの行を送信する
    void sendRequestMethod(const wxString& method, const wxString& uri);

    // HTTPレスポンスのbody部を取得する
    std::string getResponceBody(const std::string& str) const;

    // POST時のデフォルトリクエストヘッダ
    void sendPostDefault(const wxString& str, const wxString& basic);

    // GET時のデフォルトリクエストヘッダ
    void sendGetDefault(const wxString& basic);

    // PUT時のデフォルトリクエストヘッダ
    void sendPutDefault(const wxString& basic);

    // DELETE時のデフォルトリクエストヘッダ
    void sendDeleteDefault(const wxString& basic);

    // stream時のデフォルトリクエストヘッダ
    void sendStreamDefault(const wxString& basic);

    // レスポンスがHTTPレスポンスとして完結しているかを判断する
    bool isCorrectHttpResponse(void) const;

private:

    // 共通部分となるHTTPヘッダを送る
    void sendCommonHeader(int length, const wxString& basic);

private:

    // Hostを送る
    void sendHost(void);

    // Basic認証を行う行を送る
    void sendAuth(const wxString& basic);

    // Acceptを送る
    void sendAccept(void);

    // Content-Lengthを送る
    void sendLength(int length);

    // Keep-Alive
    void sendKeepAlive(void);

    // bodyを送る
    void sendBody(const wxString& body);

};

