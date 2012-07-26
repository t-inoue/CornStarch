#pragma once
#include "MenuFile.hpp"
#include "MenuServer.hpp"
#include "MenuChannel.hpp"
#include "MenuUpdate.hpp"

namespace CornStarch
{;

class CMainMenuBar : public wxMenuBar
{
private:

    CMenuFile* m_menuFile; // ファイル
    CMenuServer* m_menuServer; // サーバ
    CMenuChannel* m_menuChannel; // チャンネル
    CMenuUpdate* m_menuUpdate; // 更新

public:
    CMainMenuBar(void);
    ~CMainMenuBar(void);

    // メニューバーを初期化する
    void init(void);

};

}