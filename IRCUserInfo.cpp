//
//  IRCUserInfo.cpp
//  testtest
//
//  Created by  on 12/07/17.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "IRCUserInfo.h"

namespace CornStarch {
namespace IRC {
CIRCUserInfo::CIRCUserInfo(void) {

}

CIRCUserInfo::~CIRCUserInfo(void) {
}

// ユーザ情報を初期化
void CIRCUserInfo::init(void) {
	m_login = true;
	m_username = "TEST";
	//m_persist = new CSCPersistent();
	//m_persist->init();

}

// ユーザ名をセット
void CIRCUserInfo::setUserInfo(const string& username, const string& password) {
	m_username = username;
	m_password = password;
	// m_basic = crypt(username, password);
}

// ニックネームをセット
void CIRCUserInfo::setNickName(const string& nickName) {
	m_nick = nickName;
}

// キーワードをセット
void CIRCUserInfo::setKeywords(const std::vector<std::string> keywords) {
	m_keywords = keywords;
}

// ログイン状況をセット
void CIRCUserInfo::setLogin(bool login) {
	m_login = login;
}

// 現在見ているチャンネルをセット
void CIRCUserInfo::setChannel(const wxString& channelName) {
	m_currentCn = channelName;
}

// ユーザ名をゲット
string CIRCUserInfo::getUserName(void) const {
	return m_username;
}

// ニックネームをゲット
string CIRCUserInfo::getNickName(void) const {
	return m_nick;
}

// キーワードをゲット
vector<string> CIRCUserInfo::getKeywords(void) const {
	return m_keywords;
}

// basic暗号化された文字列を取得
string CIRCUserInfo::getBasic(void) const {
	return m_basic;
}

// ログイン状況を取得
bool CIRCUserInfo::isLogin(void) const {
	return m_login;
}

// 現在見ているチャンネル名を取得する
wxString CIRCUserInfo::getChannelwxString(void) const {
	return m_currentCn;
}

// 現在見ているチャンネル名を取得する
string CIRCUserInfo::getChannelString(void) const {
	string ch(m_currentCn.mb_str(wxConvUTF8));
	return ch;
}

// 永続化されたユーザ情報を読み込む
void CIRCUserInfo::loadPersistentInfo(void) {
//            m_username = m_persist->loadInfo(NAME_KEY);
//            m_basic = m_persist->loadInfo(BASIC_KEY);
}

// ユーザ情報を永続化する
void CIRCUserInfo::savePersistentInfo(void) {
//            m_persist->saveInfo(NAME_KEY, m_username);
//            m_persist->saveInfo(BASIC_KEY, m_basic);
}

// 永続化されたユーザ情報を消す
void CIRCUserInfo::deletePersistentInfo(void) {
//            m_persist->deleteInfo(NAME_KEY);
//            m_persist->deleteInfo(BASIC_KEY);
}

// ユーザ情報が永続化されているかどうか
bool CIRCUserInfo::isSavedPersistentInfo(void) const {
	return false;

//            if (!m_persist->isKeySaved(NAME_KEY) || !m_persist->isKeySaved(BASIC_KEY)){
//                return false;
//            }
//            
//            return true;
}

// メッセージ中にキーワードが含まれているか
bool CIRCUserInfo::isCalled(const string& message) const {
	size_t size = m_keywords.size();
	for (size_t i = 0; i < size; i++) {

		if (message.find(m_keywords[i]) != string::npos) {
			return true;
		}
	}

	return false;
}

//////////////////////////////////////////////////////////////////////

//        // basicエンコードする
//        string CIRCUserInfo::crypt(const string& username, const string& password)
//        {
//            
//            string str = m_username + ":" + password;
//            if (str.size() > MAX_LENGTH / 4){
//                m_basic = "";
//            }
//            
//            CMyCrypt crypt;
//            return crypt.encodeBase64(username + ":" + password);
//        }

}
} /* namespace CornStarch */
