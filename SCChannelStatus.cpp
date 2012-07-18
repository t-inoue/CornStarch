#include "SCChannelStatus.hpp"

using namespace std;

CSCChannelStatus::CSCChannelStatus(void)
{
}


CSCChannelStatus::~CSCChannelStatus(void)
{
    delete m_messages;
    delete m_members;
}


//////////////////////////////////////////////////////////////////////


// 初期化を行う
void CSCChannelStatus::init(void)
{
    m_messages = new CMessageVec();
    m_members = new CMemberVec();
}

// トピックをセットする
void CSCChannelStatus::setTopic(const wxString& topic)
{
    m_topic = topic;
}

// トピックを取得する
wxString CSCChannelStatus::getTopic(void) const
{
    return m_topic;
}

// メッセージ一覧を取得する
vector<CMessageData*> CSCChannelStatus::getMessages(void) const
{
    return *m_messages;
}

// メンバー一覧を取得する
vector<CMemberData*> CSCChannelStatus::getMembers(void) const
{
    return *m_members;
}

// メッセージを追加する
void CSCChannelStatus::pushMessage(const CMessageData& message)
{
    m_messages->push(message);
}

// メンバーを追加する
void CSCChannelStatus::pushMember(const CMemberData& member)
{
    m_members->push(member);
}

// メッセージ一覧をセットする
void CSCChannelStatus::setMessages(const vector<CMessageData*>& messages)
{
    m_messages->setMessages(messages);
}

// メンバー一覧をセットする
void CSCChannelStatus::setMembers(const vector<CMemberData*>& members)
{
    m_members->setMembers(members);
}

// メッセージを取得し終えたか
bool CSCChannelStatus::hasReceivedMessage(void) const
{
    return m_messages->hasSetMessage();
}

// メンバーを取得し終えたか
bool CSCChannelStatus::hasReceivedMember(void) const
{
    return m_members->hasSetMember();
}

// ID不明かつ同じ投稿内容のメッセージがあるか
bool CSCChannelStatus::hasSameMessage(const CMessageData& message) const
{
    return m_messages->hasSameMessage(message);
}

// 同じ内容のメッセージについてIDを更新
void CSCChannelStatus::updateMessageId(const CMessageData& message)
{
    if (!m_messages->hasSameMessage(message)){
        return;
    }
    m_messages->updateMessageId(message);
}

// メンバー情報を更新する
void CSCChannelStatus::updateMember(const CMemberData& member)
{
    m_members->updateStatus(member);
}

// メンバー情報を消す
void CSCChannelStatus::popMember(const wxString& userName)
{
    m_members->pop(userName);
}
