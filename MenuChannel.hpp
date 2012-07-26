#pragma once
#include "MenuPart.hpp"

namespace CornStarch
{;

// メニュー項目の【チャンネル】
class CMenuChannel : public CMenuPart
{

public:
    CMenuChannel(void);
    ~CMenuChannel(void);

    // 初期化を行う
    void init(void);
};

}