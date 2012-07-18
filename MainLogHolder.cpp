#include "MainLogHolder.hpp"

using namespace std;

CMainLogHolder::CMainLogHolder(void)
{
}


CMainLogHolder::~CMainLogHolder(void)
{
    size_t size = m_logs.size();
    for (size_t i = 0; i < size; i++){
        delete m_logs[i];
    }
}


//////////////////////////////////////////////////////////////////////


// ログ一覧を取得する
vector<CChatLog*> CMainLogHolder::getLogs(void) const
{
    return m_logs;
}

// メッセージログを追加する
void CMainLogHolder::pushMessageLog(const CMessageData& message, const wxString& nick)
{
    CMessageLog* log = new CMessageLog();
    log->init(message, nick);

    // ログの追加
    pushLog(log);
}

// チャンネル参加ログを追加する
void CMainLogHolder::pushJoinLog(const CSubscribeData& sub, const wxString& nick)
{
    CJoinLog* log = new CJoinLog();
    log->init(sub, nick);

    // ログの追加
    pushLog(log);
}

// チャンネル退出ログを追加する
void CMainLogHolder::pushPartLog(const CSubscribeData& sub, const wxString& nick)
{
    CPartLog* log = new CPartLog();
    log->init(sub, nick);

    // ログの追加
    pushLog(log);
}

// ニックネーム変更ログを追加する
void CMainLogHolder::pushChangeNickLog(const CMemberData& member)
{
    CMemberLog* log = new CMemberLog();
    log->init(member);

    // ログの追加
    pushLog(log);
}

// トピック変更ログを追加する
void CMainLogHolder::pushTopicLog(const CChannelData& channel)
{
    CTopicLog* log = new CTopicLog();
    log->init(channel);

    // ログの追加
    pushLog(log);
}

// ニックネームの更新を行う
void CMainLogHolder::onUpdateNickName(const CMemberData& member)
{
    vector<CChatLog*>::iterator it = m_logs.begin();
    for (; it != m_logs.end(); it++){

        // ニックネームが未知の時、更新を行う
        if ((*it)->isUnknownNick(member.m_name)){
            (*it)->updateNick(member.m_nick);
        }
    }
}


//////////////////////////////////////////////////////////////////////


// ログを追加する
void CMainLogHolder::pushLog(CChatLog* log)
{
    // ログの追加
    m_logs.push_back(log);

    // 多すぎたら先頭削除
    if (m_logs.size() > MAX_LENGTH){
        vector<CChatLog*>::iterator it = m_logs.begin();
        m_logs.erase(it);
    }
}