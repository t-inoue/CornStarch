#pragma once
#include <map>
#include <vector>
#include "MemberData.hpp"

// 本名とニックネームの対応付けを行うためのテーブルクラス
class CSCNickTable : public std::map<wxString, wxString>
{
public:
    CSCNickTable(void);
    ~CSCNickTable(void);

    // テーブルに追加する
    void addTableFromMembers(const std::vector<CMemberData*>& members);

    // 本名に対応するニックネームを取得する
    wxString getNickname(const wxString& name);

    // ニックネームが登録されているか
    bool isExist(const wxString& name);
};

