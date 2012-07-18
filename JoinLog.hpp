#pragma once
#include "ChatLog.hpp"
#include "SubscribeData.hpp"

// チャンネル参加ログ
class CJoinLog : public CChatLog
{
private:
    CSubscribeData* m_sub;
    wxString m_nick;

public:
    CJoinLog(void);
    ~CJoinLog(void);

    // 初期化を行う
    void init(const CSubscribeData& sub, const wxString& nick);

    // ログを取得する
    CSubscribeData getLog(void) const;

    // ニックネームを取得する
    wxString getNickName(void) const;

    // 本名に対応するニックネームが未知か
    bool isUnknownNick(const wxString& name) const;

    // ニックネームを更新する
    void updateNick(const wxString& nick);
};

