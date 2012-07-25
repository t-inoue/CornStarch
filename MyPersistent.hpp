﻿#pragma once
#include <wx/string.h>
#include "header.hpp"
#include <wx/msw/registry.h>
#include <vector>
#include "IRCService.h"
#include "SCService.h"

// 永続化情報を管理するクラス
class CMyPersistent
{
    wxRegKey* m_regKey; // レジストリアクセス
    static const wxString KEY_PLACE; // Keyのフルパス

public:
    CMyPersistent(void);
    ~CMyPersistent(void);

    // 初期化を行う
    void init(void);

    // サービスを受け取り、保存する
    void saveService(const std::map<int,CChatServiceBase*>& services);

    // 保存されたサービス情報を基に、vectorにpushする
    void loadService(wxEvtHandler* handler, std::map<int,CChatServiceBase*>& services,
        int& serviceId);

private:

    // レジスタに保存する
    void saveReg(const CChatServiceBase* service, int uniqueId);

    // レジスタのサブキーからサービスを作成する
    CChatServiceBase* newService(wxEvtHandler* handler, const wxString& subKey,
        int serviceId);
};

