#pragma once
#include "header.hpp"
#include "MemberData.hpp"

// ユーザ情報更新時のイベント
class CUserStreamEvent : public wxThreadEvent
{
private:
    CMemberData* m_member;

public:
    CUserStreamEvent(void);
    ~CUserStreamEvent(void);

    // メンバ情報をセット
    void setMember(const CMemberData& member);

    // メンバ情報を取得
    CMemberData getMember(void) const;
};

