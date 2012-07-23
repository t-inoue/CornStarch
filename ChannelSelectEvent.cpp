#include "ChannelSelectEvent.hpp"


CChannelSelectEvent::CChannelSelectEvent(void)
{
}


CChannelSelectEvent::~CChannelSelectEvent(void)
{
}


//////////////////////////////////////////////////////////////////////


// ���ږ����Z�b�g
void CChannelSelectEvent::setText(const wxString& text)
{
    m_text = text;
}

// �T�[�o�����Z�b�g
void CChannelSelectEvent::setServer(const wxString& server)
{
    m_server = server;
}

// �T�[�oID���Z�b�g
void CChannelSelectEvent::setServerId(int server)
{
    m_serverId = server;
}

// �T�[�o�����ۂ����Z�b�g
void CChannelSelectEvent::setServerOrNot(bool isServer)
{
    m_isServer = isServer;
}

// ���ږ����擾
wxString CChannelSelectEvent::getString(void) const
{
    return m_text;
}

// �T�[�o�����擾
wxString CChannelSelectEvent::getServer(void) const
{
    return m_server;
}

// �T�[�oID���擾
int CChannelSelectEvent::getServerId(void) const
{
    return m_serverId;
}

// �T�[�o��I���������ۂ����擾
bool CChannelSelectEvent::isServerSelected(void) const
{
    return m_isServer;
}
