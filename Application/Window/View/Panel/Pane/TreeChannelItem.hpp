
#ifndef TREECHANNELITEM_HPP_
#define TREECHANNELITEM_HPP_
#include "../../../Service/ChannelStatus.hpp"
#include <wx/treebase.h>

namespace CornStarch
{

class CTreeChannelItem : public wxTreeItemData
{
    wxString m_channelName;
    int m_unreadCount;

public:
    CTreeChannelItem();
    virtual ~CTreeChannelItem();

    wxString getChannelName() const
    {
        return m_channelName;
    }

    void setChannelName(wxString channelName)
    {
        m_channelName = channelName;
    }

    int getUnreadCount() const
    {
        return m_unreadCount;
    }

    void setUnreadCount(int unreadCount)
    {
        m_unreadCount = unreadCount;
    }

    void addUnreadCount()
    {
        m_unreadCount++;
    }
};

} /* namespace CornStarch */
#endif /* TREECHANNELITEM_HPP_ */
