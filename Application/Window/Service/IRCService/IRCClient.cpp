#include "IRCClient.h"

namespace CornStarch
{;

wxDECLARE_EVENT(myEVT_THREAD_GET_PING, CAuthEvent);

namespace IRC
{;

using namespace std;

CIRCClient::CIRCClient() : m_handler(NULL), m_isClosing(false)
{

}

CIRCClient::~CIRCClient(void)
{
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
    send(content);

    Thread *thread = new Thread(this, &CIRCClient::receiveLoop, true);
    thread->start();
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
                if (messages[i].find("PING") == 0){
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
    send(content);
}
void CIRCClient::quit(void)
{
    wxString content("QUIT\r\n");
    send(content);
}
void CIRCClient::disconnect(void)
{
    m_isClosing = true;
    this->close();
}

void CIRCClient::join(const wxString& channelName)
{
    wxString content(wxString::Format(wxT("JOIN %s\r\n"), channelName));
    send(content);
}
void CIRCClient::part(const wxString& channelName)
{
    wxString content(wxString::Format(wxT("PART %s\r\n"), channelName));
    send(content);
}
void CIRCClient::getTopicAsync(const wxString& channelName)
{
    wxString content(wxString::Format(wxT("TOPIC %s\r\n"), channelName));
    send(content);

}
void CIRCClient::getNamesAsync(const wxString& channelName)
{
    wxString content(wxString::Format(wxT("NAMES %s\r\n"), channelName));
    send(content);
}

void CIRCClient::sendMessage(const wxString& target, const wxString& content)
{
    wxString contentWxString(
            wxString::Format(wxT("PRIVMSG %s %s\r\n"), target, content));
    send(contentWxString);
}
void CIRCClient::sendNotice(const wxString& target, const wxString& content)
{
    wxString contentWxString(
            wxString::Format(wxT("NOTICE %s %s\r\n"), target, content));
    send(contentWxString);
}
void CIRCClient::changeTopic(const wxString& channelName,
        const wxString& content)
{
    wxString contentWxString(
            wxString::Format(wxT("TOPIC %s %s\r\n"), channelName, content));
    send(contentWxString);
}
void CIRCClient::changeNickname(const wxString& content)
{
    wxString contentWxString(wxString::Format(wxT("NICK %s\r\n"), content));
    send(contentWxString);

}
}
} /* namespace CornStarch */
