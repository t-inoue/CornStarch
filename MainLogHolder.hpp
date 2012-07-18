#pragma once
#include "MessageLog.hpp"
#include "MemberLog.hpp"
#include "JoinLog.hpp"
#include "PartLog.hpp"
#include "TopicLog.hpp"
#include <vector>

// チャットのログを保持するクラス
class CMainLogHolder
{
private:
    std::vector<CChatLog*> m_logs; // ログを保存する
    static const int MAX_LENGTH = 10; //ログの最大個数

public:
    CMainLogHolder(void);
    ~CMainLogHolder(void);

    // ログ一覧を取得する
    std::vector<CChatLog*> getLogs(void) const;

    // メッセージログを追加する
    void pushMessageLog(const CMessageData& message, const wxString& nick = "");

    // チャンネル参加ログを追加する
    void pushJoinLog(const CSubscribeData& sub, const wxString& nick = "");

    // チャンネル退出ログを追加する
    void pushPartLog(const CSubscribeData& sub, const wxString& nick = "");

    // ニックネーム変更ログを追加する
    void pushChangeNickLog(const CMemberData& member);

    // トピック変更ログを追加する
    void pushTopicLog(const CChannelData& channel);

    // ニックネームの更新を行う
    void onUpdateNickName(const CMemberData& member);

private:

    // ログを追加する
    void pushLog(CChatLog* log);
};

