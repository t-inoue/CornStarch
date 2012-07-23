#include "MainNotifier.hpp"


CMainNotifier::CMainNotifier(void) : m_taskbar(NULL)
{
}


CMainNotifier::~CMainNotifier(void)
{
    delete m_taskbar;
}


//////////////////////////////////////////////////////////////////////


// ‰Šú‰»‚ðs‚¤
void CMainNotifier::init(void)
{
    m_taskbar = new wxTaskBarIcon();
    m_taskbar->SetIcon(wxIcon());
}

// ’Ê’m‚ðs‚¤
void CMainNotifier::messageNotify(const wxString& title, const wxString& message)
{
#ifdef _WIN32
    m_taskbar->ShowBalloon(title, message, 15000, wxICON_INFORMATION);
#else
    wxMessageBox(message, title);
#endif
}