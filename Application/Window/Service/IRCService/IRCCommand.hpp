
#ifndef IRCCOMMAND_HPP_
#define IRCCOMMAND_HPP_

#include <wx/wxprec.h>
#include <wx/wx.h>
namespace CornStarch
{
namespace IRC
{
class IRCCommand
{
public:
    //! IRCコマンドステータス名です。
    const static wxString OK;
    const static wxString USER;
    const static wxString PASS;
    const static wxString QUIT;
    const static wxString PING;
    const static wxString PONG;
    const static wxString JOIN;
    const static wxString PART;
    const static wxString TOPIC;
    const static wxString TOPIC_REPLY;
    const static wxString NAMES;
    const static wxString NAMES_REPLY;
    const static wxString NAMES_REPLY_END;
    const static wxString PRIVMSG;
    const static wxString NOTICE;
    const static wxString NICK;
    const static wxString KICK;
    const static wxString INVITE;
    const static wxString INVALID_USERNAME;
    const static wxString INVALID_CHANNEL;

};
}
} /* namespace CornStarch */
#endif /* IRCCOMMAND_HPP_ */
