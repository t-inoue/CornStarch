#pragma once
#include <wx/string.h>
#include "header.hpp"

#ifdef _WIN32
#include <wx/msw/registry.h>
#else
#include <map>
#include <fstream>
#include <sys/stat.h>
#include <string>
#include <stdlib.h>
#endif

// 永続化情報を管理するクラス
class CMyPersistent
{
#ifdef _WIN32
    wxRegKey* m_regKey; // レジストリアクセス
    static const wxString KEY_PLACE; // Keyのフルパス
#else
    static const wxString FILE_PATH; // 保存するパス
#endif

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

#ifndef _WIN32

private:
    // ファイルをmapとして開く
    std::map<std::string, std::string> loadFileAsMap(void) const;

#endif

};

