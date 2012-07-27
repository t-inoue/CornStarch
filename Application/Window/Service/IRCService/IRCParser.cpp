#include "IRCParser.hpp"

namespace CornStarch
{;

wxDECLARE_EVENT(myEVT_THREAD_GET_MEMBER, CGetMemberEvent);
wxDECLARE_EVENT(myEVT_THREAD_GET_MESSAGE, CGetMessageEvent);
wxDECLARE_EVENT(myEVT_THREAD_GET_PING, CAuthEvent);
wxDECLARE_EVENT(myEVT_THREAD_STREAM_MSG_ADD, CMsgStreamEvent);
wxDECLARE_EVENT(myEVT_THREAD_STREAM_CH_JOIN, CJoinStreamEvent);
wxDECLARE_EVENT(myEVT_THREAD_STREAM_CH_PART, CPartStreamEvent);
wxDECLARE_EVENT(myEVT_THREAD_STREAM_CH_UPDATE, CChannelStreamEvent);
wxDECLARE_EVENT(myEVT_THREAD_STREAM_USER_UPDATE, CUserStreamEvent);

namespace IRC
{;

CIRCParser::CIRCParser() :
m_messageId(0)
{
}
CIRCParser::~CIRCParser()
{
}

CConnectionEventBase* CIRCParser::parse(const std::string& content)
{
    if (content[0] == ':'){
        int index = 1;
        int nextIndex = content.find(" ");
        string host = content.substr(index, nextIndex - index);
        index = nextIndex + 1;
        nextIndex = content.find(" ", index);
        string statusCode = content.substr(index, nextIndex - index);
        index = nextIndex + 1;
        string param = content.substr(index);
        if (statusCode == string("PRIV") + "MSG"){
            m_messageId++;
            return createPrivateMessageEvent(host, param);
        }
        if (statusCode == string("PA") + "RT"){
            return createPartMessageEvent(host, param);
        }
        if (statusCode == string("JO") + "IN"){
            return createJoinMessageEvent(host, param);
        }
        if (statusCode == "TOPIC"){
            return createTopicMessageEvent(host, param);
        }
        if (statusCode == "NICK"){
            return createNickMessageEvent(host, param);
        }
        if (statusCode == "353"){ //チャンネルの名前
            addNames(param);
        }
        if (statusCode == "332"){ //トピックリプライ
            return createTopicEvent(param);
        }
        if (statusCode == "366"){ //ユーザー名羅列終了リプライ
            return createNamesEvent(param);
        }
        if (statusCode == "433"|| // 不適切なチャンネル
                statusCode == "432"){ //　不適切なユーザーID
            //エラー
            CAuthEvent* event = new CAuthEvent();
            event->setAuthResult(false);
            event->SetEventType(myEVT_THREAD_GET_PING); // イベントの種類をセット
            return event;
        }
        if (statusCode == "001"){ // 接続開始リプライ
            //接続
            CAuthEvent* event = new CAuthEvent();
            event->setAuthResult(true);
            event->SetEventType(myEVT_THREAD_GET_PING); // イベントの種類をセット
            return event;
        }
    }
    return NULL;
}
CConnectionEventBase* CIRCParser::createNickMessageEvent(const string& host,
    const string& param) const
{
    vector<string> names = CStringUtility::split(host, "!");
    string name = names[0];

    int contentIndex = param.find(":") + 1;
    string content = param.substr(contentIndex,
        param.size() - contentIndex - 1);

    CMemberData member;
    member.m_name = wxString(name);
    member.m_nick = wxString(content);

    CUserStreamEvent* event = new CUserStreamEvent();
    event->SetEventType(myEVT_THREAD_STREAM_USER_UPDATE);
    event->setMember(member);
    return event;
}
CConnectionEventBase* CIRCParser::createTopicMessageEvent(const string& host,
    const string& param) const
{
    vector<string> names = CStringUtility::split(host, "!");
    string name = names[0];
    int index = param.find(" ");

    int contentIndex = param.find(":") + 1;
    string content = param.substr(contentIndex,
        param.size() - contentIndex - 1);

    string channelName = param.substr(0, index);

    CChannelData channel;
    channel.m_name = wxString(channelName);
    channel.m_topic = wxString(content);

    CChannelStreamEvent* event = new CChannelStreamEvent();
    event->SetEventType(myEVT_THREAD_STREAM_CH_UPDATE);
    event->setChannel(channel);
    return event;
}
CConnectionEventBase* CIRCParser::createJoinMessageEvent(const string& host,
    const string& param) const
{
    vector<string> names = CStringUtility::split(host, "!");
    string name = names[0];

    int index = param.size();
    string channel = param.substr(1, index - 2);
    // Eventの作成
    CJoinStreamEvent* event = new CJoinStreamEvent();
    event->SetEventType(myEVT_THREAD_STREAM_CH_JOIN);
    event->setChannelName(channel);
    event->setUserName(name);
    return event;
}
CConnectionEventBase* CIRCParser::createPartMessageEvent(const string& host,
    const string& param) const
{
    vector<string> names = CStringUtility::split(host, "!");
    string name = names[0];

    int index = param.find(" ");
    string channel = param.substr(0, index);

    // Eventの作成
    CPartStreamEvent* event = new CPartStreamEvent();
    event->SetEventType(myEVT_THREAD_STREAM_CH_PART);
    event->setChannelName(channel);
    event->setUserName(name);
    return event;

}
CConnectionEventBase* CIRCParser::createPrivateMessageEvent(const string& host,
    const string& param) const
{
    vector<string> names = CStringUtility::split(host, "!");
    string name = names[0];

    int index = param.find(" ");
    string channel = param.substr(0, index);
    int contentIndex = param.find(":") + 1;
    string content = param.substr(contentIndex,
        param.size() - contentIndex - 1);

    // Messagedataの作成。
    CMessageData message;
    message.m_id = m_messageId;
    message.m_username = name;
    message.m_body = content;
    message.m_channel = channel;
    message.m_time = time(NULL);

    // Eventの作成
    CMsgStreamEvent* event = new CMsgStreamEvent();
    event->SetEventType(myEVT_THREAD_STREAM_MSG_ADD);
    event->setMessage(message);
    return event;
}

void CIRCParser::addNames(const string& param)
{
    int index = param.find(":");
    string names = param.substr(index + 1);
    m_buffer += names;
}
CConnectionEventBase* CIRCParser::createNamesEvent(const string& param)
{
    vector<CMemberData*> result;
    vector<string> names = CStringUtility::split(m_buffer, " ");

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

CConnectionEventBase* CIRCParser::createTopicEvent(const string& param) const
{

    return NULL;
}

}
}
