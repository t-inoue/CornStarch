#include "IRCParser.hpp"
#include "IRCMessageData.hpp"
#include "IRCCommand.hpp"
namespace CornStarch
{
;

namespace IRC
{
;

CIRCParser::CIRCParser() :
        m_messageId(0)
{
}
CIRCParser::~CIRCParser()
{
}
CIRCMessageData CIRCParser::parse(const wxString& content)
{
    CIRCMessageData message;
    if (content[0] == ':'){
        // 連番の一意なIDを作成
        m_messageId++;
        message.m_id = m_messageId;
        message.m_time = time(NULL);
        // ホスト
        int index = 1;
        int nextIndex = content.find(" ");
        message.m_host = content.substr(index, nextIndex - index);
        // ステータスコード
        index = nextIndex + 1;
        nextIndex = content.find(" ", index);
        message.m_statusCode = content.substr(index, nextIndex - index);
        // パラメータ
        index = nextIndex + 1;
        message.m_param = content.substr(index);
        // 名前
        vector<wxString> names = CStringUtility::split(message.m_host, "!");
        if (names.size() > 1){
            message.m_username = names[0];
        }
        // チャンネル
        size_t channelIndex = message.m_param.find(" ");
        if (channelIndex != wxString::npos){
            message.m_channel = message.m_param.substr(0, channelIndex);
        }
        // コンテント
        size_t contentIndex = message.m_param.find(":");
        if (contentIndex != wxString::npos){
            contentIndex++;
            message.m_body = message.m_param(contentIndex,
                    message.m_param.size() - contentIndex - 1);
        }
    }
    return message;
}

}
}
