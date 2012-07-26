#pragma once
#include "MenuPart.hpp"

namespace CornStarch
{;

// メニュー項目の【ファイル】
class CMenuFile : public CMenuPart
{

public:
    CMenuFile(void);
    ~CMenuFile(void);

    // 初期化を行う
    void init(void);
};

}