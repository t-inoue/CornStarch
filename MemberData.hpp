#pragma once
#include <wx/string.h>
#include <vector>

// メンバーを表すクラス
class CMemberData
{
public:
    wxString m_name; // 名前(本名)
    wxString m_nick; // ニックネーム
    std::vector<wxString> m_keywords; // キーワード

    CMemberData(const wxString& name, const wxString& nick)
        : m_name(name), m_nick(nick){}

    CMemberData(void){}
};

