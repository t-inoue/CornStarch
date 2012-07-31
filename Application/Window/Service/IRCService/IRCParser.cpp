#include "IRCParser.hpp"
#include "IRCMessageData.hpp"

namespace CornStarch
{
;

wxDECLARE_EVENT(myEVT_THREAD_GET_MEMBER, CGetMemberEvent);
wxDECLARE_EVENT(myEVT_THREAD_GET_MESSAGE, CGetMessageEvent);
wxDECLARE_EVENT(myEVT_THREAD_GET_PING, CAuthEvent);
wxDECLARE_EVENT(myEVT_THREAD_STREAM_MSG_ADD, CMsgStreamEvent);
wxDECLARE_EVENT(myEVT_THREAD_STREAM_CH_JOIN, CJoinStreamEvent);
wxDECLARE_EVENT(myEVT_THREAD_STREAM_CH_PART, CPartStreamEvent);
wxDECLARE_EVENT(myEVT_THREAD_STREAM_CH_UPDATE, CChannelStreamEvent);
wxDECLARE_EVENT(myEVT_THREAD_STREAM_USER_UPDATE, CUserStreamEvent);

namespace IRC
{
;

CIRCParser::CIRCParser() :
        m_messageId(0)
{
}
CIRCParser::~CIRCParser()
{
}
CConnectionEventBase* CIRCParser::createEvent(const CIRCMessageData& message)
{

    if (message.m_statusCode == string("PRIV") + "MSG"){
        return createPrivateMessageEvent(message);
    }
    if (message.m_statusCode == string("PA") + "RT"){
        return createPartMessageEvent(message);
    }
    if (message.m_statusCode == string("JO") + "IN"){
        return createJoinMessageEvent(message);
    }
    if (message.m_statusCode == "TOPIC"){
        return createTopicMessageEvent(message);
    }
    if (message.m_statusCode == "NICK"){
        return createNickMessageEvent(message);
    }
    if (message.m_statusCode == "KICK"){
        return createKickEvent(message);
    }
    if (message.m_statusCode == "INVITE"){
        return createInviteEvent(message);
    }
    if (message.m_statusCode == "353"){ //チャンネルの名前
        addNames (message);
    }
    if (message.m_statusCode == "332"){ //トピックリプライ
        return createTopicEvent(message);
    }
    if (message.m_statusCode == "366"){ //ユーザー名羅列終了リプライ
        return createNamesEvent(message);
    }
    if (message.m_statusCode == "433" || // 不適切なユーザーID
            message.m_statusCode == "432"){ //　不適切なチャンネル
            //エラー
        CAuthEvent* event = new CAuthEvent();
        event->setAuthResult(false);
        event->SetEventType(myEVT_THREAD_GET_PING); // イベントの種類をセット
        return event;
    }
    if (message.m_statusCode == "001"){ // 接続開始リプライ
        //接続
        CAuthEvent* event = new CAuthEvent();
        event->setAuthResult(true);
        event->SetEventType(myEVT_THREAD_GET_PING); // イベントの種類をセット
        return event;
    }
    return NULL;
}
CConnectionEventBase* CIRCParser::parse(const wxString& content)
{
    if (content[0] == ':'){

        m_messageId++;
        CIRCMessageData message;
        message.m_id = m_messageId;
        message.m_time = time(NULL);
        // ホスト
        int index = 1;
        int nextIndex = content.find(" ");
        message.m_host = content.substr(index, nextIndex - index);
        // ステータスコード
        index = nextIndex + 1;
        nextIndex = content.find(" ", index);
        message.m_statusCode = content.substr(index, nextIndex - index);
        // パラメータ
        index = nextIndex + 1;
        message.m_param = content.substr(index);
        // 名前
        vector<wxString> names = CStringUtility::split(message.m_host, "!");
        if (names.size() > 1){
            message.m_username = names[0];
        }
        // チャンネル
        size_t channelIndex = message.m_param.find(" ");
        if (channelIndex != wxString::npos){
            message.m_channel = message.m_param.substr(0, channelIndex);
        }
        // コンテント
        size_t contentIndex = message.m_param.find(":");
        if (contentIndex != wxString::npos){
            contentIndex++;
            message.m_body = message.m_param(contentIndex,
                    message.m_param.size() - contentIndex - 1);
        }
        return createEvent(message);
    }
    return NULL;
}
CConnectionEventBase* CIRCParser::createNickMessageEvent(const CIRCMessageData& message) const
{

    CMemberData member;
    member.m_name = wxString(message.m_username);
    member.m_nick = wxString(message.m_body);

    CUserStreamEvent* event = new CUserStreamEvent();
    event->SetEventType(myEVT_THREAD_STREAM_USER_UPDATE);
    event->setMember(member);
    return event;
}
CConnectionEventBase* CIRCParser::createTopicMessageEvent(const CIRCMessageData& message) const
{

    CChannelData channel;
    channel.m_name = wxString(message.m_channel);
    channel.m_topic = wxString(message.m_body);

    CChannelStreamEvent* event = new CChannelStreamEvent();
    event->SetEventType(myEVT_THREAD_STREAM_CH_UPDATE);
    event->setChannel(channel);
    return event;
}
CConnectionEventBase* CIRCParser::createJoinMessageEvent(const CIRCMessageData& message) const
{
    // Eventの作成
    CJoinStreamEvent* event = new CJoinStreamEvent();
    event->SetEventType(myEVT_THREAD_STREAM_CH_JOIN);
    event->setChannelName(message.m_body);
    event->setUserName(message.m_username);
    return event;
}
CConnectionEventBase* CIRCParser::createPartMessageEvent(const CIRCMessageData& message) const
{
    // Eventの作成
    CPartStreamEvent* event = new CPartStreamEvent();
    event->SetEventType(myEVT_THREAD_STREAM_CH_PART);
    event->setChannelName(message.m_channel);
    event->setUserName(message.m_username);
    return event;

}
CConnectionEventBase* CIRCParser::createPrivateMessageEvent(const CIRCMessageData& message) const
{

    // Eventの作成
    CMsgStreamEvent* event = new CMsgStreamEvent();
    event->SetEventType(myEVT_THREAD_STREAM_MSG_ADD);
    event->setMessage(message);
    return event;
}

void CIRCParser::addNames(const CIRCMessageData& message)
{
    int index = message.m_param.find(":");
    wxString names = message.m_param.substr(index + 1);
    m_buffer += names;
}
CConnectionEventBase* CIRCParser::createNamesEvent(const CIRCMessageData& message)
{
    vector<CMemberData*> result;
    vector<wxString> names = CStringUtility::split(m_buffer, " ");

    // 各メンバについてループ
    int size = (int) names.size();
    for (int i = 0; i < size; i++){
        if (names[i].size() != 0 && names[i] != "\r"){
            // パラメータの取得
            CMemberData* mem = new CMemberData();
            mem->m_name = names[i]; // 名前(name)
            mem->m_nick = names[i]; // ニックネーム(name)
            // vectorに追加
            result.push_back(mem);
        }
    }

    CGetMemberEvent* event = new CGetMemberEvent();
    event->setMembers(result); // 値取得
    event->SetEventType(myEVT_THREAD_GET_MEMBER); // イベントの種類をセット
    m_buffer = "";
    return event;
}

CConnectionEventBase* CIRCParser::createTopicEvent(const CIRCMessageData& message) const
{
    return NULL;
}

CConnectionEventBase* CIRCParser::createKickEvent(const CIRCMessageData& message) const
{
    return NULL;
}

CConnectionEventBase* CIRCParser::createInviteEvent(const CIRCMessageData& message) const
{
    return NULL;
}
}
}
