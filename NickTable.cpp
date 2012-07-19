#include "NickTable.hpp"

using namespace std;

CNickTable::CNickTable(void)
{
}


CNickTable::~CNickTable(void)
{
}


//////////////////////////////////////////////////////////////////////


// テーブルに追加する
void CNickTable::addTableFromMembers(const vector<CMemberData*>& members)
{
    size_t size = members.size();
    for (size_t i = 0; i < size; i++){
        (*this)[members[i]->m_name] = members[i]->m_nick;
    }
}

// 本名に対応するニックネームを取得する
wxString CNickTable::getNickname(const wxString& name)
{
    if (!isExist(name)){
        return "";
    }

    return (*this)[name];
}

// ニックネームが登録されているか
bool CNickTable::isExist(const wxString& name)
{
    return find(name) != end();
}
