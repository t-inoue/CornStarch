#include "IRCStartTask.hpp"

namespace CornStarch
{;
namespace IRC
{;
CIRCStartTask::CIRCStartTask(wxThreadKind kind) :CIRCTask(kind)
{

}

CIRCStartTask::~CIRCStartTask()
{
}


// Run実行時に呼ばれる本体
wxThread::ExitCode CIRCStartTask::Entry(void)
{
    wxString pass(
            wxString::Format(wxT( "PASS %s\r\nNICK %s\r\nUSER %s * 0 :%s\r\n"),
                  getPassword().c_str(), getUserName().c_str(), getUserName().c_str(),
                  getUserName().c_str()));

    //m_client->setPort(m_client->getPort());
    m_client->setUrl(m_client->getHost());
    m_client->connect();
    //　IRCへの接続
    m_client->addCommandQueue(pass);







    // 成功時
    return (wxThread::ExitCode)0;
}
}
} /* namespace CornStarch */
