#pragma once
#include <wx/wxprec.h>
#include <wx/wx.h>

namespace CornStarch
{;

// メッセージ投稿用ペイン
class CPanePost : public wxTextCtrl
{
public:
    CPanePost(void);
    ~CPanePost(void);

    // 初期化を行う
    void init(wxWindow* parent);
};

}