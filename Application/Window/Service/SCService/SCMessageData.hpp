#ifndef SCMESSAGEDATA_HPP_
#define SCMESSAGEDATA_HPP_

#include <vector>
#include "../../../DataStruct/ChannelData.hpp"
#include "../../../DataStruct/MessageData.hpp"
#include "../../../DataStruct/MemberData.hpp"

namespace CornStarch
{
namespace StarChat
{
using namespace std;
class CSCMessageType
{
public:
    enum SC_MESSAGE_TYPE
    {
        UNKNOWN, MESSAGE, MESSAGE_REPLY, NOTICE, JOIN, JOIN_REPLY, PART,
        PART_REPLY, TOPIC, NICK, GET_MEMBER, GET_MEMBERS, GET_CHANNEL,
        GET_MESSAGES
    };
};

class CSCMessageData: public CMessageData
{
public:

    CSCMessageType::SC_MESSAGE_TYPE m_type;
    vector<CMessageData*> m_messages;
    CMemberData m_member;
    vector<CMemberData*> m_members;
    vector<CChannelData*> m_channels;
    CChannelData m_channelData;
    CSCMessageData();
    virtual ~CSCMessageData();
};
}
}
#endif /* SCMESSAGEDATA_HPP_ */
