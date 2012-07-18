#include "PaneCn.hpp"

using namespace std;

CPaneCn::CPaneCn(void)
{
}


CPaneCn::~CPaneCn(void)
{
}


//////////////////////////////////////////////////////////////////////


// 初期化を行う
void CPaneCn::init(wxWindow* parent)
{
    // スクロールバー(水平、垂直を必要に応じて)、ソート
    Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL,
        wxLB_NEEDED_SB | wxLB_SORT | wxLB_HSCROLL);
}

// 選択済み項目を決める
void CPaneCn::setStringSelection(const wxString& channel)
{
    SetStringSelection(channel);
}

// 所属チャンネル一覧を表示
void CPaneCn::displayChannels(const vector<wxString>& channels)
{
    // 現在の表示文字をクリアする
    this->Clear();

    int size = (int)channels.size();
    for (int i = 0; i < size; i++){

        this->Append(channels[i]);
    }
}

