#include "MainLogHolder.hpp"
#include "MessageLog.hpp"
#include "MemberLog.hpp"
#include "JoinLog.hpp"
#include "PartLog.hpp"
#include "TopicLog.hpp"
#include "InviteLog.hpp"
#include "KickLog.hpp"

using namespace std;

namespace CornStarch
{;

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
void CMainLogHolder::pushMessageLog(const CMessageData& message,const wxString& serviceName, const wxString& nick)
{
    CMessageLog* log = new CMessageLog();
    log->init(message, nick);

    // ログの追加
    pushLog(log,serviceName);
}

// チャンネル参加ログを追加する
void CMainLogHolder::pushJoinLog(const CSubscribeData& sub,const wxString& serviceName, const wxString& nick)
{
    CJoinLog* log = new CJoinLog();
    log->init(sub, nick);

    // ログの追加
    pushLog(log,serviceName);
}

// チャンネル退出ログを追加する
void CMainLogHolder::pushPartLog(const CSubscribeData& sub,const wxString& serviceName, const wxString& nick)
{
    CPartLog* log = new CPartLog();
    log->init(sub, nick);

    // ログの追加
    pushLog(log,serviceName);
}

// ニックネーム変更ログを追加する
void CMainLogHolder::pushChangeNickLog(const CMemberData& member,const wxString& serviceName)
{
    CMemberLog* log = new CMemberLog();
    log->init(member);

    // ログの追加
    pushLog(log,serviceName);
}
// トピック変更ログを追加する
void CMainLogHolder::pushKickLog(const wxString& channel,const wxString& serviceName,const wxString& userName)
{
    CKickLog* log = new CKickLog();
    log->init(userName, channel);
    // ログの追加
    pushLog(log,serviceName);
}
// トピック変更ログを追加する
void CMainLogHolder::pushInviteLog(const wxString& channel,const wxString& serviceName,const wxString& userName)
{
    CInviteLog* log = new CInviteLog();
    log->init(userName, channel);
    // ログの追加
    pushLog(log,serviceName);
}

// トピック変更ログを追加する
void CMainLogHolder::pushTopicLog(const CChannelData& channel,const wxString& serviceName)
{
    CTopicLog* log = new CTopicLog();
    log->init(channel);

    // ログの追加
    pushLog(log,serviceName);
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
void CMainLogHolder::pushLog(CChatLog* log,const wxString& serviceName)
{
    log->setServiceName(serviceName);
    // ログの追加
    m_logs.push_back(log);

    // 多すぎたら先頭削除
    if (m_logs.size() > MAX_LENGTH){
        vector<CChatLog*>::iterator it = m_logs.begin();
        delete *it;
        m_logs.erase(it);

    }
}

}
