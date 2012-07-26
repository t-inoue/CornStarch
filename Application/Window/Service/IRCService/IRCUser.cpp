//
//  IRCUserInfo.cpp
//  testtest
//
//  Created by  on 12/07/17.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

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
	m_username = "TEST";
	//m_persist = new CSCPersistent();
	//m_persist->init();

}

// ユーザ名をセット
void CIRCUser::setUserInfo(const wxString& username, const wxString& password)
{
	m_username = username;
	m_password = password;
	// m_basic = crypt(username, password);
}

// ニックネームをセット
void CIRCUser::setNickName(const wxString& nickName)
{
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

// 永続化されたユーザ情報を読み込む
void CIRCUser::loadPersistentInfo(void)
{
//            m_username = m_persist->loadInfo(NAME_KEY);
//            m_basic = m_persist->loadInfo(BASIC_KEY);
}

// ユーザ情報を永続化する
void CIRCUser::savePersistentInfo(void)
{
//            m_persist->saveInfo(NAME_KEY, m_username);
//            m_persist->saveInfo(BASIC_KEY, m_basic);
}

// 永続化されたユーザ情報を消す
void CIRCUser::deletePersistentInfo(void)
{
//            m_persist->deleteInfo(NAME_KEY);
//            m_persist->deleteInfo(BASIC_KEY);
}

// ユーザ情報が永続化されているかどうか
bool CIRCUser::isSavedPersistentInfo(void) const
{
	return false;

//            if (!m_persist->isKeySaved(NAME_KEY) || !m_persist->isKeySaved(BASIC_KEY)){
//                return false;
//            }
//            
//            return true;
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

//////////////////////////////////////////////////////////////////////

//        // basicエンコードする
//        wxString CIRCUserInfo::crypt(const wxString& username, const wxString& password)
//        {
//            
//            wxString str = m_username + ":" + password;
//            if (str.size() > MAX_LENGTH / 4){
//                m_basic = "";
//            }
//            
//            CMyCrypt crypt;
//            return crypt.encodeBase64(username + ":" + password);
//        }

}
} /* namespace CornStarch */
