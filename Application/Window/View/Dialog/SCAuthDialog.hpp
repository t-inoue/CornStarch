#pragma once
#include "AuthDialog.hpp"

namespace CornStarch
{;

// StarChatサーバ追加用認証ダイアログの作成
class CSCAuthDialog : public CAuthDialog
{
public:
    CSCAuthDialog(void);
    ~CSCAuthDialog(void);
};

}