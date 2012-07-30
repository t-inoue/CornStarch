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
    m_client->setUrl(m_client->getHost());
    m_client->connect();
    wxString pass(
            wxString::Format(wxT( "PASS %s"),
                  getPassword().c_str()));
    wxString nick(
              wxString::Format(wxT( "NICK %s"),

                    getUserName().c_str()));
    wxString user(
              wxString::Format(wxT( "USER %s * 0 :%s"),
                     getUserName().c_str(),
                    getUserName().c_str()));
    //　IRCへの接続
    m_client->addCommandQueue(pass);
    m_client->addCommandQueue(nick);
    m_client->addCommandQueue(user);

    // 成功時
    return (wxThread::ExitCode)0;
}
}
} /* namespace CornStarch */
