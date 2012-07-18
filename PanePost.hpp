#pragma once
#include "header.hpp"

// メッセージ投稿用ペイン
class CPanePost : public wxTextCtrl
{
public:
    CPanePost(void);
    ~CPanePost(void);

    // 初期化を行う
    void init(wxWindow* parent);
};

