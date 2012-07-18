#include "GetMemberEvent.hpp"

using namespace std;

CGetMemberEvent::CGetMemberEvent(void)
{
}


CGetMemberEvent::~CGetMemberEvent(void)
{
    // メンバー要素の削除
    int size = (int)m_members.size();
    for (int i = 0; i < size; i++){
        delete m_members[i];
    }
}


//////////////////////////////////////////////////////////////////////


// メンバーをセット
void CGetMemberEvent::setMembers(const vector<CMemberData*>& members)
{
    m_members = members;
}


// メンバーを取得
vector<CMemberData*> CGetMemberEvent::getMembers(void) const
{
    return m_members;
}