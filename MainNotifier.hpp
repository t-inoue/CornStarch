#pragma once
#include "header.hpp"
#include <wx/taskbar.h>

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
