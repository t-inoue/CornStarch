
#include "IRCConnectionContents.h"
#include "IRCUser.hpp"
#include "IRCConnection.h"
namespace CornStarch {
namespace IRC {
CIRCConnectionContents::CIRCConnectionContents() {

}

CIRCConnectionContents::~CIRCConnectionContents() {
}

void CIRCConnectionContents::init(wxEvtHandler* handler) {

	CConnectionContents::init(handler);

	m_connect = new CIRCConnection();
	m_connect->init(m_handler);

	m_user = new CIRCUser();
	m_user->init();
	m_user->setChannel("");

}
}
}
