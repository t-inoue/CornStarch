#pragma once
#include "header.hpp"
#include <wx/taskbar.h>

// �ʒm���s��
class CMainNotifier
{
private:
    wxTaskBarIcon* m_taskbar; // �^�X�N�o�[

public:
    CMainNotifier(void);
    ~CMainNotifier(void);

    // ���������s��
    void init(void);

    // �ʒm���s��
    void messageNotify(const wxString& title, const wxString& message);
};

