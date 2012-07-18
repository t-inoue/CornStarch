#pragma once
#include "MainWindow.hpp"

class CMainApplication : public wxApp
{
private:
    // フレームのサイズ
    static const int WIDTH = 600;
    static const int HEIGHT = 800;
    static const wxString TITLE;

    CMainWindow *m_window; // メインとなるウィンドウ

public:
    // アプリケーションの初期化を行う
    virtual bool OnInit();
};

