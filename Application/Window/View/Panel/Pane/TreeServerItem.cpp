#include "TreeServerItem.hpp"

namespace CornStarch
{;

CTreeServerItem::CTreeServerItem(void)
{
}


CTreeServerItem::~CTreeServerItem(void)
{
}


//////////////////////////////////////////////////////////////////////


// サーバIDをセット
void CTreeServerItem::setServerId(int id)
{
    m_serverId = id;
}

// サーバIDを取得
int CTreeServerItem::getServerId(void) const
{
    return m_serverId;
}

}