#pragma once
#include "MenuPart.hpp"

// メニュー項目の【登録】
class CMenuServer : public CMenuPart
{
public:
    CMenuServer(void);
    ~CMenuServer(void);

    // 初期化を行う
    void init(void);

};

