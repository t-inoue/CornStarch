#ifndef KICKEVENT_HPP_
#define KICKEVENT_HPP_
#include "ConnectionEventBase.hpp"
namespace CornStarch
{
class CKickEvent: public CConnectionEventBase
{
    wxString m_channel; // チャンネル名
    wxString m_user; // ユーザ名
public:
    CKickEvent();
    virtual ~CKickEvent();

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
};
}
#endif /* KICKEVENT_HPP_ */
