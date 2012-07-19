#include "IRCClient.h"
#include "Thread.h"
#include "GetMemberEvent.hpp"
#include "IRCParser.h"
#include "StringUtility.h"

using namespace std;

wxDECLARE_EVENT(myEVT_THREAD_GET_MEMBER, CGetMemberEvent);
namespace CornStarch {
namespace IRC {
CIRCClient::CIRCClient() :
		m_userInfo(NULL), m_handler(NULL) {

}

CIRCClient::~CIRCClient(void) {
	if (m_userInfo != NULL) {
		delete m_userInfo;
	}
}
void CIRCClient::init(int connectionId) {
	CSocketClient::init();
	m_connectionId = connectionId;
	//TEST
	m_userInfo = new CIRCUser();
	m_userInfo->setUserInfo("TEST", "");
	m_userInfo->setNickName("TEST");

	m_port = "6667";
	m_host = "sample.co.jp";

}
void CIRCClient::start(wxEvtHandler* handler) {

	if (m_connected) {
		return;
	}

	setPort(this->m_port);
	string host(this->m_host.c_str());
	setUrl(host);

	m_connected = connect();
	m_handler = handler;
	//
	string pass(
			wxString::Format(wxT( "PASS %s\r\n"), m_userInfo->getPassword()).c_str());
	send(pass);
	string nick(
			wxString::Format(wxT("NICK %s\r\n"), m_userInfo->getNickName()).c_str());
	send(nick);
	string user(
			wxString::Format(wxT( "USER %s * 0 :%s\r\n"),
					m_userInfo->getUserName(), m_userInfo->getUserName()).c_str());
	send(user);

	Thread *thread = new Thread(this, &CIRCClient::receiveLoop);
	thread->start();
}
void CIRCClient::receiveLoop() {
	CIRCParser parser;

	while (m_connected) {
		this->m_buffer = "";
		receive();
		if (this->m_buffer != "") {
			vector<string> messages = CStringUtility::split(this->m_buffer,
					"\n");
			for (int i = 0; i < messages.size(); i++) {
				cout << messages[i].c_str();
				CConnectionEventBase* event = parser.parse(messages[i]);
				if (event != NULL) {
					event->setConnectionId(m_connectionId);
					wxQueueEvent(m_handler, event);
				}
			}

		}
	}
}

void CIRCClient::join(wxString channelName) {
	wxString content(wxString::Format(wxT("JOIN %s\r\n"), channelName));
	send(content);
}
void CIRCClient::part(wxString channelName) {
	wxString content(wxString::Format(wxT("PART %s\r\n"), channelName));
	send(content);
}
void CIRCClient::getTopicAsync(wxString channelName) {
	wxString content(wxString::Format(wxT("TOPIC %s\r\n"), channelName));
	send(content);

}
void CIRCClient::getNamesAsync(wxString channelName) {
	wxString content(wxString::Format(wxT("NAMES %s\r\n"), channelName));
	send(content);

}

void CIRCClient::sendMessage(wxString target, wxString content) {
	wxString contentWxString(
			wxString::Format(wxT("PRIVMSG %s %s\r\n"), target, content));
	send(contentWxString);
}
void CIRCClient::sendNotice(wxString target, wxString content) {

	wxString contentWxString(
			wxString::Format(wxT("NOTICE %s %s\r\n"), target, content));
	send(contentWxString);
}
}
} /* namespace CornStarch */
