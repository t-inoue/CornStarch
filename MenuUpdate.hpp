#pragma once
#include "MenuPart.hpp"

// メニュー項目の【更新】
class CMenuUpdate : public CMenuPart
{
public:
    CMenuUpdate(void);
    ~CMenuUpdate(void);

    // 初期化を行う
    void init(void);
};

