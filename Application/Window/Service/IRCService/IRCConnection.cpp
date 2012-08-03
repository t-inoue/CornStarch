/*
 * IRCConnection.cpp
 *
 *  Created on: 2012/07/13
 */

#include "IRCConnection.hpp"

namespace CornStarch
{
;

// イベントの宣言
wxDECLARE_EVENT(myEVT_THREAD_PUT_JOIN, CJoinEvent);
wxDECLARE_EVENT(myEVT_THREAD_GET_CHANNEL, CGetChannelEvent);
wxDECLARE_EVENT(myEVT_THREAD_POST_MESSAGE, wxThreadEvent);
wxDECLARE_EVENT(myEVT_THREAD_GET_MESSAGE, CGetMessageEvent);
wxDECLARE_EVENT(myEVT_THREAD_GET_MEMBER_INFO, CGetMemberInfoEvent);
wxDECLARE_EVENT(myEVT_THREAD_DELETE_PART, CPartEvent);
wxDECLARE_EVENT(myEVT_THREAD_STREAM_CH_UPDATE, CChannelStreamEvent);
wxDECLARE_EVENT(myEVT_THREAD_STREAM_USER_UPDATE, CUserStreamEvent);

namespace IRC
{
;

CIRCConnection::CIRCConnection()
{

}

CIRCConnection::~CIRCConnection()
{
    m_client->disconnect();
    delete m_client;
    int size = (int) m_channels.size();
    for (int i = 0; i < size; i++){
        delete m_channels[i];
    }
}

// 初期化を行う
void CIRCConnection::init(int connectionId, wxEvtHandler* handler)
{
    m_connectionId = connectionId;
    m_handler = handler;
    m_client = new CIRCClient();
    m_client->init(connectionId, handler);
}

// メッセージを投稿するタスク(別スレッド)を開始する
void CIRCConnection::startPostMessageTask(const IUser* user,
        const wxString& message, const wxString& channel)
{
    m_client->sendMessageAsync(channel, message);

    // イベントを通知
    wxThreadEvent* event = new wxThreadEvent();
    event->SetEventType(myEVT_THREAD_POST_MESSAGE);
    wxQueueEvent(m_handler, event);

}

// チャンネルのメッセージを取得するタスク(別スレッド)を開始する
void CIRCConnection::startGetMessageTask(const IUser* user,
        const wxString& channel)
{
    if (channel != ""){
        // イベントを通知
        vector<CMessageData*> result;
        CGetMessageEvent* event = new CGetMessageEvent();
        event->setMessages(result); // 値取得
        event->SetEventType(myEVT_THREAD_GET_MESSAGE); // イベントの種類をセット
        event->setConnectionId(m_connectionId);
        wxQueueEvent(m_handler, event);
    }
}

// チャンネルのメンバーを取得するタスク(別スレッド)を開始する
void CIRCConnection::startGetMemberTask(const IUser* user,
        const wxString& channel)
{
    if (channel != ""){
        m_client->getNamesAsync(channel);
    }
}

// ユーザの所属するチャンネル一覧を取得するタスク(別スレッド)を開始する
void CIRCConnection::startGetChannelTask(const IUser* user)
{
    // イベントを通知
    CGetChannelEvent* event = new CGetChannelEvent();

    vector<CChannelData*> channels;
    int size = m_channels.size();
    for (int i = 0; i < size; i++){
        CChannelData* channel = new CChannelData();
        channel->m_name = m_channels[i]->m_name;
        channel->m_topic = m_channels[i]->m_topic;
        channels.push_back(channel);
    }
    event->setChannels(channels); // 値取得
    event->SetEventType(myEVT_THREAD_GET_CHANNEL); // イベントの種類をセット
    event->setConnectionId(m_connectionId);
    wxQueueEvent(m_handler, event);
}
wxString CIRCConnection::getValidateChannelName(const wxString& channel)
{
    //先頭が#か&でなければ追加。
    wxString validateChannelName =channel;
    if (channel.Find("#") != 0 && channel.Find("&") != 0){
        validateChannelName = wxString("#") + channel;
    }
    // スペースを削除
    validateChannelName.Replace(" ","");
    // カンマを削除
    validateChannelName.Replace(",","");
    return validateChannelName;
}
// チャンネルから離脱するタスク(別スレッド)を開始する
void CIRCConnection::startPartTask(const IUser* user, const wxString& channel)
{
    wxString validateChannelName =getValidateChannelName(channel);
    m_client->partAsync(validateChannelName);

    vector<CChannelData*>::iterator it = m_channels.begin();
    while (it != m_channels.end()){
        wxString channelName = (*it)->m_name;
        if (channelName == validateChannelName){
            m_channels.erase(it);
            delete *it;
            break;
        }
        ++it;
    }
    // イベントを通知
    CPartEvent* event = new CPartEvent();
    event->SetEventType(myEVT_THREAD_DELETE_PART); // イベントの種類をセット
    event->SetString(channel);
    event->setConnectionId(m_connectionId);
    wxQueueEvent(m_handler, event);
}

// チャンネルに参加するタスク(別スレッド)を開始する
void CIRCConnection::startJoinTask(const IUser* user, const wxString& channel)
{
    wxString validateChannelName =getValidateChannelName(channel);
    m_client->joinAsync(validateChannelName);
    m_client->getTopicAsync(validateChannelName);

    // イベントを通知
    CChannelData *channelData = new CChannelData();
    channelData->m_name = validateChannelName;
    channelData->m_topic = "";
    m_channels.push_back(channelData);

    CJoinEvent* event = new CJoinEvent();
    event->SetEventType(myEVT_THREAD_PUT_JOIN); // イベントの種類をセット
    event->SetString(channel); // 新チャンネル名
    event->setConnectionId(m_connectionId);
    wxQueueEvent(m_handler, event);
}

// メンバーの情報を取得するタスク(別スレッド)を開始する
void CIRCConnection::startGetMemberInfoTask(const IUser* user,
        const wxString& userName)
{
    // イベントを通知
    CGetMemberInfoEvent* event = new CGetMemberInfoEvent();
    CMemberData member(userName, userName);
    event->setMember(member); // 値取得
    event->SetEventType(myEVT_THREAD_GET_MEMBER_INFO); // イベントの種類をセット
    event->setConnectionId(m_connectionId);
    wxQueueEvent(m_handler, event);

}

// ユーザが正規の人かどうか判断するタスク(別スレッド)を開始する
void CIRCConnection::startAuthTask(const IUser* user)
{
    m_client->setPort("6667");
    m_client->setHost(m_host);
    m_client->startAsync(user->getUserName(), "");
}

// ストリーム通信タスク(別スレッド)を開始
void CIRCConnection::startStreamTask(const IUser* user)
{
}

// 認証用タスク(別スレッド)を削除する
void CIRCConnection::deleteAuthTask(void)
{
}

// ホストを取得
wxString CIRCConnection::getHost() const
{
    return m_host;
}
// ホストを設定
void CIRCConnection::setHost(const wxString& host)
{
    m_host = host;
}

//override ニックネームを変更するタスク(別スレッド)を開始する
void CIRCConnection::startNickChangeTask(const IUser* user,
        const wxString& nick)
{
    m_client->changeNicknameAsync(nick);
}

//override トピックを変更するタスク(別スレッド)を開始する
void CIRCConnection::startChangeTopicTask(const IUser* user,
        const wxString& topic)
{
    m_client->changeTopicAsync(user->getChannelString(), topic);
}

}
} /* namespace CornStarch */
