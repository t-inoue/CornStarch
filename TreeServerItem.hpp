#pragma once
#include "wx/treebase.h"

namespace CornStarch
{;

// ツリーのサーバ情報に入れるデータ
class CTreeServerItem : public wxTreeItemData
{
private:
    int m_serverId; // サーバID

public:
    CTreeServerItem(void);
    ~CTreeServerItem(void);

    // サーバIDをセット
    void setServerId(int id);

    // サーバIDを取得
    int getServerId(void) const;
};

}