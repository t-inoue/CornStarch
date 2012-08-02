
#include "IRCUser.hpp"

namespace CornStarch
{
namespace IRC
{
CIRCUser::CIRCUser(void)
{

}

CIRCUser::~CIRCUser(void)
{
}

// ユーザ情報を初期化
void CIRCUser::init(void)
{
	m_login = true;
}

// ユーザ名をセット
void CIRCUser::setUserInfo(const wxString& username, const wxString& password)
{
	m_username = username;
	m_password = password;
}

// ニックネームをセット
void CIRCUser::setNickName(const wxString& nickName)
{
    m_username = nickName;
	m_nick = nickName;
}

// キーワードをセット
void CIRCUser::setKeywords(const std::vector<wxString> keywords)
{
	m_keywords = keywords;
}

// ログイン状況をセット
void CIRCUser::setLogin(bool login)
{
	m_login = login;
}

// 現在見ているチャンネルをセット
void CIRCUser::setChannel(const wxString& channelName)
{
	m_currentCn = channelName;
}

// ユーザ名をゲット
wxString CIRCUser::getUserName(void) const
{
	return m_username;
}

// ニックネームをゲット
wxString CIRCUser::getNickName(void) const
{
	return m_nick;
}

// キーワードをゲット
vector<wxString> CIRCUser::getKeywords(void) const
{
	return m_keywords;
}

// basic暗号化された文字列を取得
wxString CIRCUser::getBasic(void) const
{
	return m_basic;
}

// ログイン状況を取得
bool CIRCUser::isLogin(void) const
{
	return m_login;
}

// 現在見ているチャンネル名を取得する
wxString CIRCUser::getChannelwxString(void) const
{
	return m_currentCn;
}

// 現在見ているチャンネル名を取得する
wxString CIRCUser::getChannelString(void) const
{
	return m_currentCn;
}

// メッセージ中にキーワードが含まれているか
bool CIRCUser::isCalled(const wxString& message) const
{
	size_t size = m_keywords.size();
	for (size_t i = 0; i < size; i++){

		if (message.find(m_keywords[i]) != wxString::npos){
			return true;
		}
	}

	return false;
}

}
} /* namespace CornStarch */
