#pragma once
#include "ChatLog.hpp"
#include "MemberData.hpp"

// メンバー情報更新ログ
class CMemberLog : public CChatLog
{
private:
    CMemberData* m_member;

public:
    CMemberLog(void);
    ~CMemberLog(void);

    // 初期化を行う
    void init(const CMemberData& member);

    // ログを取得する
    CMemberData getLog(void) const;
};

