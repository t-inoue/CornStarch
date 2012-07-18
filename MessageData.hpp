#pragma once
#include <wx/string.h>
#include <time.h>

// 投稿メッセージの内容を表すクラス
class CMessageData
{
private:
    static const int MAX_LENGTH = 256; // 時間表示形式の最大文字数

public:

    int m_id; // メッセージID
    wxString m_username; // ユーザ名
    wxString m_body; // メッセージ本文
    time_t m_time; // UNIX時間
    wxString m_channel; // チャンネル名
    wxString m_tempNick; // 一時ニックネーム

    CMessageData(){}
    CMessageData(int id, const wxString& name, const wxString& body,
        const wxString& channel, const time_t& t)
        : m_id(id), m_username(name), m_channel(channel), m_time(t), m_body(body){}

    // 指定の形式で時刻を取得
    wxString getTime(const wxString& format) const
    {
        char buf[MAX_LENGTH];
        tm* timeStruct;

        // tm構造体形式に変換
        timeStruct = localtime(&m_time);

        // 表示形式を変換
        strftime(buf, sizeof(buf), format.c_str(), timeStruct);

        return wxString(buf);
    }
};

