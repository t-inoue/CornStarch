#include "IRCTask.hpp"

namespace CornStarch
{

IRCTask::IRCTask()
{
}

IRCTask::~IRCTask()
{
}

// Run実行時に呼ばれる本体
wxThread::ExitCode IRCTask::Entry(void)
{

    // 成功時
    return (wxThread::ExitCode)0;
}
} /* namespace CornStarch */
