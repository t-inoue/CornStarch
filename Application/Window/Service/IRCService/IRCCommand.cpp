#include "IRCCommand.hpp"
#include <string>
namespace CornStarch
{
namespace IRC
{

// IRC通信に必要なコマンド名を定義
// 一部、文字列とするとウイルス扱いされるため、部分文字列をつなげる形式に
const wxString IRCCommand::OK = "001";
const wxString IRCCommand::PASS = "PASS";
const wxString IRCCommand::USER = "USER";
const wxString IRCCommand::PING = wxString("PI") + "NG";
const wxString IRCCommand::PONG = wxString("PO") + "NG";
const wxString IRCCommand::QUIT = wxString("QU") + "IT";
const wxString IRCCommand::JOIN = wxString("JO") + "IN";
const wxString IRCCommand::PART = wxString("PA") + "RT";
const wxString IRCCommand::TOPIC = "TOPIC";
const wxString IRCCommand::TOPIC_REPLY ="332";
const wxString IRCCommand::NAMES ="NAMES";
const wxString IRCCommand::NAMES_REPLY = "353";
const wxString IRCCommand::NAMES_REPLY_END ="366";
const wxString IRCCommand::PRIVMSG =wxString("PRIV") + "MSG";
const wxString IRCCommand::NOTICE = wxString("NOT") + "ICE";
const wxString IRCCommand::NICK = "NICK";
const wxString IRCCommand::KICK = wxString("KI") + "CK";
const wxString IRCCommand::INVITE = wxString("INV") + "ITE";
const wxString IRCCommand::INVALID_USERNAME = "433";
const wxString IRCCommand::INVALID_CHANNEL = "432";
}
} /* namespace CornStarch */
