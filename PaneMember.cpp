#include "PaneMember.hpp"

using namespace std;

CPaneMember::CPaneMember(void)
{
}


CPaneMember::~CPaneMember(void)
{
}


//////////////////////////////////////////////////////////////////////


// 初期化を行う
void CPaneMember::init(wxWindow* parent)
{
    // スクロールバー(水平、垂直を必要に応じて)、ソート
    Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL,
        wxLB_NEEDED_SB | wxLB_SORT | wxLB_HSCROLL);
}

// メンバーを表示する
void CPaneMember::displayMembers(const vector<CMemberData*>& members)
{
    // 現在の表示をクリアする
    this->Clear();

    int size = (int)members.size();
    for (int i = 0; i < size; i++){

        this->Append(members[i]->m_nick);
    }
}