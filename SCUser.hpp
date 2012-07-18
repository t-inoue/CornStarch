#pragma once
#include "header.hpp"
#include <vector>
#include <wx/base64.h>

// StarChatユーザの情報を格納
class CSCUser
{
private:

    static const int MAX_LENGTH = 1024; // basicエンコード後の最大文字長
    static const wxString NAME_KEY; // ユーザ名保存に使うキー名
    static const wxString BASIC_KEY; // basic文字列保存に使うキー名

    wxString m_username; // ユーザ名
    wxString m_basic; // basic
    wxString m_nick; // ニックネーム
    std::vector<wxString> m_keywords; // キーワード

    bool m_login; // ログイン状況
    wxString m_currentCn; // 現在見ているチャンネル

public:
    CSCUser(void);
    ~CSCUser(void);

    // ユーザ情報を初期化
    void init(void);

    // ユーザ名をセット
    void setUserInfo(const wxString& username, const wxString& password);

    // ニックネームをセット
    void setNickName(const wxString& nickName);

    // キーワードをセット
    void setKeywords(const std::vector<wxString> keywords);

    // ログイン状況をセット
    void setLogin(bool login);

    // 現在見ているチャンネルをセット
    void setChannel(const wxString& channel);

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
    wxString getChannelString(void) const;

    // メッセージ中にキーワードが含まれているか
    bool isCalled(const wxString& message) const;

    // basic認証用文字列をセット
    void setBasic(const wxString& basic);

    // ユーザ名をセット
    void setUserName(const wxString& name);

    // basic文字列を保存する際のキー名を取得
    wxString getBasicKey(void) const;

    // 名前を保存する際のキー名を取得
    wxString getNameKey(void) const;

private:

    // basicエンコードする
    wxString crypt(const wxString& username, const wxString& password);

};

