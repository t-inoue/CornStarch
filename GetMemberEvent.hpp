#pragma once
#include "header.hpp"
#include "vector"
#include "MemberData.hpp"

// メンバー受信時のイベント
class CGetMemberEvent : public wxThreadEvent
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

