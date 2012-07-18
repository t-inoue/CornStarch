#pragma once
#include "ChannelData.hpp"
#include <vector>
#include "header.hpp"
#include "wx/listbox.h"

class CPaneCn : public wxListBox
{

public:
    CPaneCn(void);
    ~CPaneCn(void);

    // 初期化を行う
    void init(wxWindow* parent);

    // 選択済み項目を決める
    void setStringSelection(const wxString& channel);

    // 所属チャンネル一覧を表示
    void displayChannels(const std::vector<wxString>& channels);

};

