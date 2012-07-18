#include "MemberLog.hpp"


CMemberLog::CMemberLog(void) : m_member(NULL)
{
}


CMemberLog::~CMemberLog(void)
{
    delete m_member;
}


//////////////////////////////////////////////////////////////////////


// 初期化を行う
void CMemberLog::init(const CMemberData& member)
{
    if (m_member == NULL){
        m_member = new CMemberData();
    }
    *m_member = member;

    // タイプの指定
    m_type = LOG_USER;
}

// ログを取得する
CMemberData CMemberLog::getLog(void) const
{
    return *m_member;
}