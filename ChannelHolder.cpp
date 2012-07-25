#include "ChannelHolder.hpp"

using namespace std;

CChannelHolder::CChannelHolder(void):m_isLoaded(false)
{
}


CChannelHolder::~CChannelHolder(void)
{
    deleteChannels();
}


//////////////////////////////////////////////////////////////////////


// 初期化を行う
void CChannelHolder::init(void)
{
}

// チャンネル一覧をセットする
void CChannelHolder::setChannels(const vector<CChannelData*>& channels)
{
	m_isLoaded = true;
    // チャンネル一覧を空にする
    deleteChannels();

    size_t size = channels.size();
    for (size_t i = 0; i < size; i++){

        wxString channel = channels[i]->m_name;
        wxString topic = channels[i]->m_topic;

        // 既にチャンネル情報を受信しているときはトピックの変更のみ
        if (m_channels.find(channel) != m_channels.end()){
            m_channels[channel]->setTopic(topic);
        } else {

            // メモリ領域を確保して挿入
            CChannelStatus* data = new CChannelStatus();
            data->init();
            data->setTopic(topic);
            m_channels[channel] = data;
        }
    }
}

// チャンネル一覧を取得する
vector<wxString> CChannelHolder::getChannels(void) const
{
    map<wxString, CChannelStatus*>::const_iterator it;
    vector<wxString> result;

    // チャンネル一覧を作成
    for (it = m_channels.begin(); it != m_channels.end(); it++){
        result.push_back(it->first);
    }

    return result;
}

// 既にチャンネル一覧を取得したか
bool CChannelHolder::hasReceivedChannel(void) const
{
    return m_isLoaded;
}

// チャンネルを追加する
void CChannelHolder::setChannel(const CChannelData& channel)
{
    wxString name = channel.m_name;
    wxString topic = channel.m_topic;

    // チャンネルが存在するとき、トピックの更新のみ行う
    if (m_channels.find(name) != m_channels.end()){
        m_channels[name]->setTopic(topic);
        return;
    }

    // チャンネルが存在しない時は追加を行う
    CChannelStatus* data = new CChannelStatus();
    data->init();
    data->setTopic(topic);
    m_channels[name] = data;
}

// チャンネルを削除する
void CChannelHolder::popChannel(const wxString& channel)
{
    delete m_channels[channel];
    m_channels.erase(channel);
}

// チャンネル名からtopicを取得する
wxString CChannelHolder::getTopic(const wxString& channel)
{
    if (m_channels.find(channel) == m_channels.end()){
        return "";
    }

    return m_channels[channel]->getTopic();
}

// チャンネル一覧のメモリ領域を削除する
void CChannelHolder::deleteChannels(void)
{
    map<wxString, CChannelStatus*>::iterator it;
    for (it = m_channels.begin(); it != m_channels.end(); it++){
        delete m_channels[it->first];
    }
    m_channels.clear();

}

// 一番頭のチャンネルを取得する
wxString CChannelHolder::getFirstChannel(void)
{
    if (m_channels.size() == 0){
        return "";
    }

    return m_channels.begin()->first;
}


/////////////////////////////////////////////////////////////


// チャンネルのメッセージ一覧を取得する
vector<CMessageData*> CChannelHolder::getMessages(const wxString& channel)
{
    // チャンネルが存在しない
    if (m_channels.find(channel) == m_channels.end()){
        return vector<CMessageData*>();
    }

    return m_channels[channel]->getMessages();
}

// チャンネルのメンバー一覧を取得する
vector<CMemberData*> CChannelHolder::getMembers(const wxString& channel)
{
    // チャンネルが存在しない
    if (m_channels.find(channel) == m_channels.end()){
        return vector<CMemberData*>();
    }

    return m_channels[channel]->getMembers();
}

// チャンネルのメッセージを追加する
void CChannelHolder::pushMessage(const wxString& channel, const CMessageData& message)
{
    // チャンネルが存在しない
    if (m_channels.find(channel) == m_channels.end()){
        return;
    }

    m_channels[channel]->pushMessage(message);
}

// チャンネルのメンバーを追加する
void CChannelHolder::pushMember(const wxString& channel, const CMemberData& member)
{
    // チャンネルが存在しない
    if (m_channels.find(channel) == m_channels.end()){
        return;
    }

    m_channels[channel]->pushMember(member);
}

// チャンネルのメッセージ一覧をセットする
void CChannelHolder::setMessages(const wxString& channel, const vector<CMessageData*>& messages)
{
    // チャンネルが存在しない
    if (m_channels.find(channel) == m_channels.end()){
        return;
    }

    m_channels[channel]->setMessages(messages);
}

// チャンネルのメンバー一覧をセットする
void CChannelHolder::setMembers(const wxString& channel, const vector<CMemberData*>& members)
{
    // チャンネルが存在しない
    if (m_channels.find(channel) == m_channels.end()){
        return;
    }

    m_channels[channel]->setMembers(members);
}

// メンバーを消す
void CChannelHolder::popMember(const wxString& userName)
{
    map<wxString, CChannelStatus*>::iterator it;
    for (it = m_channels.begin(); it != m_channels.end(); it++){
        it->second->popMember(userName);
    }
}

// メンバー情報を更新する
void CChannelHolder::updateMember(const CMemberData& member)
{
    map<wxString, CChannelStatus*>::iterator it;
    for (it = m_channels.begin(); it != m_channels.end(); it++){
        it->second->updateMember(member);
    }
}

// メッセージIDを更新する
void CChannelHolder::onUpdateMessageId(const CMessageData& message)
{
    map<wxString, CChannelStatus*>::iterator it;
    for (it = m_channels.begin(); it != m_channels.end(); it++){
        it->second->updateMessageId(message);
    }
}

// チャンネルのメッセージ情報を収集したか
bool CChannelHolder::hasReceivedMessage(const wxString& channel)
{
    // チャンネルが存在しない
    if (m_channels.find(channel) == m_channels.end()){
        return false;
    }

    return m_channels[channel]->hasReceivedMessage();
}

// チャンネルのメッセージ情報を収集したか
bool CChannelHolder::hasReceivedMember(const wxString& channel)
{
    // チャンネルが存在しない
    if (m_channels.find(channel) == m_channels.end()){
        return false;
    }

    return m_channels[channel]->hasReceivedMember();
}

// 同じメッセージ内容のものがあるか
bool CChannelHolder::hasSameMessage(const CMessageData& message)
{
    // チャンネルが存在しない
    if (m_channels.find(message.m_channel) == m_channels.end()){
        return false;
    }

    return m_channels[message.m_channel]->hasSameMessage(message);
}
