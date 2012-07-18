#include "SCClient.hpp"

using namespace std;

CSCClient::CSCClient(void)
{
}


CSCClient::~CSCClient(void)
{
}


///////////////////////////////////////////////////////////////////////////


// pingを送るリクエストを投げる
void CSCClient::sendPingRequest(const wxString& userName, const wxString& basic)
{
    // APIを叩く
    sendPingApi(userName);
    sendGetDefault(basic);
}

// メッセージを投稿するリクエストを投げる
void CSCClient::postMessageRequest(const wxString& body, const wxString& channel,
    const wxString& basic)
{
    // APIを叩く
    sendPostMstApi(channel);
    sendPostDefault(body, basic);
}

// その人のチャンネルをJSON形式で取得するリクエストを投げる
void CSCClient::sendGetChannelsRequest(const wxString& userName,
    const wxString& basic)
{
    // APIを叩く
    sendGetCnApi(userName);
    sendGetDefault(basic);
}

// チャンネルのメッセージをJSON形式で取得するリクエストを投げる
void CSCClient::sendGetMessagesRequest(const wxString& channel,
    const wxString& basic)
{
    // APIを叩く
    sendGetMsgApi(channel);
    sendGetDefault(basic);
}

// チャンネルのメンバーをJSON形式で取得するリクエストを投げる
void CSCClient::sendGetMembersRequest(const wxString& channel,
    const wxString& basic)
{
    // APIを叩く
    sendGetMemApi(channel);
    sendGetDefault(basic);
}

// チャンネルに参加するリクエストを投げる
void CSCClient::sendJoinRequest(const wxString& channel, const wxString& userName,
    const wxString& basic)
{
    // APIを叩く
    sendJoinApi(channel, userName);
    sendPutDefault(basic);
}

// チャンネルから抜けるリクエストを投げる
void CSCClient::sendPartRequest( const wxString& channel, const wxString& userName,
    const wxString& basic)
{
    sendPartApi(channel, userName);
    sendPutDefault(basic);
}

// メンバーの情報をJSON形式で取得するリクエストを投げる
void CSCClient::sendGetMemInfoRequest(const wxString& userName, const wxString& basic)
{
    sendGetMemInfoApi(userName);
    sendGetDefault(basic);
}

// ストリームを取得するリクエストを送る
void CSCClient::sendGetStreamRequest(const wxString& userName, const wxString& basic)
{
    sendStreamApi(userName);
    sendGetDefault(basic);
}

// ストリームをJSON形式で取得する
string CSCClient::getStreamJson(void)
{
    // 受信する
    int length = recvStream();

    // ストリームが来ていない場合
    if (length == 0){

        // 空文字列を返す
        return "";
    }

    // 文字数の列を破棄するため、改行コードを探す
    int num = m_buffer.find("\r\n");
    return m_buffer.substr(num + 2); // 2は改行コードの文字長
}


///////////////////////////////////////////////////////////////////////////


// ストリームを受信する
int CSCClient::recvStream(long waitTimeUsec)
{
    int length = 0;
    m_buffer = "";

    // 正しい形式となるまで受信し続ける
    while(1){

        // 受信
        length += receive(waitTimeUsec);

        // 受信していない時は0を返す
        if (length == 0){
            return length;
        }

        // "\n"の受信時("1\r\n\n\r\n"という文字列が来る)
        if (length == 6 && m_buffer == ("1\r\n\n\r\n")){
            return 0;
        }

        // 受信途中(完全な形式のストリームでない)ならば
        int pos = m_buffer.rfind("\r\n") + 2;
        if (pos != m_buffer.size()){

            // 受信を続ける
            continue;
        } else {

            // 受信終了
            break;
        }
    }

    return length;
}

// ストリーム形式が正規のものか確認する
bool CSCClient::isCorrectStream(void) const
{
    int pos;
    int length;

    // 改行コードがあれば
    if ((pos = m_buffer.find("\r\n")) != wxString::npos){

        // 文字長を取得
        stringstream ss;
        ss << m_buffer.substr(0, pos);
        ss >> length;

        // 文字長と実際に受信した文字列の長さが一致すれば
        if (length == m_buffer.substr(pos + 4).size()){
            return true;
        }
    }
    return false;
}


///////////////////////////////////////////////////////////////////////////


// pingを送るAPIを叩く(GET /users/user_name/ping)
void CSCClient::sendPingApi(const wxString& userName)
{
    sendRequestMethod("GET", "/users/" + userName + "/ping");
}

// メッセージ投稿するAPIを叩く(POST /channels/channel_name/messages)
void CSCClient::sendPostMstApi(const wxString& channel)
{
    sendRequestMethod("POST", "/channels/" + channel + "/messages");
}

// チャンネル一覧取得のAPIを叩く(GET /users/user_name/channels)
void CSCClient::sendGetCnApi(const wxString& userName)
{
    sendRequestMethod("GET", "/users/" + userName + "/channels");
}

// メンバー一覧取得のAPIを叩く(GET /channels/channel_name/users)
void CSCClient::sendGetMemApi(const wxString& channel)
{
    sendRequestMethod("GET", "/channels/" + channel + "/users");
}

// メッセージ一覧取得(最大100件)のAPIを叩く(GET /channels/channel_name/messages/recent)
void CSCClient::sendGetMsgApi(const wxString& channel)
{
    sendRequestMethod("GET", "/channels/" + channel + "/messages/recent");
}

// チャンネル参加APIを叩く//(PUT /subscribings?user_name=user_name;channel_name=channel_name)
void CSCClient::sendJoinApi(const wxString& channel, const wxString& userName)
{
    sendRequestMethod("PUT", "/subscribings?channel_name=" + channel
        + ";user_name=" + userName);
}

// チャンネル離脱APIを叩く(DELETE /subscribings?user_name=user_name;channel_name=channel_name)
void CSCClient::sendPartApi(const wxString& channel, const wxString& userName)
{
    sendRequestMethod("DELETE", "/subscribings?channel_name=" + channel
        + ";user_name=" + userName);
}

// メンバー情報取得APIを叩く
void CSCClient::sendGetMemInfoApi(const wxString& userName)
{
    sendRequestMethod("GET", "/users/" + userName);
}

// ストリーム取得用APIを叩く(GET /users/user_name/stream(?start_message_id=start_message_id))
void CSCClient::sendStreamApi(const wxString& userName)
{
    sendRequestMethod("GET", "/users/" + userName + "/stream");
}
