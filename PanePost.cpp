#include "PanePost.hpp"


CPanePost::CPanePost(void)
{
}


CPanePost::~CPanePost(void)
{
}


//////////////////////////////////////////////////////////////////////


// 初期化を行う
void CPanePost::init(wxWindow* parent)
{
    // テキスト領域の作成
    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, 
        wxDefaultSize, wxTE_PROCESS_ENTER);
}
