#ifndef IRCMESSAGE_HPP_
#define IRCMESSAGE_HPP_

#include <wx/wxprec.h>
#include <wx/wx.h>
#include <ctime>
#include "../../../DataStruct/MessageData.hpp"
namespace CornStarch
{
namespace IRC
{
class CIRCMessageData :public CMessageData
{
public:
    CIRCMessageData();
    virtual ~CIRCMessageData();

    wxString m_host;
    wxString m_param;
    wxString m_statusCode;
    wxString m_target;
};
}
} /* namespace CornStarch */
#endif /* IRCMESSAGE_HPP_ */
