#pragma once
#include "MenuPart.hpp"

// メニュー項目の【登録】
class CMenuRegister : public CMenuPart
{
public:
    CMenuRegister(void);
    ~CMenuRegister(void);

    // 初期化を行う
    void init(void);

};

