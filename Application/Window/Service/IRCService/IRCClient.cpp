#include "IRCClient.hpp"
namespace CornStarch
{
;

wxDECLARE_EVENT(myEVT_THREAD_GET_PING, CAuthEvent);

namespace IRC
{
;

using namespace std;

CIRCClient::CIRCClient() :
        m_handler(NULL), m_isClosing(false), recieveThread(NULL)
{
    m_mutex = new wxMutex();

}

CIRCClient::~CIRCClient(void)
{
    delete m_mutex;
}
void CIRCClient::init(int connectionId)
{
    CSocketClient::init();
    m_connectionId = connectionId;
}
void CIRCClient::startAsync(wxEvtHandler* handler, const wxString& userName,
        const wxString& password)
{
    if (m_socket->IsConnected()){
        return;
    }

    m_handler = handler;

    wxString pass(
            wxString::Format(wxT( "PASS %s\r\nNICK %s\r\nUSER %s * 0 :%s\r\n"),
                    password.c_str(), userName.c_str(), userName.c_str(),
                    userName.c_str()));

    Thread *thread = new Thread(this, &CIRCClient::connect, pass);
    thread->start();
}

void CIRCClient::connect(const wxString& content)
{
    setPort(this->m_port);
    setUrl(this->m_host);
    CSocketClient::connect();
    //　IRCへの接続
    sendCommand(content);

    recieveThread = new Thread(this, &CIRCClient::receiveLoop);
    recieveThread->start();
}
void CIRCClient::sendCommand(const wxString& content)
{
    m_mutex->Lock();
    send(content);
    m_mutex->Unlock();
}
void CIRCClient::receiveLoop()
{
    CIRCParser parser;
    while (m_socket->IsConnected()){
        this->m_buffer = "";

        receive();
        if (this->m_buffer != ""){
            vector<string> messages = CStringUtility::split(this->m_buffer,
                    "\n");
            for (int i = 0; i < messages.size(); i++){
                if (messages[i].find(string("PI") + "NG") == 0){
                    string pingValue =
                            CStringUtility::split(messages[i], ":")[1];
                    pong(pingValue);
                } else{
                    CConnectionEventBase* event = parser.parse(messages[i]);
                    if (event != NULL){
                        event->setConnectionId(m_connectionId);
                        wxQueueEvent(m_handler, event);
                    }
                }
            }
        }
        usleep(500);
    }
    if (m_isClosing != true){
        CAuthEvent* event = new CAuthEvent();
        event->setAuthResult(false);
        event->SetEventType(myEVT_THREAD_GET_PING); // イベントの種類をセット
        event->setConnectionId(m_connectionId);
        wxQueueEvent(m_handler, event);
    }
}
void CIRCClient::pong(const wxString& value)
{
    wxString content(wxString::Format(wxT("PONG %s\r\n"), value));
    sendCommand(content);
}
void CIRCClient::quitAsync(void)
{
    wxString content("QUIT\r\n");

    Thread *thread =new Thread(this, &CIRCClient::sendCommand,content);
    thread->start();
}
void CIRCClient::disconnect(void)
{
    if (m_isClosing == false){
        m_isClosing = true;
        this->close();
        if (recieveThread != NULL&& recieveThread->IsAlive()){
            if (recieveThread->IsRunning()){
                recieveThread->join();
            }
        }
    }
}

void CIRCClient::joinAsync(const wxString& channelName)
{
    wxString content(
            wxString::Format(wxString("JO") + wxString("IN %s\r\n"),
                    channelName));
    Thread *thread =new Thread(this, &CIRCClient::sendCommand,content);
    thread->start();

    // イベントを通知
    CChannelData *channelData = new CChannelData();
    channelData->m_name = channel;
    channelData->m_topic = "";
    m_channels.push_back(channelData);

    CJoinEvent* event = new CJoinEvent();
    event->SetEventType(myEVT_THREAD_PUT_JOIN); // イベントの種類をセット
    event->SetString(channel); // 新チャンネル名
    event->setConnectionId(m_connectionId);
    wxQueueEvent(m_handler, event);
}
void CIRCClient::partAsync(const wxString& channelName)
{
    wxString content(
            wxString::Format(wxString("PA") + wxString("RT %s\r\n"),
                    channelName));
    Thread *thread =new Thread(this, &CIRCClient::sendCommand,content);
    thread->start();
}
void CIRCClient::getTopicAsync(const wxString& channelName)
{
    wxString content(wxString::Format(wxT("TOPIC %s\r\n"), channelName));
    Thread *thread =new Thread(this, &CIRCClient::sendCommand,content);
    thread->start();

}
void CIRCClient::getNamesAsync(const wxString& channelName)
{
    wxString content(wxString::Format(wxT("NAMES %s\r\n"), channelName));
    Thread *thread =new Thread(this, &CIRCClient::sendCommand,content);
    thread->start();
}

void CIRCClient::sendMessageAsync(const wxString& target, const wxString& content)
{
    wxString contentWxString(
            wxString::Format(wxString("PRIV") + wxString("MSG %s %s\r\n"),
                    target, content));
    Thread *thread =new Thread(this, &CIRCClient::sendCommand,content);
    thread->start();
}
void CIRCClient::sendNoticeAsync(const wxString& target, const wxString& content)
{
    wxString contentWxString(
            wxString::Format(wxT("NOTICE %s %s\r\n"), target, content));
    Thread *thread =new Thread(this, &CIRCClient::sendCommand,content);
    thread->start();
}
void CIRCClient::changeTopicAsync(const wxString& channelName,
        const wxString& content)
{
    wxString contentWxString(
            wxString::Format(wxT("TOPIC %s %s\r\n"), channelName, content));
    Thread *thread =new Thread(this, &CIRCClient::sendCommand,content);
    thread->start();
}
void CIRCClient::changeNicknameAsync(const wxString& content)
{
    wxString contentWxString(wxString::Format(wxT("NICK %s\r\n"), content));
    Thread *thread =new Thread(this, &CIRCClient::sendCommand,content);
    thread->start();

}
}
} /* namespace CornStarch */
