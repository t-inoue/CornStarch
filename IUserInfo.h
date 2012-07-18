//
//  IUserInfo.h
//  testtest
//
//  Created by  on 12/07/17.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef _IUserInfo_h
#define _IUserInfo_h
#include <string>
#include <vector>

class IUserInfo{
public:
    IUserInfo(void){};
    virtual ~IUserInfo(void){};
    
    // ユーザ情報を初期化
    virtual void init(void) = 0;
    
    // ユーザ名をセット
    virtual void setUserInfo(const std::string& username, const std::string& password) = 0;
    
    // ニックネームをセット
    virtual void setNickName(const std::string& nickName) = 0;
    
    // キーワードをセット
    virtual void setKeywords(const std::vector<std::string> keywords) = 0;
    
    // ログイン状況をセット
    virtual void setLogin(bool login) = 0;
    
    // 現在見ているチャンネルをセット
    virtual void setChannel(const wxString& channelName) = 0;
    
    // ユーザ名をゲット
    virtual std::string getUserName(void) const = 0;
    
    // ニックネームをゲット
    virtual std::string getNickName(void) const = 0;
    
    // キーワードをゲット
    virtual std::vector<std::string> getKeywords(void) const = 0;
    
    // basic暗号化された文字列を取得
    virtual std::string getBasic(void) const = 0;
    
    // ログイン状況を取得
   virtual  bool isLogin(void) const = 0;
    
    // 現在見ているチャンネル名を取得する
    virtual wxString getChannelwxString(void) const = 0;
    
    // 現在見ているチャンネル名を取得する
    virtual std::string getChannelString(void) const = 0;
    
    // 永続化されたユーザ情報を読み込む
    virtual void loadPersistentInfo(void) = 0;
    
    // ユーザ情報を永続化する
    virtual void savePersistentInfo(void) = 0;
    
    // 永続化されたユーザ情報を消す
    virtual void deletePersistentInfo(void) = 0;
    
    // ユーザ情報が永続化されているかどうか
    virtual bool isSavedPersistentInfo(void) const =0 ;
    
    // メッセージ中にキーワードが含まれているか
    virtual bool isCalled(const std::string& message) const = 0;
};



#endif
