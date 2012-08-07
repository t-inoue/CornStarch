
#ifndef INVITELOG_HPP_
#define INVITELOG_HPP_

#include "ChatLog.hpp"
namespace CornStarch
{;

class CInviteLog: public CChatLog
{
    wxString m_channel; // チャンネル名
    wxString m_username; // ユーザ名
public:
    CInviteLog();
    virtual ~CInviteLog();
    // 初期化を行う
    void init(const wxString& name, const wxString& channel);

    wxString getChannel() const
    {
        return m_channel;
    }

    void setChannel(wxString channel)
    {
        m_channel = channel;
    }

    wxString getUsername() const
    {
        return m_username;
    }

    void setUsername(wxString username)
    {
        m_username = username;
    }
};
}
#endif /* INVITELOG_HPP_ */
