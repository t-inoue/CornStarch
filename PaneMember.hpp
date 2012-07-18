#pragma once
#include "MemberData.hpp"
#include <vector>
#include "header.hpp"
#include "wx/listbox.h"

class CPaneMember : public wxListBox
{
public:
    CPaneMember(void);
    ~CPaneMember(void);

    // 初期化を行う
    void init(wxWindow* parent);

    // メンバーを表示する
    void displayMembers(const std::vector<CMemberData*>& members);
};

