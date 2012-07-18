#pragma once
#include <wx/string.h>

// チャットのログを管理
class CChatLog
{
public:
    // チャットログのタイプ
    enum LOG_TYPE{
        LOG_MESSAGE,
        LOG_JOIN,
        LOG_PART,
        LOG_TOPIC,
        LOG_USER,
    };

protected:
    LOG_TYPE m_type; // ログのタイプ

public:
    CChatLog(void);
    virtual ~CChatLog(void);

    // ログの種類を取得
    LOG_TYPE getLogType(void) const;

    // 本名に対応するニックネームが未知か
    virtual bool isUnknownNick(const wxString& name) const;

    // ニックネームを更新する
    virtual void updateNick(const wxString& nick);
};

