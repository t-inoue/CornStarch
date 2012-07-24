#include "SCNickChangeTask.hpp"

using namespace std;

CSCNickChangeTask::CSCNickChangeTask(void)
{
}


CSCNickChangeTask::~CSCNickChangeTask(void)
{
}


//////////////////////////////////////////////////////////////////////


// ���������s��
void CSCNickChangeTask::init(int connectionId, wxEvtHandler* handler, const wxString& nick,
    const wxString& name, const wxString& basic)
{
    CSCTask::init(connectionId, handler, basic);
    m_nick = nick;
    m_name = name;
}


//////////////////////////////////////////////////////////////////////


// StarChat�ɑ΂��ă��N�G�X�g�𑗐M����
void CSCNickChangeTask::sendRequestToSC(CSCClient* client)
{
    // GET���N�G�X�g�̑��M
    client->sendChangeNickRequest(m_name, m_nick, m_basic);
}

// HTTP���X�|���X����͂��ăC�x���g���쐬����
CConnectionEventBase* CSCNickChangeTask::parseHttpResponse(const string& responseBody)
{
    return NULL;
}
