#pragma once
#include "MessageLog.hpp"
#include "MemberLog.hpp"
#include "JoinLog.hpp"
#include "PartLog.hpp"
#include "TopicLog.hpp"
#include "header.hpp"
#include <vector>

// メッセージ一覧表示用ペイン
class CPaneRecord : public wxTextCtrl
{
public:
    static const int MAX_LENGTH = 200000; // 最大文字数

private:
    static const wxColour COLOR_BLACK;
    static const wxColour COLOR_GREEN;
    static const wxColour COLOR_RED;
    static const wxColour COLOR_BLUE;

public:
    CPaneRecord(void);
    ~CPaneRecord(void);

    // 初期化を行う
    void init(wxWindow* parent);

    // ログ一覧を表示
    void displayLogs(const std::vector<CChatLog*>& logs);

private:

    // 単色で文字列を追加する
    void pushStringRow(const wxString& str, const wxColour& colour);

    // メッセージログを表示
    void pushLog(const CMessageLog& messageLog);

    // チャンネル参加ログを表示
    void pushLog(const CJoinLog& joinLog);

    // チャンネル離脱ログを表示
    void pushLog(const CPartLog& partLog);

    // メンバー情報更新ログを表示
    void pushLog(const CMemberLog& memberLog);

    // トピック変更ログを表示
    void pushLog(const CTopicLog& topicLog);
};

