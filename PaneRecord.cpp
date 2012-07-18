#include "PaneRecord.hpp"

using namespace std;

const wxColour CPaneRecord::COLOR_BLACK = wxColour(0, 0, 0);
const wxColour CPaneRecord::COLOR_BLUE = wxColour(0, 0, 200);
const wxColour CPaneRecord::COLOR_GREEN = wxColour(0, 50, 0);
const wxColour CPaneRecord::COLOR_RED = wxColour(255, 0, 0);

CPaneRecord::CPaneRecord(void)
{
}


CPaneRecord::~CPaneRecord(void)
{
}


//////////////////////////////////////////////////////////////////////


// 初期化を行う
void CPaneRecord::init(wxWindow* parent)
{
    // テキスト領域の作成
    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, 
        wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY|wxVSCROLL|wxTE_RICH2 | wxTE_CHARWRAP);

    // フォントの設定(個人的にこれが好き)
    this->SetFont(wxFont(10, wxDEFAULT, wxNORMAL, wxNORMAL));
    this->SetBackgroundColour(wxColour(200, 200, 200));
}

// ログ一覧を表示
void CPaneRecord::displayLogs(const vector<CChatLog*>& logs)
{
    Clear();

    size_t size = logs.size();
    for (size_t i = 0; i < size; i++){
        switch (logs[i]->getLogType()){
        case CChatLog::LOG_MESSAGE:
            pushLog(*(CMessageLog*)logs[i]);
            break;
        case CChatLog::LOG_JOIN:
            pushLog(*(CJoinLog*)logs[i]);
            break;
        case CChatLog::LOG_PART:
            pushLog(*(CPartLog*)logs[i]);
            break;
        case CChatLog::LOG_TOPIC:
            pushLog(*(CTopicLog*)logs[i]);
            break;
        case CChatLog::LOG_USER:
            pushLog(*(CMemberLog*)logs[i]);
            break;
        }
    }
}


//////////////////////////////////////////////////////////////////////


// 単色で文字列を追加する
void CPaneRecord::pushStringRow(const wxString& str, const wxColour& colour)
{
    // 文字色変更位置
    int first = (int)this->GetValue().size();
    int second = first + (int)str.size();

    // 文字列の挿入
    this->AppendText(str);

    // 文字列の色を変更する
    this->SetStyle(first, second, wxTextAttr(colour));
}

// メッセージログを表示
void CPaneRecord::pushLog(const CMessageLog& messageLog)
{
    // 文字コード変換
    CMessageData message = messageLog.getLog();
    wxString n = messageLog.getNickName();
    wxString p = message.m_body;
    wxString c = message.m_channel;
    wxString t = message.getTime("%H:%M");

    // temporary_nickがあれば、本文の先頭に表示
    wxString nick= message.m_tempNick;
    if (nick != ""){
        p = "(" + nick + ") " + p;
    }

    pushStringRow(t + " ", COLOR_RED); // 時間を赤で表示
    pushStringRow("<" + c + "> (" + n + ") : ", COLOR_BLUE); // 名前を青で表示
    pushStringRow(p + "\n", COLOR_BLACK); // 本文を黒で表示
}

// チャンネル参加ログを表示
void CPaneRecord::pushLog(const CJoinLog& joinLog)
{
    pushStringRow(joinLog.getNickName() + "が" + joinLog.getLog().m_channel + "に参加しました\n", COLOR_GREEN);
}

// チャンネル離脱ログを表示
void CPaneRecord::pushLog(const CPartLog& partLog)
{
    pushStringRow(partLog.getNickName() + "が" + partLog.getLog().m_channel + "から離脱しました\n", COLOR_GREEN);
}

// メンバー情報更新ログを表示
void CPaneRecord::pushLog(const CMemberLog& memberLog)
{
    CMemberData member = memberLog.getLog();
    pushStringRow(member.m_name + "がニックネームを" + member.m_nick + "に変更しました\n", COLOR_GREEN);
}

// トピック変更ログを表示
void CPaneRecord::pushLog(const CTopicLog& topicLog)
{
    CChannelData channel = topicLog.getLog();
    pushStringRow(channel.m_name + "のトピックが" + channel.m_topic + "に変更されました\n", COLOR_GREEN);
}
