#pragma once
#include <vector>
#include "ConnectionEventBase.hpp"

namespace CornStarch
{;

// メンバー受信時のイベント
class CGetMemberEvent : public CConnectionEventBase
{
private:
    std::vector<CMemberData*> m_members; // メンバー

public:
    CGetMemberEvent(void);
    ~CGetMemberEvent(void);

    // メンバーをセット
    void setMembers(const std::vector<CMemberData*>& members);

    // メンバーを取得
    std::vector<CMemberData*> getMembers(void) const;
};

}