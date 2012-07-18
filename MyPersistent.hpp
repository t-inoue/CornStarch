#pragma once
#include <wx/string.h>
#include "header.hpp"

#ifdef _WIN32
#include <wx/msw/registry.h>
#else
#include <map>
#include <fstream>
#include <sys/stat.h>
#endif

// 永続化情報を管理するクラス
class CMyPersistent
{
#ifdef _WIN32
    wxRegKey* m_regKey; // レジストリアクセス
    static const wxString KEY_PLACE; // Keyのフルパス
#else
    std::ifstream m_ifs;
    std::ofstream m_ofs;
    std::map<wxString, wxString> m_value;    
#endif

public:
    CMyPersistent(void);
    ~CMyPersistent(void);

    // 初期化を行う
    void init(void);

    // keyとvalueを永続化する
    void saveInfo(const wxString& key, const wxString& value);

    // keyの情報を取得する
    wxString loadInfo(const wxString& key);

    // keyが登録されているかどうか
    bool isKeySaved(const wxString& key) const;

    // 永続化された情報を消す
    void deleteInfo(const wxString& key);
};

