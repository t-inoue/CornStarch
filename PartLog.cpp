#include "PartLog.hpp"

using namespace std;

CPartLog::CPartLog(void) : m_sub(NULL)
{
}


CPartLog::~CPartLog(void)
{
    delete m_sub;
}


//////////////////////////////////////////////////////////////////////


// 初期化を行う
void CPartLog::init(const CSubscribeData& sub, const wxString& nick)
{
    if (m_sub == NULL){
        m_sub = new CSubscribeData();
    }
    *m_sub = sub;
    m_nick = nick;

    // タイプの指定
    m_type = LOG_PART;
}

// ログを取得する
CSubscribeData CPartLog::getLog(void) const
{
    return *m_sub;
}

// ニックネームを取得する
wxString CPartLog::getNickName(void) const
{
    return m_nick;
}

// 本名に対応するニックネームが未知か
bool CPartLog::isUnknownNick(const wxString& name) const
{
    if (m_nick == ""){
        return true;
    }
    return false;
}

// ニックネームを更新する
void CPartLog::updateNick(const wxString& nick)
{
    m_nick = nick;
}
