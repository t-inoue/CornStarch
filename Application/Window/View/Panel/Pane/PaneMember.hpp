#pragma once
#include "../../../../DataStruct/MemberData.hpp"
#include <vector>
#include <wx/wxprec.h>
#include <wx/wx.h>
#include <wx/listbox.h>

namespace CornStarch
{;

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

}