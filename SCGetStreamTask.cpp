#include "SCGetStreamTask.hpp"

using namespace std;

CSCGetStreamTask::CSCGetStreamTask(void)
{
}


CSCGetStreamTask::~CSCGetStreamTask(void)
{
}


//////////////////////////////////////////////////////////////////////


// 初期化を行う
void CSCGetStreamTask::init(wxEvtHandler* handler, const wxString& userName,
        const wxString& basic)
{
    CSCTask::init(handler, basic);
    m_userName = userName;
}


//////////////////////////////////////////////////////////////////////


// メインループ
wxThread::ExitCode CSCGetStreamTask::Entry()
{
    // クライアントの初期化
    CSCClient* client = new CSCClient();
    client->init();

    client->connect();
    client->sendGetStreamRequest(m_userName, m_basic);
    client->recvHttpResponseBody();

    // Deleteされるまでループ
    while (!TestDestroy()){

        // ストリーム(JSON形式)を受信
        CSCJsonParser parser;
        string jsons = client->getStreamJson();
        vector<string> jsonVec = parser.getJsonVec(jsons);

        // 各JSONを解析して、イベントを送信する
        size_t size = jsonVec.size();
        for (size_t i = 0; i < size; i++){
            wxThreadEvent* event = parseStream(jsonVec[i]);

            // イベントを送信
            if (event != NULL){
                wxQueueEvent(m_handler, event);
            }
        }
    }

    // 後処理
    client->close();
    delete client;

    // 成功時
    return (wxThread::ExitCode)0;
}


//////////////////////////////////////////////////////////////////////


// Streamの内容からイベントを作成する
wxThreadEvent* CSCGetStreamTask::parseStream(const string& json)
{
    // JSONのパース
    CSCJsonParser parser;
    CStreamData stream = parser.getStreamData(json);

    // ストリームの種類により分岐
    switch (stream.m_type){
    case CStreamData::TYPE_UNKNOWN: // 解析不可
    case CStreamData::TYPE_NOSTREAM: // ストリーム未受信

        return NULL;

    case CStreamData::TYPE_MESSAGE_ADD: // メッセージ投稿
        {
            CMsgStreamEvent* event = new CMsgStreamEvent();
            event->SetEventType(myEVT_THREAD_STREAM_MSG_ADD);
            event->setMessage(stream.m_message);
            return event;
        }
    case CStreamData::TYPE_CHANNEL_MEMBER_ADD: // チャンネルメンバー参加
        {
            CJoinStreamEvent* event = new CJoinStreamEvent();
            event->SetEventType(myEVT_THREAD_STREAM_CH_JOIN);
            event->setChannelName(stream.m_channel.m_name);
            event->setUserName(stream.m_member.m_name);
            return event;
        }
    case CStreamData::TYPE_CHANNEL_MEMBER_SUB: // チャンネルメンバー離脱
        {
            CPartStreamEvent* event = new CPartStreamEvent();
            event->SetEventType(myEVT_THREAD_STREAM_CH_PART);
            event->setChannelName(stream.m_channel.m_name);
            event->setUserName(stream.m_member.m_name);
            return event;
        }
    case CStreamData::TYPE_CHANNEL_UPDATE: // チャンネル情報更新
        {
            CChannelStreamEvent* event = new CChannelStreamEvent();
            event->SetEventType(myEVT_THREAD_STREAM_CH_UPDATE);
            event->setChannel(stream.m_channel);
            return event;
        }
    case CStreamData::TYPE_USER_UPDATE: // ユーザ情報更新
        {
            CUserStreamEvent* event = new CUserStreamEvent();
            event->SetEventType(myEVT_THREAD_STREAM_USER_UPDATE);
            event->setMember(stream.m_member);
            return event;
        }
    }

    return NULL;
}
