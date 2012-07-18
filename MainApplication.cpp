#include "MainApplication.hpp"

const wxString CMainApplication::TITLE = "CornStarch"; // ウィンドウタイトル

// アプリケーションクラスを認識させる
wxIMPLEMENT_APP(CMainApplication);

// アプリケーションの初期化を行う
bool CMainApplication::OnInit()
{
    // 通信の準備
    wxSocketBase::Initialize();

    // メインウィンドウの初期化
    m_window = new CMainWindow();
    m_window->Create(NULL, wxID_ANY, TITLE, wxDefaultPosition,
        wxSize(WIDTH, HEIGHT));
    m_window->init();

    // メインウィンドウの表示
    m_window->Show(true);

    // 続きの処理を実行
    return true;
}