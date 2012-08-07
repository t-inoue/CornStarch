#include "ChannelSelectEvent.hpp"

namespace CornStarch
{;

CChannelSelectEvent::CChannelSelectEvent(void)
{
}


CChannelSelectEvent::~CChannelSelectEvent(void)
{
}


//////////////////////////////////////////////////////////////////////


// 項目名をセット
void CChannelSelectEvent::setChannelName(const wxString& channel)
{
    m_channelName = channel;
}

// サーバ名をセット
void CChannelSelectEvent::setServer(const wxString& server)
{
    m_server = server;
}

// サーバIDをセット
void CChannelSelectEvent::setServerId(int server)
{
    m_serverId = server;
}

// サーバ名か否かをセット
void CChannelSelectEvent::setServerOrNot(bool isServer)
{
    m_isServer = isServer;
}

// 項目名を取得
wxString CChannelSelectEvent::getChannelName(void) const
{
    return m_channelName;
}

// サーバ名を取得
wxString CChannelSelectEvent::getServer(void) const
{
    return m_server;
}

// サーバIDを取得
int CChannelSelectEvent::getServerId(void) const
{
    return m_serverId;
}

// サーバを選択したか否かを取得
bool CChannelSelectEvent::isServerSelected(void) const
{
    return m_isServer;
}

}
