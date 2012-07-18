#include "SCJsonParser.hpp"

using namespace std;
using namespace picojson;

CSCJsonParser::CSCJsonParser(void)
{
}


CSCJsonParser::~CSCJsonParser(void)
{
}


//////////////////////////////////////////////////////////////////////


// メンバの一覧をvectorとして返す
vector<CMemberData*> CSCJsonParser::getMembers(const string& json) const
{
    vector<CMemberData*> result;

    // jsonを解析したarrayを取得
    array arr = getArray(parseSCJson(json));

    // 各メンバについてループ
    int size = (int)arr.size();
    for (int i = 0; i < size; i++){

        // パラメータの取得
        CMemberData* mem = new CMemberData();
        mem->m_name = wxString(arr[i].get("name").get<string>().c_str(), wxConvUTF8); // 名前(name)
        mem->m_nick = wxString(arr[i].get("nick").get<string>().c_str(), wxConvUTF8); // ニックネーム(name)

        // vectorに追加
        result.push_back(mem);
    }

    return result;
}

// チャンネル一覧をvectorとして返す
vector<CChannelData*> CSCJsonParser::getChannels(const string& json) const
{
    vector<CChannelData*> result;

    // jsonを解析したarrayを取得
    array arr = getArray(parseSCJson(json));

    // 各チャンネルについてループ
    int size = (int)arr.size();
    for (int i = 0; i < size; i++){

        // パラメータの取得
        CChannelData* cn = new CChannelData();
        cn->m_name = wxString(arr[i].get("name").get<string>().c_str(), wxConvUTF8); // チャンネル名(name)
        if (arr[i].get("topic")){ // topic(あれば)
            cn->m_topic = wxString(arr[i].get("topic").get("body").get<string>().c_str(), wxConvUTF8);
        } else {
            cn->m_topic = "";
        }

        // vectorに追加
        result.push_back(cn);
    }

    return result;
}

// メッセージ一覧をvectorとして返す
vector<CMessageData*> CSCJsonParser::getMessages(const string& json) const
{
    vector<CMessageData*> result;

    // jsonを解析したarrayを取得
    array arr = getArray(parseSCJson(json));

    // 各メッセージについてループ
    int size = (int)arr.size();
    for (int i = 0; i < size; i++){

        // パラメータの取得
        CMessageData* msg = new CMessageData();
        msg->m_id = arr[i].get("id").get<double>(); // メッセージID
        msg->m_username = wxString(arr[i].get("user_name").get<string>().c_str(), wxConvUTF8); // 発言者
        msg->m_body = wxString(arr[i].get("body").get<string>().c_str(), wxConvUTF8); // 本文
        msg->m_channel = wxString(arr[i].get("channel_name").get<string>().c_str(), wxConvUTF8); // 投稿チャンネル
        msg->m_time = (time_t)arr[i].get("created_at").get<double>(); // 作成UNIX時
        if (arr[i].get("temporary_nick")){ // テンポラリニックネーム(あれば)
            msg->m_tempNick = wxString(arr[i].get("temporary_nick").get<string>().c_str(), wxConvUTF8);
        }

        // vectorに追加
        result.push_back(msg);
    }

    return result;
}

// メンバ情報を返す
CMemberData CSCJsonParser::getMember(const string& json) const
{
    // jsonの解析
    value v = parseSCJson(json);

    CMemberData member;

    // パラメータの取得
    member.m_name = wxString(v.get("name").get<string>().c_str(), wxConvUTF8); // 名前
    member.m_nick = wxString(v.get("nick").get<string>().c_str(), wxConvUTF8); // ニックネーム

    if (v.get("keywords")){
        array arr = v.get("keywords").get<array>();
        size_t size = arr.size();
        for (size_t i = 0; i < size; i++){
            member.m_keywords.push_back(wxString(arr[i].get<string>().c_str(), wxConvUTF8)); // キーワード
        }
    }

    return member;
}

// ストリームを返す
CStreamData CSCJsonParser::getStreamData(const string& json) const
{
    CStreamData result;
    value u;

    // 文字列が空の場合
    if (json == ""){
        // ストリームはないと判断する
        result.m_type = CStreamData::TYPE_NOSTREAM;
        return result;
    }

    // ストリームの種類を取得
    value v = parseSCJson(json);
    CStreamData::TYPE type = getStreamType(v);

    // ストリームの種類により分岐
    switch (type){
    case CStreamData::TYPE_MESSAGE_ADD: // メッセージの投稿があった

        // メッセージの取得
        u = v.get("message");

        // 値を取得する
        result.m_type = CStreamData::TYPE_MESSAGE_ADD;
        result.m_message.m_id = u.get("id").get<double>();
        result.m_message.m_username = wxString(u.get("user_name").get<string>().c_str(), wxConvUTF8);
        result.m_message.m_body = wxString(u.get("body").get<string>().c_str(), wxConvUTF8);
        result.m_message.m_channel = wxString(u.get("channel_name").get<string>().c_str(), wxConvUTF8);
        result.m_message.m_time = (time_t)u.get("created_at").get<double>();
        if (u.get("temporary_nick")){ // テンポラリニックネーム(あれば)
            result.m_message.m_tempNick = wxString(u.get("temporary_nick").get<string>().c_str(), wxConvUTF8);
        }
        break;

    case CStreamData::TYPE_CHANNEL_MEMBER_ADD: // チャンネルにメンバー追加

        result.m_type = CStreamData::TYPE_CHANNEL_MEMBER_ADD;
        result.m_member.m_name = wxString(v.get("user_name").get<string>().c_str(), wxConvUTF8);
        result.m_channel.m_name = wxString(v.get("channel_name").get<string>().c_str(), wxConvUTF8);
        break;

    case CStreamData::TYPE_CHANNEL_MEMBER_SUB: // チャンネルからメンバー離脱

        result.m_type = CStreamData::TYPE_CHANNEL_MEMBER_SUB;
        result.m_member.m_name = wxString(v.get("user_name").get<string>().c_str(), wxConvUTF8);
        result.m_channel.m_name = wxString(v.get("channel_name").get<string>().c_str(), wxConvUTF8);
        break;

    case CStreamData::TYPE_CHANNEL_UPDATE: // チャンネル情報更新

        u = v.get("channel");

        result.m_type = CStreamData::TYPE_CHANNEL_UPDATE;
        result.m_channel.m_name = wxString(u.get("name").get<string>().c_str(), wxConvUTF8);
        result.m_channel.m_topic = wxString(u.get("topic").get("body").get<string>().c_str(), wxConvUTF8);
        break;

    case CStreamData::TYPE_USER_UPDATE: // ユーザ情報更新

        u =  v.get("user");

        result.m_type = CStreamData::TYPE_USER_UPDATE;
        result.m_member.m_name = wxString(u.get("name").get<string>().c_str(), wxConvUTF8);
        result.m_member.m_nick = wxString(u.get("nick").get<string>().c_str(), wxConvUTF8);
        break;

    default: // 解析不能
        result.m_type = CStreamData::TYPE_UNKNOWN;
        break;
    }

    return result;

}

// pingが成功したか否かを返す
bool CSCJsonParser::isPingSucceeded(const string& body) const
{
    // pongが見つからなければ
    if (body.find("pong") == string::npos){
        return false;
    }
    return true;
}

// 複数行のJSONを、vector形式に変換する
vector<string> CSCJsonParser::getJsonVec(const string& jsons)
{
    vector<string> result;
    string buffer = jsons;

    // 空文字列のとき
    if (jsons == ""){
        return result;
    }

    while(1){

        // これ以上JSON部分がない
        if (buffer.find("\r\n") == 0){
            break;
        }

        // JSON部分をresultにセット
        int pos = buffer.find("\n");
        result.push_back(buffer.substr(0, pos));

        // bufferを更新
        buffer = buffer.substr(pos + 1);
    }
    return result;
}


//////////////////////////////////////////////////////////////////////


// ストリームのvalueから、ストリームタイプを得る
CStreamData::TYPE CSCJsonParser::getStreamType(const value& val) const
{
    // 形式が不正
    if (!val.is<object>()){
        return CStreamData::TYPE_UNKNOWN;
    }

    // タイプを文字列で取得
    wxString str = val.get("type").get<string>();
    if (str == "message"){ // メッセージが投稿
        return CStreamData::TYPE_MESSAGE_ADD;
    } else if (str == "delete_subscribing"){ // チャンネルにメンバー参加
        return CStreamData::TYPE_CHANNEL_MEMBER_SUB;
    } else if (str == "subscribing"){ // チャンネルからメンバー離脱
        return CStreamData::TYPE_CHANNEL_MEMBER_ADD;
    } else if (str == "channel"){ // チャンネル情報更新
        return CStreamData::TYPE_CHANNEL_UPDATE;
    } else if (str == "user"){ // ユーザ情報変更
        return CStreamData::TYPE_USER_UPDATE;
    }

    // 解析できなかった
    return CStreamData::TYPE_UNKNOWN;
}

// valueを解析してarrayとして返す
array CSCJsonParser::getArray(const value& val) const
{
    // array形式であれば
    if (val.is<array>()){

        // arrayを返す
        return val.get<array>();
    }

    // 空のarrayを返す
    return array();
}

// jsonを解析してvalueとして返す
value CSCJsonParser::parseSCJson(const string& json) const
{
    // 文字列の解析
    value v;
    const char* str = json.c_str();
    picojson::parse(v, str, str + strlen(str));

    // 解析結果
    return v;
}