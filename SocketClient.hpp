#pragma once
#include <wx/socket.h>
#include <wx/string.h>

// ソケット通信を行うクライアント
class CSocketClient
{
protected:

    static const int MAX_LENGTH = 200000; // 最大受信サイズ(byte)
    wxIPV4address* m_address; // ソケットアドレス情報
    std::string m_buffer; // 受信文字列
    wxSocketClient* m_socket;

public:

    CSocketClient(void);
    virtual ~CSocketClient(void);

    // クライアントの初期化を行う
    virtual void init(void);

    // 改行込みで接続を行う
    bool connect(void);

    // 接続を閉じる
    void close(void);

    // ポート番号をセット
    void setPort(const wxString& port);

    // ホスト名からIPアドレスをセット
    void setUrl(const wxString& url);

    // 指定された時間受信待機する。
    // 受信可能なら正の値(1)、不可なら0
    int waitRecv(int usec = 1000, int sec = 0);

protected:

    // 受信を行う(待機デフォルト1000usec)
    int receive(long waitTimeUsec = 1000);

    // 送信を行う
    void send(const wxString& message);

    // 改行を送信する
    void sendLF(void);

};

