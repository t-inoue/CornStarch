#pragma once
#include "wx/treebase.h"

// �c���[�̃T�[�o���ɓ����f�[�^
class CTreeServerItem : public wxTreeItemData
{
private:
    int m_serverId; // �T�[�oID

public:
    CTreeServerItem(void);
    ~CTreeServerItem(void);

    // �T�[�oID���Z�b�g
    void setServerId(int id);

    // �T�[�oID���擾
    int getServerId(void) const;
};

