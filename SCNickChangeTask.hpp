#pragma once
#include "SCTask.hpp"

// �j�b�N�l�[���ύX���s�����߂̃^�X�N
class CSCNickChangeTask : public CSCTask
{
private:
    wxString m_nick; // �j�b�N�l�[��
    wxString m_name; // �{��

public:
    CSCNickChangeTask(void);
    ~CSCNickChangeTask(void);

    // ���������s��
    void init(int connectionId, wxEvtHandler* handler, const wxString& nick, 
        const wxString& name, const wxString& basic);

private:

    // StarChat�ɑ΂��ă��N�G�X�g�𑗐M����
    void sendRequestToSC(CSCClient* client);

    // HTTP���X�|���X����͂��ăC�x���g���쐬����
    CConnectionEventBase* parseHttpResponse(const std::string& responseBody);
};

