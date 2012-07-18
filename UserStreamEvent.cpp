#include "UserStreamEvent.hpp"


CUserStreamEvent::CUserStreamEvent(void) : m_member(NULL)
{
}


CUserStreamEvent::~CUserStreamEvent(void)
{
    delete m_member;
}


///////////////////////////////////////////////////////////////////////////


// メンバ情報をセット
void CUserStreamEvent::setMember(const CMemberData& member)
{
    if (m_member == NULL){
        m_member = new CMemberData();
    }

    *m_member = member;
}

// メンバ情報を取得
CMemberData CUserStreamEvent::getMember(void) const
{
    return *m_member;
}
