#include "GetMemberInfoEvent.hpp"


CGetMemberInfoEvent::CGetMemberInfoEvent(void) : m_member(NULL)
{
}


CGetMemberInfoEvent::~CGetMemberInfoEvent(void)
{
    delete m_member;
}


//////////////////////////////////////////////////////////////////////


// チャンネルをセット
void CGetMemberInfoEvent::setMember(const CMemberData& member)
{
    if (m_member == NULL){
        m_member = new CMemberData();
    }

    *m_member = member;
}

// チャンネルを取得
CMemberData CGetMemberInfoEvent::getMember(void) const
{
    return *m_member;
}
