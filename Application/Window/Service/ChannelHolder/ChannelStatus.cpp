#include "ChannelStatus.hpp"

using namespace std;

namespace CornStarch
{;

CChannelStatus::CChannelStatus(void)
{
}


CChannelStatus::~CChannelStatus(void)
{
    delete m_messages;
    delete m_members;
}


//////////////////////////////////////////////////////////////////////


// 初期化を行う
void CChannelStatus::init(void)
{
    m_messages = new CMessageVec();
    m_members = new CMemberVec();
}

// トピックをセットする
void CChannelStatus::setTopic(const wxString& topic)
{
    m_topic = topic;
}

// トピックを取得する
wxString CChannelStatus::getTopic(void) const
{
    return m_topic;
}

// メッセージ一覧を取得する
vector<CMessageData*> CChannelStatus::getMessages(void) const
{
    return *m_messages;
}

// メンバー一覧を取得する
vector<CMemberData*> CChannelStatus::getMembers(void) const
{
    return *m_members;
}

// メッセージを追加する
void CChannelStatus::pushMessage(const CMessageData& message)
{
    m_messages->push(message);
}

// メンバーを追加する
void CChannelStatus::pushMember(const CMemberData& member)
{
    m_members->push(member);
}

// メッセージ一覧をセットする
void CChannelStatus::setMessages(const vector<CMessageData*>& messages)
{
    m_messages->setMessages(messages);
}

// メンバー一覧をセットする
void CChannelStatus::setMembers(const vector<CMemberData*>& members)
{
    m_members->setMembers(members);
}

// メッセージを取得し終えたか
bool CChannelStatus::hasReceivedMessage(void) const
{
    return m_messages->hasSetMessage();
}

// メンバーを取得し終えたか
bool CChannelStatus::hasReceivedMember(void) const
{
    return m_members->hasSetMember();
}

// ID不明かつ同じ投稿内容のメッセージがあるか
bool CChannelStatus::hasSameMessage(const CMessageData& message) const
{
    return m_messages->hasSameMessage(message);
}

// 同じ内容のメッセージについてIDを更新
void CChannelStatus::updateMessageId(const CMessageData& message)
{
    if (!m_messages->hasSameMessage(message)){
        return;
    }
    m_messages->updateMessageId(message);
}

// メンバー情報を更新する
void CChannelStatus::updateMember(const CMemberData& member)
{
    m_members->updateStatus(member);
}

// メンバー情報を消す
void CChannelStatus::popMember(const wxString& userName)
{
    m_members->pop(userName);
}

}