#pragma once
#include "../../../../../DataStruct/MemberData.hpp"
#include "ConnectionEventBase.hpp"

namespace CornStarch
{;

// ユーザ情報更新時のイベント
class CUserStreamEvent : public CConnectionEventBase
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

}