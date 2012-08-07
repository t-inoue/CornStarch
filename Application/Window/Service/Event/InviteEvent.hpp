#ifndef INVITEEVENT_HPP_
#define INVITEEVENT_HPP_
#include "ConnectionEventBase.hpp"

namespace CornStarch
{

class CInviteEvent: public CConnectionEventBase
{
    wxString m_channel; // チャンネル名
    wxString m_user; // ユーザ名
public:
    CInviteEvent();
    virtual ~CInviteEvent();
    wxString getChannel() const
    {
        return m_channel;
    }

    void setChannel(wxString channel)
    {
        m_channel = channel;
    }

    wxString getUser() const
    {
        return m_user;
    }

    void setUser(wxString user)
    {
        m_user = user;
    }
}

;

} /* namespace CornStarch */
#endif /* INVITEEVENT_HPP_ */
