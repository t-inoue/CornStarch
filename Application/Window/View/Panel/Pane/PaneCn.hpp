#pragma once
#include "../../../Service/ChatServiceBase.hpp"
#include <wx/wxprec.h>
#include <wx/wx.h>
#include <wx/treectrl.h>
#include "ChannelSelectEvent.hpp"
#include "TreeServerItem.hpp"
#include <map>

namespace CornStarch
{;

// イベントの宣言
wxDECLARE_EVENT(myEVT_SELECT_TREE_NODE, CChannelSelectEvent);

class CPaneCn : public wxTreeCtrl
{
    // wxWindowイベントを処理させたいクラスに利用するマクロ
    DECLARE_EVENT_TABLE()

public:
    CPaneCn(void);
    ~CPaneCn(void);

    // 初期化を行う
    void init(wxWindow* parent);

    // 選択済み項目を決める
    void setStringSelection(const wxString& channel);

    // 所属チャンネル一覧を表示
    void displayChannels(const std::map<int, CChatServiceBase*>& services);

private:
    // チャンネルが選択された際のイベント処理
    void onChannelSelected(wxTreeEvent& event);

};

}