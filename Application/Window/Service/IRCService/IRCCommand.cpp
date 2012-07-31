#include "IRCCommand.hpp"
#include <string>
namespace CornStarch
{
namespace IRC
{
const wxString IRCCommand::OK = "001";
const wxString IRCCommand::PASS = "PASS";
const wxString IRCCommand::ERROR = "ERROR";
const wxString IRCCommand::USER = "USER";
const wxString IRCCommand::PING = "PING";
const wxString IRCCommand::PONG = "PONG";
const wxString IRCCommand::QUIT = "QUIT";
const wxString IRCCommand::JOIN = "JOIN";
const wxString IRCCommand::PART = "PART";
const wxString IRCCommand::TOPIC = "TOPIC";
const wxString IRCCommand::TOPIC_REPLY ="332";
const wxString IRCCommand::NAMES ="NAMES";
const wxString IRCCommand::NAMES_REPLY = "353";
const wxString IRCCommand::NAMES_REPLY_END ="366";
const wxString IRCCommand::PRIVMSG ="PRIVMSG";
const wxString IRCCommand::NOTICE = "NOTICE";
const wxString IRCCommand::NICK = "NICK";
const wxString IRCCommand::KICK = "KICK";
const wxString IRCCommand::INVITE ="INVITE";
const wxString IRCCommand::INVALID_USERNAME = "433";
const wxString IRCCommand::INVALID_CHANNEL = "432";
}
} /* namespace CornStarch */
