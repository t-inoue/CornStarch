#include "SCNickTable.hpp"

using namespace std;

CSCNickTable::CSCNickTable(void)
{
}


CSCNickTable::~CSCNickTable(void)
{
}


//////////////////////////////////////////////////////////////////////


// テーブルに追加する
void CSCNickTable::addTableFromMembers(const vector<CMemberData*>& members)
{
    size_t size = members.size();
    for (size_t i = 0; i < size; i++){
        (*this)[members[i]->m_name] = members[i]->m_nick;
    }
}

// 本名に対応するニックネームを取得する
wxString CSCNickTable::getNickname(const wxString& name)
{
    if (!isExist(name)){
        return "";
    }

    return (*this)[name];
}

// ニックネームが登録されているか
bool CSCNickTable::isExist(const wxString& name)
{
    return find(name) != end();
}
