#include "ChatLog.hpp"


CChatLog::CChatLog(void)
{
}


CChatLog::~CChatLog(void)
{
}


//////////////////////////////////////////////////////////////////////


// ログの種類を取得
CChatLog::LOG_TYPE CChatLog::getLogType(void) const
{
    return m_type;
}

// 本名に対応するニックネームが未知か
bool CChatLog::isUnknownNick(const wxString& name) const
{
    return false;
}

// ニックネームを更新する
void CChatLog::updateNick(const wxString& nick)
{
}
