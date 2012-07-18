//
//  IRCUserInfo.h
//  testtest
//
//  Created by  on 12/07/17.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef _IRCUserInfo_h
#define _IRCUserInfo_h
#include "header.hpp"
#include "IUserInfo.h"
using namespace std;

namespace CornStarch {
namespace IRC {
class CIRCUserInfo: public IUserInfo {

//            static const int MAX_LENGTH = 1024; // basicエンコード後の最大文字長
//            static const std::string NAME_KEY; // ユーザ名保存に使うキー名
//            static const std::string BASIC_KEY; // basic文字列保存に使うキー名

	std::string m_password; // ユーザ名
	std::string m_username; // ユーザ名
	std::string m_basic; // basic
	std::string m_nick; // ニックネーム
	std::vector<std::string> m_keywords; // キーワード

	bool m_login; // ログイン状況
	wxString m_currentCn; // 現在見ているチャンネル
	//CSCPersistent* m_persist; // 永続化情報を管理

public:
	CIRCUserInfo(void);
	virtual ~CIRCUserInfo(void);

	// ユーザ情報を初期化
	void init(void);

	std::string getPassword() {
		return m_password;
	}

	// ユーザ名をセット
	void setUserInfo(const std::string& username, const std::string& password);

	// ニックネームをセット
	void setNickName(const std::string& nickName);

	// キーワードをセット
	void setKeywords(const std::vector<std::string> keywords);

	// ログイン状況をセット
	void setLogin(bool login);

	// 現在見ているチャンネルをセット
	void setChannel(const wxString& channelName);

	// ユーザ名をゲット
	std::string getUserName(void) const;

	// ニックネームをゲット
	std::string getNickName(void) const;

	// キーワードをゲット
	std::vector<std::string> getKeywords(void) const;

	// basic暗号化された文字列を取得
	std::string getBasic(void) const;

	// ログイン状況を取得
	bool isLogin(void) const;

	// 現在見ているチャンネル名を取得する
	wxString getChannelwxString(void) const;

	// 現在見ているチャンネル名を取得する
	std::string getChannelString(void) const;

	// 永続化されたユーザ情報を読み込む
	void loadPersistentInfo(void);

	// ユーザ情報を永続化する
	void savePersistentInfo(void);

	// 永続化されたユーザ情報を消す
	void deletePersistentInfo(void);

	// ユーザ情報が永続化されているかどうか
	bool isSavedPersistentInfo(void) const;

	// メッセージ中にキーワードが含まれているか
	bool isCalled(const std::string& message) const;
};
}
} /* namespace CornStarch */

#endif
