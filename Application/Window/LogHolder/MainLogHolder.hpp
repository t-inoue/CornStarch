#pragma once
#include "ChatLog.hpp"
#include <vector>

namespace CornStarch
{;

// チャットのログを保持するクラス
class CMainLogHolder
{
private:
    std::vector<CChatLog*> m_logs; // ログを保存する
    static const int MAX_LENGTH = 200; //ログの最大個数

public:
    CMainLogHolder(void);
    ~CMainLogHolder(void);

    // ログ一覧を取得する
    std::vector<CChatLog*> getLogs(void) const;

    // メッセージログを追加する
    void pushMessageLog(const CMessageData& message,const wxString& serviceName, const wxString& nick = "");

    // チャンネル参加ログを追加する
    void pushJoinLog(const CSubscribeData& sub,const wxString& serviceName, const wxString& nick = "");

    // チャンネル退出ログを追加する
    void pushPartLog(const CSubscribeData& sub,const wxString& serviceName, const wxString& nick = "");

    // ニックネーム変更ログを追加する
    void pushChangeNickLog(const CMemberData& member,const wxString& serviceName);

    // トピック変更ログを追加する
    void pushTopicLog(const CChannelData& channel,const wxString& serviceName);

    // 招待ログを追加する
    void pushInviteLog(const wxString& channel,const wxString& serviceName,const wxString& userName);

    // キックログを追加する
    void pushKickLog(const wxString& channel,const wxString& serviceName,const wxString& userName);

    // ニックネームの更新を行う
    void onUpdateNickName(const CMemberData& member);

private:

    // ログを追加する
    void pushLog(CChatLog* log,const wxString& serviceName);
};

}
