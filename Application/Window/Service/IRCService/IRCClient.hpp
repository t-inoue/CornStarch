
#ifndef _IRCClient_h
#define _IRCClient_h
#include "../SocketClient.hpp"
#include "IRCParser.hpp"
#include "Thread.hpp"
#include "../../../header.hpp"
#include <wx/wxprec.h>
#include <wx/wx.h>
#include <wx/msgqueue.h>

namespace CornStarch
{
namespace IRC
{
// IRCと接続するためのクライントクラスです。
class CIRCClient: public CSocketClient
{

    wxMessageQueue<wxString> *m_commandQueue;
    // 受信用のスレッドです。
    wxThread *m_receiveTask;
    wxThread *m_sendTask;
    //Thread *recieveThread;
    // ミューテックス
    wxMutex *m_mutex;
    // ホスト名です。
    wxString m_host;
//    // ポート番号です
//    wxString m_port;
    // コネクションIDです。
    int m_connectionId;

    // 切断中かを示します。
    bool m_isClosing;
    wxEvtHandler* m_handler;

    // ハートビートへの反応です。
//    void pong(const wxString& value);
//    //IRCへ接続します。
//    void connect(const wxString& userName,const wxString& password);

    // スレッドを開始します。
    void startThread(wxThread* task);
public:
    CIRCClient();
    virtual ~CIRCClient(void);
    // 初期化します。
    void init(int connectionId, wxEvtHandler* handler);
    // 通信を開始します。
    void startAsync(const wxString& userName, const wxString& password);

    // コマンドをスレッドセーフで送信します。
    void sendCommand(const wxString& command);

    void addCommandQueue(const wxString& target);
    // 受信ループです。
    void receiveLoop(void);

    // Quitメッセージを送ります。
    void quitAsync(void);

    // IRCから切断します。
    void disconnect(void);
    // メッセージを送ります。
    void sendMessageAsync(const wxString& target, const wxString& content);
    // Noticeを送ります。
    void sendNoticeAsync(const wxString& target, const wxString& content);
    // チャンネルに参加します。
    void joinAsync(const wxString& channelName);
    // チャンネルから離脱します。
    void partAsync(const wxString& channelName);
    // トピックを変更します。
    void changeTopicAsync(const wxString& channelName, const wxString& content);
    // ニックネームを変更します。
    void changeNicknameAsync(const wxString& content);

    // トピックを非同期で取得します。
    void getTopicAsync(const wxString& channelName);
    // 名前一覧を非同期で取得します。
    void getNamesAsync(const wxString& channelName);

    wxString recieveData();

    wxMessageQueue<wxString>* getCommandQueue() const
     {
         return m_commandQueue;
     }

     void setCommandQueue(wxMessageQueue<wxString>* commandQueue)
     {
         m_commandQueue = commandQueue;
     }

    bool isSocketConnected() const
    {
        return m_socket->IsConnected();
    }

    // ホストを取得
    wxString getHost() const
    {
        return m_host;
    }
    // ホストを設定
    void setHost(wxString host)
    {
        m_host = host;
    }
//    wxString getPort() const
//    {
//        return m_port;
//    }

//    void setPort(wxString port)
//    {
//        m_port = port;
//    }
//    wxString getBuffer() const
//    {
//        return m_buffer;
//    }
//    void setBuffer(wxString value)
//    {
//        m_buffer = value;
//    }

    bool isClosing() const
    {
        return m_isClosing;
    }

    void setClosing(bool isClosing)
    {
        m_isClosing = isClosing;
    }
}

;
}
} /* namespace CornStarch */

#endif
