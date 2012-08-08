
#ifndef _IRCClient_h
#define _IRCClient_h
#include "../SocketClient.hpp"
#include "IRCParser.hpp"
#include "../../../header.hpp"
#include "../IMessageConnectionObserver.hpp"
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
    // 送信用コマンドキュー
    wxMessageQueue<wxString> *m_commandQueue;
    // 接続用のスレッドです。
    wxThread *m_conenctTask;
    // 受信用のスレッドです。
    wxThread *m_receiveTask;
    // 送信用のスレッドです。
    wxThread *m_sendTask;
    // ホスト名です。
    wxString m_host;

    //メッセージオブザーバー
    IMessageConnectionObserver* m_observer;

    // スレッドを開始します。
    void startThread(wxThread* task);


public:
    // Queueに送信コマンドを追加します。
    void addCommandQueue(const wxString& target);
    CIRCClient();
    virtual ~CIRCClient(void);
    // 初期化します。
    void init(IMessageConnectionObserver* observer);
    // 通信を開始します。
    void startAsync(const wxString& userName, const wxString& password);
    // pong応答を返します。
    void pong(const wxString& value);
    // コマンドをスレッドセーフで送信します。
    void sendCommand(const wxString& command);


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

    // ソケットからデータを受信します。
    wxString recieveData();

    IMessageConnectionObserver* getObserver() const
    {
        return m_observer;
    }
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

}

;
}
} /* namespace CornStarch */

#endif
