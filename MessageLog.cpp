#include "MessageLog.hpp"

using namespace std;

CMessageLog::CMessageLog(void) : m_message(NULL)
{
}


CMessageLog::~CMessageLog(void)
{
    delete m_message;
}


//////////////////////////////////////////////////////////////////////


// 初期化を行う
void CMessageLog::init(const CMessageData& message, const wxString& nick)
{
    if (m_message == NULL){
        m_message = new CMessageData();
    }
    *m_message = message;
    m_nick = nick;

    // タイプの指定
    m_type = LOG_MESSAGE;
}

// ログを取得する
CMessageData CMessageLog::getLog(void) const
{
    return *m_message;
}

// ニックネームを取得する
wxString CMessageLog::getNickName(void) const
{
    return m_nick;
}

// 本名に対応するニックネームが未知か
bool CMessageLog::isUnknownNick(const wxString& name) const
{
    if (m_nick == ""){
        return true;
    }
    return false;
}

// ニックネームを更新する
void CMessageLog::updateNick(const wxString& nick)
{
    m_nick = nick;
}
