/*
 * SCConnectionContents.cpp
 *
 *  Created on: 2012/07/19
 *      Author: yasuo_tanaka
 */

#include "SCConnectionContents.h"
#include "SCConnection.hpp"
#include "SCUser.hpp"

CSCConnectionContents::CSCConnectionContents() {
	// TODO Auto-generated constructor stub

}

CSCConnectionContents::~CSCConnectionContents() {
	// TODO Auto-generated destructor stub
}

void CSCConnectionContents::init(wxEvtHandler* handler)
{
	CConnectionContents::init(handler);

    // �ʐM�̏���
    m_connect = new CSCConnection();
    m_connect->init(m_handler);
    // ���[�U���̏���
    m_user = new CSCUser();
    m_user->init();
    m_user->setChannel("");

    // �p�X���[�h��񂪕ۑ�����Ă����
    wxString basicKey = m_user->getBasicKey();
    wxString nameKey = m_user->getNameKey();
    if (m_persist->isKeySaved(basicKey) && m_persist->isKeySaved(nameKey)){

        // �p�X���[�h����ǂݍ���
        m_user->setUserName(m_persist->loadValue(nameKey));
        m_user->setBasic(m_persist->loadValue(basicKey));

        // �F�؃^�X�N���J�n����
        m_connect->startAuthTask(m_handler, m_user->getUserName(), m_user->getBasic());
    }
}
