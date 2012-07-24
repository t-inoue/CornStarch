#include "IRCClient.h"
#include "Thread.h"
#include "GetMemberEvent.hpp"
#include "IRCParser.h"
#include "StringUtility.h"

using namespace std;

namespace CornStarch
{
namespace IRC
{
CIRCClient::CIRCClient() :
		m_handler(NULL), m_connected(false)
{

}

CIRCClient::~CIRCClient(void)
{
	m_connected = false;
	this->close();
}
void CIRCClient::init(int connectionId)
{
	CSocketClient::init();
	m_connectionId = connectionId;

}
void CIRCClient::start(wxEvtHandler* handler, const wxString& userName,
        const wxString& password)
{

	if (m_connected){
		return;
	}

	setPort(this->m_port);
	string host(this->m_host.c_str());
	setUrl(host);

	m_connected = connect();
	m_handler = handler;
	//　IRCへの接続
	string pass(wxString::Format(wxT( "PASS %s\r\n"), userName.c_str()));
	send(pass);
	string nick(wxString::Format(wxT("NICK %s\r\n"), userName.c_str()));
	send(nick);
	string user(
	        wxString::Format(wxT( "USER %s * 0 :%s\r\n"), userName.c_str(),
	                userName.c_str()));
	send(user);

	Thread *thread = new Thread(this, &CIRCClient::receiveLoop);
	thread->start();
}
void CIRCClient::receiveLoop()
{
	CIRCParser parser;

	while (m_connected){
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
