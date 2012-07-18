#include "MainMenuBar.hpp"


CMainMenuBar::CMainMenuBar(void)
    : m_menuFile(NULL), m_menuRegister(NULL), m_menuChannel(NULL), m_menuUpdate(NULL)
{
}


CMainMenuBar::~CMainMenuBar(void)
{
}


///////////////////////////////////


// メニューバーを初期化する
void CMainMenuBar::init(void)
{
    // 【ファイル】
    m_menuFile = new CMenuFile();
    m_menuFile->init();

    // 【登録】
    m_menuRegister = new CMenuRegister();
    m_menuRegister->init();

    // 【チャンネル】
    m_menuChannel = new CMenuChannel();
    m_menuChannel->init();

    // 【更新】
    m_menuUpdate = new CMenuUpdate();
    m_menuUpdate->init();

    // メニューバーに項目を追加する
    Append(m_menuFile, m_menuFile->getTitle());
    Append(m_menuRegister, m_menuRegister->getTitle());
    Append(m_menuChannel, m_menuChannel->getTitle());
    Append(m_menuUpdate, m_menuUpdate->getTitle());
}

