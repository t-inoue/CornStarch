/*
 * IRCConnectionContents.cpp
 *
 *  Created on: 2012/07/19
 */

#include "IRCConnectionContents.h"
#include "IRCUser.hpp"
#include "IRCConnection.h"
namespace CornStarch {
namespace IRC {
CIRCConnectionContents::CIRCConnectionContents() {
	// TODO Auto-generated constructor stub

}

CIRCConnectionContents::~CIRCConnectionContents() {
	// TODO Auto-generated destructor stub
}

void CIRCConnectionContents::init(wxEvtHandler* handler) {

	CConnectionContents::init(handler);
	// �ʐM�̏���
	m_connect = new CIRCConnection();
	m_connect->init(m_handler);
	// ���[�U���̏���
	m_user = new CIRCUser();
	m_user->init();
	m_user->setChannel("");

}
}
}
