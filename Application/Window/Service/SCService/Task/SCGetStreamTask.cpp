#include "SCGetStreamTask.hpp"

using namespace std;
#include "../../ConnectionStatusChecker.h"
namespace CornStarch
{
;
namespace StarChat
{
;

CSCGetStreamTask::CSCGetStreamTask(void) :
        CSCTask(wxTHREAD_JOINABLE)
{
}

CSCGetStreamTask::~CSCGetStreamTask(void)
{
}

// メインループ
wxThread::ExitCode CSCGetStreamTask::Entry()
{
    // クライアントの初期化
    CSCClient* client = new CSCClient();
    client->init();
    client->setHost(m_host);
    client->setPort(m_port);
    client->connect();
    client->sendGetStreamRequest(m_userName, m_basic);
    client->recvHttpResponseBody();

    // Statusチェックの間隔計測
    CConnectionStatusChecker checker(m_observer);
    // Deleteされるまでループ
    while (!TestDestroy()){

        // CPUを休ませる(100msec)
        wxUsleep(100);

        // ストリーム(JSON形式)を受信
        CSCJsonParser parser;
        string jsons = client->getStreamJson();
        vector<string> jsonVec = parser.getJsonVec(jsons);

        // 各JSONを解析して、イベントを送信する
        size_t size = jsonVec.size();
        if (size != 0){
            for (size_t i = 0; i < size; i++){
                CSCMessageData message = parseStream(jsonVec[i]);
                m_observer->onMessageReceived(&message);
            }
            // サーバーのステータスチェック計測のリセット
            checker.refreshCount();
        }
        checker.tick();
    }

    // 後処理
    client->close();
    delete client;

    // 成功時
    return (wxThread::ExitCode) 0;
}

//////////////////////////////////////////////////////////////////////

// Streamの内容からイベントを作成する
CSCMessageData CSCGetStreamTask::parseStream(const string& json)
{
    // JSONのパース
    CSCJsonParser parser;
    CStreamData stream = parser.getStreamData(json);
    CSCMessageData message;
    // ストリームの種類により分岐
    switch (stream.m_type) {
    case CStreamData::TYPE_UNKNOWN: // 解析不可
    case CStreamData::TYPE_NOSTREAM: // ストリーム未受信
    {
        message.m_type = CSCMessageType::UNKNOWN;
        break;
    }
    case CStreamData::TYPE_MESSAGE_ADD: // メッセージ投稿
    {
        message.m_type = CSCMessageType::MESSAGE;

        message.m_id = stream.m_message.m_id;
        message.m_username = stream.m_message.m_username;
        message.m_body = stream.m_message.m_body;
        message.m_channel = stream.m_message.m_channel;
        message.m_time = stream.m_message.m_time;
        message.m_tempNick = stream.m_message.m_tempNick;
        break;
    }
    case CStreamData::TYPE_CHANNEL_MEMBER_ADD: // チャンネルメンバー参加
    {
        message.m_type = CSCMessageType::JOIN;
        message.m_username = stream.m_member.m_name;
        message.m_channel = stream.m_channel.m_name;
        break;
    }
    case CStreamData::TYPE_CHANNEL_MEMBER_SUB: // チャンネルメンバー離脱
    {
        message.m_type = CSCMessageType::PART;
        message.m_username = stream.m_member.m_name;
        message.m_channel = stream.m_channel.m_name;
        break;
    }
    case CStreamData::TYPE_CHANNEL_UPDATE: // チャンネル情報更新
    {
        message.m_type = CSCMessageType::TOPIC;
        message.m_channelData = stream.m_channel;
        break;
    }
    case CStreamData::TYPE_USER_UPDATE: // ユーザ情報更新
    {
        message.m_type = CSCMessageType::NICK;
        message.m_member = stream.m_member;
        break;
    }
    }

    return message;
}

}
}
