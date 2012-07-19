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
#include "IUser.h"
using namespace std;

namespace CornStarch {
namespace IRC {
class CIRCUser: public IUser {

//            static const int MAX_LENGTH = 1024; // basicエンコード後の最大文字長
//            static const wxString NAME_KEY; // ユーザ名保存に使うキー名
//            static const wxString BASIC_KEY; // basic文字列保存に使うキー名

	wxString m_password; // ユーザ名
	wxString m_username; // ユーザ名
	wxString m_basic; // basic
	wxString m_nick; // ニックネーム
	std::vector<wxString> m_keywords; // キーワード

	bool m_login; // ログイン状況
	wxString m_currentCn; // 現在見ているチャンネル
	//CSCPersistent* m_persist; // 永続化情報を管理

public:
	CIRCUser(void);
	virtual ~CIRCUser(void);

	// ユーザ情報を初期化
	void init(void);

	wxString getPassword() {
		return m_password;
	}

	// ユーザ名をセット
	void setUserInfo(const wxString& username, const wxString& password);

	// ニックネームをセット
	void setNickName(const wxString& nickName);

	// キーワードをセット
	void setKeywords(const std::vector<wxString> keywords);

	// ログイン状況をセット
	void setLogin(bool login);

	// 現在見ているチャンネルをセット
	void setChannel(const wxString& channelName);

	// ユーザ名をゲット
	wxString getUserName(void) const;

	// ニックネームをゲット
	wxString getNickName(void) const;

	// キーワードをゲット
	std::vector<wxString> getKeywords(void) const;

	// basic暗号化された文字列を取得
	wxString getBasic(void) const;

	// ログイン状況を取得
	bool isLogin(void) const;

	// 現在見ているチャンネル名を取得する
	wxString getChannelwxString(void) const;

	// 現在見ているチャンネル名を取得する
	wxString getChannelString(void) const;

	// 永続化されたユーザ情報を読み込む
	void loadPersistentInfo(void);

	// ユーザ情報を永続化する
	void savePersistentInfo(void);

	// 永続化されたユーザ情報を消す
	void deletePersistentInfo(void);

	// ユーザ情報が永続化されているかどうか
	bool isSavedPersistentInfo(void) const;

	// メッセージ中にキーワードが含まれているか
	bool isCalled(const wxString& message) const;

    // basic認証用文字列をセット
    virtual void setBasic(const wxString& basic) {};

    // ユーザ名をセット
    virtual void setUserName(const wxString& name) {};

    // basic文字列を保存する際のキー名を取得
    virtual wxString getBasicKey(void) const {return "";};

    // 名前を保存する際のキー名を取得
    virtual wxString getNameKey(void) const {return "";};

};
}
} /* namespace CornStarch */

#endif
