#include "TreeServerItem.hpp"


CTreeServerItem::CTreeServerItem(void)
{
}


CTreeServerItem::~CTreeServerItem(void)
{
}


//////////////////////////////////////////////////////////////////////


// �T�[�oID���Z�b�g
void CTreeServerItem::setServerId(int id)
{
    m_serverId = id;
}

// �T�[�oID���擾
int CTreeServerItem::getServerId(void) const
{
    return m_serverId;
}
