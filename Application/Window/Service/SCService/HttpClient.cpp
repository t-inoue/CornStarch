#include "HttpClient.hpp"

using namespace std;

namespace CornStarch
{;
namespace StarChat
{;

const wxString CHttpClient::HTTP_VER = "HTTP/1.1";
const wxString CHttpClient::HTTP_PORT = "80";


CHttpClient::CHttpClient(void)
{
}


CHttpClient::~CHttpClient(void)
{
}


///////////////////////////////////////////////////////////////////////////


// 初期化を行う
void CHttpClient::init(void)
{
    CSocketClient::init();

    setPort(HTTP_PORT); // 80番ポート
}

// HTTPレスポンスを受信して、Bodyを返す
string CHttpClient::recvHttpResponseBody(void)
{
    int length = 0;
    m_buffer = "";

    while(!isCorrectHttpResponse()){
        length += receive();
    }

    return getResponceBody(m_buffer);
}


///////////////////////////////////////////////////////////////////////////


// HTTPリクエストメソッドの行を送信する
void CHttpClient::sendRequestMethod(const wxString& method, const wxString& uri)
{
    send(method + " " + uri + " " + HTTP_VER);
}

// HTTPレスポンスのbody部を取得する
string CHttpClient::getResponceBody(const string& str) const
{
    int num = str.find("\r\n\r\n") + 4;

    if(num >= (int)str.size()){
        return "";
    }

    return str.substr(num);
}

// POST時のデフォルトリクエストヘッダ
void CHttpClient::sendPostDefault(const wxString& str, const wxString& basic)
{    
    wxString msg = urlEncode(str);
    string s(msg.mb_str(wxConvUTF8));
    sendCommonHeader((int)s.size(), basic);
    send("");
    send("body=" + msg);
    sendLF();
}

// GET時のデフォルトリクエストヘッダ
void CHttpClient::sendGetDefault(const wxString& basic)
{
    sendCommonHeader(0, basic);
    sendLF();
}

// PUT時のデフォルトリクエストヘッダ
void CHttpClient::sendPutDefault(const wxString& basic)
{
    sendCommonHeader(0, basic);
    send("Content-Length: 0");
    sendLF();
}

// DELETE時のデフォルトリクエストヘッダ
void CHttpClient::sendDeleteDefault(const wxString& basic)
{
    sendCommonHeader(0, basic);
    sendLF();
}

// stream時のデフォルトリクエストヘッダ
void CHttpClient::sendStreamDefault(const wxString& basic)
{
    sendCommonHeader(0, basic);
    sendKeepAlive();
    sendLF();
}

// PUT時にキー名をvalueを指定するときのリクエストヘッダ
void CHttpClient::sendPutParticular(const wxString& key, const wxString& value, 
    const wxString& basic)
{
    wxString aKey = urlEncode(key);
    wxString aValue = urlEncode(value);

    string strValue = (string)aValue.mb_str(wxConvUTF8);
    string strKey = (string)aKey.mb_str(wxConvUTF8);

    sendCommonHeader(strKey.size() + strValue.size() - 4, basic);
    send("Content-Type: application/x-www-form-urlencoded; charset=UTF-8");
    send("");
    send(aKey + "=" + aValue);
    sendLF();
}

// レスポンスがHTTPレスポンスとして完結しているかを判断する
bool CHttpClient::isCorrectHttpResponse(void) const
{
    int pos;
    int length;

    // Content-Lengthが存在するとき、bodyの文字数をチェック
    if ((pos = m_buffer.find("Content-Length: ")) != wxString::npos){

        string str = m_buffer.substr(pos + 16);
        if ((pos = str.find("\r\n")) != wxString::npos){

            stringstream ss;
            ss << str.substr(0, pos);
            ss >> length;

            // 文字数が一致していたら
            size_t size = getResponceBody(m_buffer).size();
            if (length == size){
                return true;
            }
        }
    } else if (m_buffer.find("\r\n\r\n") + 4 == m_buffer.size()){

        // メッセージの終了が\r\n\r\nだったら
        return true;
    }

    return false;
}


///////////////////////////////////////////////////////////////////////////


// 共通部分となるHTTPヘッダを送る
void CHttpClient::sendCommonHeader(int length, const wxString& basic)
{
    sendHost(); // ホスト名
    sendAuth(basic); // basic認証
    sendLength(length); // データ長
    sendAccept(); // Accept形式
}


///////////////////////////////////////////////////////////////////////////


// Hostを送る
void CHttpClient::sendHost(void)
{
    send("Host: " + m_host);
}

// Basic認証を行う行を送る
void CHttpClient::sendAuth(const wxString& basic)
{
    send("Authorization: Basic " + basic);
}

// Acceptを送る
void CHttpClient::sendAccept(void)
{
    send("Accept: application/json, text/javascript, */*; q=0.01");
}

// Content-Lengthを送る
void CHttpClient::sendLength(int length)
{
    // 長さ0の時
    if (length == 0){
        return;
    }

    // intに変換
    ostringstream stream;
    stream << (length + 5);

    send("Content-Length: " + stream.str());
}

// Keep-Alive
void CHttpClient::sendKeepAlive(void)
{
    send("Connection: keep-alive");
}

// bodyを送る
void CHttpClient::sendBody(const wxString& body)
{
    send("body=" + body);
}

// URLエンコードを行う
wxString CHttpClient::urlEncode(const wxString& text)
{
    // http://tools.ietf.org/html/rfc3986#section-2.4

    string str = (string)text.mb_str(wxConvUTF8);
    string result = "";

    string::const_iterator it;
    for (it = str.begin(); it != str.end(); it++){

        if ((*it) == '%'){
            // %のとき
            result += "%25";

        } else if ((*it) == ' '){
            // 半角空白の時
            result += '+';

        } else if (isReservedDelim(*it)){
            // 予約語の時
            char value[4];
            sprintf(value, "%%%X", (unsigned char)*it);
            result += value;

        } else {
            // それ以外
            result += *it;
        }
    }
    return wxString(result.c_str(), wxConvUTF8);
}

// 予約文字か判断する
bool CHttpClient::isReservedDelim(char c)
{
    // gen-delims  = ":" / "/" / "?" / "#" / "[" / "]" / "@"
    // sub-delims  = "!" / "$" / "&" / "'" / "(" / ")"
    // / "*" / "+" / "," / ";" / "="

    if (c == ':' || c == '/' || c == '?' || c == '#' || c == '[' || 
        c == ']' || c == '@' || c == '!' || c == '$' || c == '&' || 
        c == '\'' || c == '(' || c == ')' || c == '*' || c == '+' || 
        c == ',' || c == ';' || c == '='){
            return true;
    }

    return false;
}


}
}
