#pragma once
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

    // keyとvalueを永続化する
    void saveValue(const wxString& key, const wxString& value);

    // keyの情報を取得する
    wxString loadValue(const wxString& key);

    // keyが登録されているかどうか
    bool isKeySaved(const wxString& key) const;

    // 永続化された情報を消す
    void deleteValue(const wxString& key);

    // サービスを受け取り、ファイルに保存する
    void saveService(const std::vector<CChatServiceBase*>& services);

    // 保存されたサービス情報を基に、vectorにpushする
    void loadService(wxEvtHandler* handler, std::vector<CChatServiceBase*>& services,
        int& serviceId);
};

