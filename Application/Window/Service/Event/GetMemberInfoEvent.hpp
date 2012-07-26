#pragma once
#include "ConnectionEventBase.hpp"

namespace CornStarch
{;

// メンバー情報取得時のイベント
class CGetMemberInfoEvent : public CConnectionEventBase
{
private:
    CMemberData* m_member; // メンバー

public:
    CGetMemberInfoEvent(void);
    ~CGetMemberInfoEvent(void);

    // メンバーをセット
    void setMember(const CMemberData& member);

    // メンバーを取得
    CMemberData getMember(void) const;
};

}