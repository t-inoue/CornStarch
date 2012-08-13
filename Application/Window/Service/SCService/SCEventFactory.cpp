#include "SCEventFactory.hpp"
#include "../Event/ConnectionEventBase.hpp"
#include "../Event/DisconnectEvent.hpp"
#include "../Event/PartEvent.hpp"
#include "../Event/AuthEvent.hpp"
#include "../Event/JoinEvent.hpp"
#include "../Event/MsgStreamEvent.hpp"
#include "../Event/ChannelStreamEvent.hpp"
#include "../Event/JoinStreamEvent.hpp"
#include "../Event/PartStreamEvent.hpp"
#include "../Event/UserStreamEvent.hpp"
#include "../Event/GetMessageEvent.hpp"
#include "../Event/GetMemberEvent.hpp"
#include "../Event/GetMemberInfoEvent.hpp"
#include "../Event/GetChannelEvent.hpp"
#include "../IMessageConnectionObserver.hpp"

namespace CornStarch
{

wxDECLARE_EVENT(myEVT_THREAD_GET_MEMBER_INFO, CGetMemberInfoEvent);
wxDECLARE_EVENT(myEVT_THREAD_GET_CHANNEL, CGetChannelEvent);
wxDECLARE_EVENT(myEVT_THREAD_GET_MEMBER, CGetMemberEvent);
wxDECLARE_EVENT(myEVT_THREAD_GET_MESSAGE, CGetMessageEvent);
wxDECLARE_EVENT(myEVT_THREAD_GET_PING, CAuthEvent);
wxDECLARE_EVENT(myEVT_THREAD_STREAM_MSG_ADD, CMsgStreamEvent);
wxDECLARE_EVENT(myEVT_THREAD_STREAM_CH_JOIN, CJoinStreamEvent);
wxDECLARE_EVENT(myEVT_THREAD_STREAM_CH_PART, CPartStreamEvent);
wxDECLARE_EVENT(myEVT_THREAD_STREAM_CH_UPDATE, CChannelStreamEvent);
wxDECLARE_EVENT(myEVT_THREAD_STREAM_USER_UPDATE, CUserStreamEvent);
wxDECLARE_EVENT(myEVT_THREAD_DISCONNECT, CDisconnectEvent);
wxDECLARE_EVENT(myEVT_THREAD_GET_PING, CAuthEvent);
wxDECLARE_EVENT(myEVT_THREAD_DELETE_PART, CPartEvent);
wxDECLARE_EVENT(myEVT_THREAD_PUT_JOIN, CJoinEvent);
namespace StarChat
{
CSCEventFactory::CSCEventFactory()
{

}

CSCEventFactory::~CSCEventFactory()
{
}
CConnectionEventBase* CSCEventFactory::Create(CSCMessageData message)
{
    if (message.m_type == CSCMessageType::GET_CHANNEL){
        CGetChannelEvent* event = new CGetChannelEvent();
        event->setChannels(message.m_channels); // 値取得
        event->SetEventType(myEVT_THREAD_GET_CHANNEL); // イベントの種類をセット
        return event;
    }
    if (message.m_type == CSCMessageType::GET_MEMBER){
        CGetMemberInfoEvent* event = new CGetMemberInfoEvent();
        event->setMember(message.m_member); // 値取得
        event->SetEventType(myEVT_THREAD_GET_MEMBER_INFO); // イベントの種類をセット
        return event;
    }
    if (message.m_type == CSCMessageType::GET_MEMBERS){
        CGetMemberEvent* event = new CGetMemberEvent();
        event->setMembers(message.m_members); // 値取得
        event->setChannel(message.m_channel);
        event->SetEventType(myEVT_THREAD_GET_MEMBER); // イベントの種類をセット
        return event;
    }
    if (message.m_type == CSCMessageType::GET_MESSAGES){
        CGetMessageEvent* event = new CGetMessageEvent();
        event->setMessages(message.m_messages); // 値取得
        event->setChannel(message.m_channel); // チャンネル
        event->SetEventType(myEVT_THREAD_GET_MESSAGE); // イベントの種類をセット
        return event;
    }
    if (message.m_type == CSCMessageType::MESSAGE){
        CMsgStreamEvent* event = new CMsgStreamEvent();
        event->SetEventType(myEVT_THREAD_STREAM_MSG_ADD);
        event->setMessage(message);
        return event;
    }
    if (message.m_type == CSCMessageType::JOIN){
        CJoinStreamEvent* event = new CJoinStreamEvent();
        event->SetEventType(myEVT_THREAD_STREAM_CH_JOIN);
        event->setChannelName(message.m_channel);
        event->setUserName(message.m_username);
        return event;
    }
    if (message.m_type == CSCMessageType::PART){
        CPartStreamEvent* event = new CPartStreamEvent();
        event->SetEventType(myEVT_THREAD_STREAM_CH_PART);
        event->setChannelName(message.m_channel);
        event->setUserName(message.m_username);
        return event;
    }
    if (message.m_type == CSCMessageType::TOPIC){
        CChannelStreamEvent* event = new CChannelStreamEvent();
        event->SetEventType(myEVT_THREAD_STREAM_CH_UPDATE);
        event->setChannel(message.m_channelData);
        return event;
    }
    if (message.m_type == CSCMessageType::NICK){
        CUserStreamEvent* event = new CUserStreamEvent();
        event->SetEventType(myEVT_THREAD_STREAM_USER_UPDATE);
        event->setMember(message.m_member);
        return event;
    }
    if (message.m_type == CSCMessageType::JOIN_REPLY){
        CJoinEvent* event = new CJoinEvent();
        event->SetEventType(myEVT_THREAD_PUT_JOIN); // イベントの種類をセット
        event->SetString(message.m_channel); // 新チャンネル名
        return event;
    }
    if (message.m_type == CSCMessageType::PART_REPLY){
        CConnectionEventBase* event = new CPartEvent();
        event->SetEventType(myEVT_THREAD_DELETE_PART); // イベントの種類をセット
        event->SetString(message.m_channel);
        return event;
    }
    return NULL;
}
}
} // namespace CornStarch

