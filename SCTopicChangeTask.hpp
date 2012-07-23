#pragma once
#include "SCTask.hpp"

// �g�s�b�N��ύX���邽�߂̃^�X�N
class CSCTopicChangeTask : public CSCTask
{
private:
    wxString m_channel; // �`�����l����
    wxString m_topic; // �V�g�s�b�N

public:
    CSCTopicChangeTask(void);
    ~CSCTopicChangeTask(void);

    // ���������s��
    void init(int connectionId, wxEvtHandler* handler, const wxString& channel,
        const wxString& topic, const wxString& basic);

private:

    // StarChat�ɑ΂��ă��N�G�X�g�𑗐M����
    void sendRequestToSC(CSCClient* client);

    // HTTP���X�|���X����͂��ăC�x���g���쐬����
    CConnectionEventBase* parseHttpResponse(const std::string& responseBody);
};

