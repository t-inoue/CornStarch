#include "SCTopicChangeTask.hpp"

using namespace std;

CSCTopicChangeTask::CSCTopicChangeTask(void)
{
}


CSCTopicChangeTask::~CSCTopicChangeTask(void)
{
}


//////////////////////////////////////////////////////////////////////


// ���������s��
void CSCTopicChangeTask::init(int connectionId, wxEvtHandler* handler, const wxString& channel,
    const wxString& topic, const wxString& basic)
{
    CSCTask::init(connectionId, handler, basic);
    m_channel = channel;
    m_topic = topic;
}


//////////////////////////////////////////////////////////////////////


// StarChat�ɑ΂��ă��N�G�X�g�𑗐M����
void CSCTopicChangeTask::sendRequestToSC(CSCClient* client)
{
    // GET���N�G�X�g�̑��M
    client->sendChangeTopicRequest(m_channel, m_topic, m_basic);
}

// HTTP���X�|���X����͂��ăC�x���g���쐬����
CConnectionEventBase* CSCTopicChangeTask::parseHttpResponse(const string& responseBody)
{
    return NULL;
}
