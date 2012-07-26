#pragma once
#include <wx/wxprec.h>
#include <wx/wx.h>
#include <wx/taskbar.h>

namespace CornStarch
{;

// 通知を行う
class CMainNotifier
{
private:
    wxTaskBarIcon* m_taskbar; // タスクバー

public:
    CMainNotifier(void);
    ~CMainNotifier(void);

    // 初期化を行う
    void init(void);

    // 通知を行う
    void messageNotify(const wxString& title, const wxString& message);
};

}