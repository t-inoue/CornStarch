#include "JoinLog.hpp"

using namespace std;

CJoinLog::CJoinLog(void) : m_sub(NULL)
{
}


CJoinLog::~CJoinLog(void)
{
    delete m_sub;
}


//////////////////////////////////////////////////////////////////////


// 初期化を行う
void CJoinLog::init(const CSubscribeData& sub, const wxString& nick)
{
    if (m_sub == NULL){
        m_sub = new CSubscribeData();
    }
    *m_sub = sub;
    m_nick = nick;

    // タイプの指定
    m_type = LOG_JOIN;
}

// ログを取得する
CSubscribeData CJoinLog::getLog(void) const
{
    return *m_sub;
}

// ニックネームを取得する
wxString CJoinLog::getNickName(void) const
{
    return m_nick;
}

// 本名に対応するニックネームが未知か
bool CJoinLog::isUnknownNick(const wxString& name) const
{
    if (m_nick == ""){
        return true;
    }
    return false;
}

// ニックネームを更新する
void CJoinLog::updateNick(const wxString& nick)
{
    m_nick = nick;
}
