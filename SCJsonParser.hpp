#pragma once
// 'int' : ブール値を 'true' または 'false' に強制的に設定します (警告の処理)
// picojsonの上の警告文を消すためのpragma
#pragma warning(disable:4800)
#pragma warning(disable:4996)
#include "picojson.hpp"
#include "StreamData.hpp"
#include "vector"
#include "header.hpp"

// StarChatに使われるJsonのパースを行う
class CSCJsonParser
{
public:
    CSCJsonParser(void);
    ~CSCJsonParser(void);

    // メンバの一覧をvectorとして返す
    std::vector<CMemberData*> getMembers(const std::string& json) const;

    // チャンネル一覧をvectorとして返す
    std::vector<CChannelData*> getChannels(const std::string& json) const;

    // メッセージ一覧をvectorとして返す
    std::vector<CMessageData*> getMessages(const std::string& json) const;

    // メンバ情報を返す
    CMemberData getMember(const std::string& json) const;

    // ストリームを返す
    CStreamData getStreamData(const std::string& json) const;

    // pingが成功したか否かを返す
    bool isPingSucceeded(const std::string& json) const;

    // 複数行のJSONを、vector形式に変換する
    std::vector<std::string> getJsonVec(const std::string& jsons);

private:

    // ストリームのvalueから、ストリームタイプを得る
    CStreamData::TYPE getStreamType(const picojson::value& val) const;

    // valueを解析してarrayとして返す
    picojson::array getArray(const picojson::value& val) const;

    // jsonを解析してvalueとして返す
    picojson::value parseSCJson(const std::string& json) const;
};

