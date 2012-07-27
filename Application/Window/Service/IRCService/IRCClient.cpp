#include "IRCClient.h"
namespace CornStarch
{;

wxDECLARE_EVENT(myEVT_THREAD_GET_PING, CAuthEvent);

namespace IRC
{;

using namespace std;

CIRCClient::CIRCClient() :
        m_handler(NULL), m_isClosing(false),recieveThread(NULL)
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
void CIRCClient::start(wxEvtHandler* handler, const wxString& userName,
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
    send (content);
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
void CIRCClient::quit(void)
{
    wxString content("QUIT\r\n");
    sendCommand(content);
}
void CIRCClient::disconnect(void)
{
    if(m_isClosing == false)
    {
        m_isClosing = true;
        this->close();
        if (recieveThread->IsRunning()){
            recieveThread->join();
            }
    }
}

void CIRCClient::join(const wxString& channelName)
{
    wxString content(wxString::Format(wxString("JO") + wxString("IN %s\r\n"), channelName));
    sendCommand(content);
}
void CIRCClient::part(const wxString& channelName)
{
    wxString content(wxString::Format(wxString("PA") + wxString("RT %s\r\n"), channelName));
    sendCommand(content);
}
void CIRCClient::getTopicAsync(const wxString& channelName)
{
    wxString content(wxString::Format(wxT("TOPIC %s\r\n"), channelName));
    sendCommand(content);

}
void CIRCClient::getNamesAsync(const wxString& channelName)
{
    wxString content(wxString::Format(wxT("NAMES %s\r\n"), channelName));
    sendCommand(content);
}

void CIRCClient::sendMessage(const wxString& target, const wxString& content)
{
    wxString contentWxString(
            wxString::Format(wxString("PRIV") + wxString("MSG %s %s\r\n"), target, content));
    sendCommand(contentWxString);
}
void CIRCClient::sendNotice(const wxString& target, const wxString& content)
{
    wxString contentWxString(
            wxString::Format(wxT("NOTICE %s %s\r\n"), target, content));
    sendCommand(contentWxString);
}
void CIRCClient::changeTopic(const wxString& channelName,
        const wxString& content)
{
    wxString contentWxString(
            wxString::Format(wxT("TOPIC %s %s\r\n"), channelName, content));
    sendCommand(contentWxString);
}
void CIRCClient::changeNickname(const wxString& content)
{
    wxString contentWxString(wxString::Format(wxT("NICK %s\r\n"), content));
    sendCommand(contentWxString);

}
}
} /* namespace CornStarch */
