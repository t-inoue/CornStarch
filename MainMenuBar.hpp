#pragma once
#include "MenuFile.hpp"
#include "MenuRegister.hpp"
#include "MenuChannel.hpp"
#include "MenuUpdate.hpp"

class CMainMenuBar : public wxMenuBar
{
private:

    CMenuFile* m_menuFile; // ファイル
    CMenuRegister* m_menuRegister; // 登録
    CMenuChannel* m_menuChannel; // チャンネル
    CMenuUpdate* m_menuUpdate; // 更新

public:
    CMainMenuBar(void);
    ~CMainMenuBar(void);

    // メニューバーを初期化する
    void init(void);

};

