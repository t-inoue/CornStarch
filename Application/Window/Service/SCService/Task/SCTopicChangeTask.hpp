#pragma once
#include "SCTask.hpp"

namespace CornStarch
{
;
namespace StarChat
{
;

// トピックを変更するためのタスク
class CSCTopicChangeTask: public CSCTask
{
private:
    wxString m_channel;
    wxString m_topic;

public:
    CSCTopicChangeTask(void);
    ~CSCTopicChangeTask(void);

    wxString getChannel() const
    {
        return m_channel;
    }

    void setChannel(wxString channel)
    {
        m_channel = channel;
    }

    wxString getTopic() const
    {
        return m_topic;
    }

    void setTopic(wxString topic)
    {
        m_topic = topic;
    }

private:
    void sendRequestToSC(CSCClient* client);
};

}
}
