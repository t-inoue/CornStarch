#pragma once
#include "ChatLog.hpp"
#include "MessageData.hpp"

// メッセージのログ
class CMessageLog : public CChatLog
{
private:
    CMessageData* m_message;
    wxString m_nick;

public:
    CMessageLog(void);
    ~CMessageLog(void);

    // 初期化を行う
    void init(const CMessageData& message, const wxString& nick);

    // ログを取得する
    CMessageData getLog(void) const;

    // ニックネームを取得する
    wxString getNickName(void) const;

    // 本名に対応するニックネームが未知か
    bool isUnknownNick(const wxString& name) const;

    // ニックネームを更新する
    void updateNick(const wxString& nick);
};

