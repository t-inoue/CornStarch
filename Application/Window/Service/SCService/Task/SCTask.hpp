#pragma once
#include <wx/wxprec.h>
#include <wx/wx.h>
#include "../SCClient.hpp"
#include "../SCJsonParser.hpp"
#include "../SCMessageData.hpp"
#include "../../Event/ConnectionEventBase.hpp"
#include "../../Event/DisconnectEvent.hpp"
#include "../../Event/PartEvent.hpp"
#include "../../Event/AuthEvent.hpp"
#include "../../Event/JoinEvent.hpp"
#include "../../Event/MsgStreamEvent.hpp"
#include "../../Event/ChannelStreamEvent.hpp"
#include "../../Event/JoinStreamEvent.hpp"
#include "../../Event/PartStreamEvent.hpp"
#include "../../Event/UserStreamEvent.hpp"
#include "../../Event/GetMessageEvent.hpp"
#include "../../Event/GetMemberEvent.hpp"
#include "../../Event/GetMemberInfoEvent.hpp"
#include "../../Event/GetChannelEvent.hpp"
#include "../../Event/InviteEvent.hpp"
#include "../../Event/KickEvent.hpp"
#include "../../IMessageConnectionObserver.hpp"

namespace CornStarch
{
;
namespace StarChat
{
;

// スターチャットと通信を行うためのクラス
class CSCTask: public wxThread
{
protected:
    IMessageConnectionObserver* m_observer;

    wxString m_basic;
    wxString m_host;
    int m_port;

public:
    CSCTask(wxThreadKind king = wxTHREAD_DETACHED);
    virtual ~CSCTask(void);

    wxString getHost() const
    {
        return m_host;
    }

    void setHost(wxString host)
    {
        m_host = host;
    }

    void init(IMessageConnectionObserver* observer, const wxString& basic);

    int getPort() const
    {
        return m_port;
    }

    void setPort(int port)
    {
        m_port = port;
    }

protected:
    virtual ExitCode Entry(void);

    virtual void sendRequestToSC(CSCClient* client)
    {
    }

    ;

    virtual void notifyMessage(const std::string& responseBody)
    {
    }

    ;
};

}
}
