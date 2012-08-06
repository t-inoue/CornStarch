#pragma once
#include "SCTask.hpp"
#include "../SCMessageData.hpp"

namespace CornStarch
{
;

namespace StarChat
{
;

// ストリームを受信するためのタスク
class CSCGetStreamTask: public CSCTask
{
private:
    wxString m_userName;

public:
    CSCGetStreamTask(void);
    ~CSCGetStreamTask(void);

    wxString getUserName() const
    {
        return m_userName;
    }

    void setUserName(wxString userName)
    {
        m_userName = userName;
    }

private:
    ExitCode Entry(void);
    CSCMessageData parseStream(const std::string& json);
};

}
}
