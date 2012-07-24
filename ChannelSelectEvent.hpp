#pragma once
#include "wx/treebase.h"

// �`�����l���c���[�y�C���őI�����ɔ�������C�x���g
class CChannelSelectEvent : public wxTreeEvent
{
private:
    wxString m_text; // ���ږ�
    wxString m_server; // �T�[�o��
    int m_serverId; // �T�[�oID
    bool m_isServer; // �T�[�o�����ۂ�

public:
    CChannelSelectEvent(void);
    ~CChannelSelectEvent(void);

    // ���ږ����Z�b�g
    void setText(const wxString& text);

    // �T�[�o�����Z�b�g
    void setServer(const wxString& server);

    // �T�[�oID���Z�b�g
    void setServerId(int server);

    // �T�[�o�����ۂ����Z�b�g
    void setServerOrNot(bool isServer);

    // ���ږ����擾
    wxString getString(void) const;

    // �T�[�o�����擾
    wxString getServer(void) const;

    // �T�[�oID���擾
    int getServerId(void) const;

    // �T�[�o��I���������ۂ����擾
    bool isServerSelected(void) const;
};

