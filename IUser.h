#ifndef _IUserInfo_h
#define _IUserInfo_h
#include <string>
#include <vector>

//　ユーザーのインターフェース
class IUser{
public:
    IUser(void){};
    virtual ~IUser(void){};

    // ユーザ情報を初期化
    virtual void init(void) = 0;

    // ユーザ名をセット
    virtual void setUserInfo(const wxString& username, const wxString& password) = 0;

    // ニックネームをセット
    virtual void setNickName(const wxString& nickName) = 0;

    // キーワードをセット
    virtual void setKeywords(const std::vector<wxString> keywords) = 0;

    // ログイン状況をセット
    virtual void setLogin(bool login) = 0;

    // 現在見ているチャンネルをセット
    virtual void setChannel(const wxString& channelName) = 0;

    // ユーザ名をゲット
    virtual wxString getUserName(void) const = 0;

    // ニックネームをゲット
    virtual wxString getNickName(void) const = 0;

    // キーワードをゲット
    virtual std::vector<wxString> getKeywords(void) const = 0;

    // basic暗号化された文字列を取得
    virtual wxString getBasic(void) const = 0;

    // ログイン状況を取得
    virtual  bool isLogin(void) const = 0;

    // 現在見ているチャンネル名を取得する
    virtual wxString getChannelString(void) const = 0;

    // メッセージ中にキーワードが含まれているか
    virtual bool isCalled(const wxString& message) const =0;

    // basic認証用文字列をセット
    virtual void setBasic(const wxString& basic) = 0;

    // ユーザ名をセット
    virtual void setUserName(const wxString& name) = 0;

    // basic文字列を保存する際のキー名を取得
    virtual wxString getBasicKey(void) const = 0;

    // 名前を保存する際のキー名を取得
    virtual wxString getNameKey(void) const = 0;

};
#endif
