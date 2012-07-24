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

}
void CIRCClient::init(int connectionId)
{
	CSocketClient::init();
	m_connectionId = connectionId;

	m_port = "6667";
	m_host = "example";

}
void CIRCClient::start(wxEvtHandler* handler, wxString userName,
		wxString password)
{

	if (m_connected)
	{
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

	while (m_connected)
	{
		this->m_buffer = "";
		receive();
		if (this->m_buffer != "")
		{
			vector<string> messages = CStringUtility::split(this->m_buffer,
					"\n");
			for (int i = 0; i < messages.size(); i++)
			{
				cout << messages[i].c_str();
				CConnectionEventBase* event = parser.parse(messages[i]);
				if (event != NULL)
				{
					event->setConnectionId(m_connectionId);
					wxQueueEvent(m_handler, event);
				}
			}

		}
	}
}
void CIRCClient::disconnect(void)
{
	wxString content("QUIT\r\n");
	send(content);
}
void CIRCClient::join(wxString channelName)
{
	wxString content(wxString::Format(wxT("JOIN %s\r\n"), channelName));
	send(content);
}
void CIRCClient::part(wxString channelName)
{
	wxString content(wxString::Format(wxT("PART %s\r\n"), channelName));
	send(content);
}
void CIRCClient::getTopicAsync(wxString channelName)
{
	wxString content(wxString::Format(wxT("TOPIC %s\r\n"), channelName));
	send(content);

}
void CIRCClient::getNamesAsync(wxString channelName)
{
	wxString content(wxString::Format(wxT("NAMES %s\r\n"), channelName));
	send(content);

}

void CIRCClient::sendMessage(wxString target, wxString content)
{
	wxString contentWxString(
			wxString::Format(wxT("PRIVMSG %s %s\r\n"), target, content));
	send(contentWxString);
}
void CIRCClient::sendNotice(wxString target, wxString content)
{

	wxString contentWxString(
			wxString::Format(wxT("NOTICE %s %s\r\n"), target, content));
	send(contentWxString);
}
}
} /* namespace CornStarch */
