#pragma once
#include "header.hpp"
#include "ConnectionEventBase.hpp"

// ユーザ認証時のイベント
class CAuthEvent : public CConnectionEventBase
{
private:
    bool m_auth; // 認証の成否

public:
    CAuthEvent(void);
    ~CAuthEvent(void);

    // 認証の成否をセット
    void setAuthResult(bool ping);

    // 認証の成否を取得
    bool isAuthSucceeded(void) const;

};

