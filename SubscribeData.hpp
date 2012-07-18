#pragma once
#include <wx/string.h>
#include <vector>

// チャンネル入退出の内容を表すクラス
class CSubscribeData
{
public:
    wxString m_channel; // チャンネル名
    wxString m_username; // ユーザ名

    CSubscribeData(wxString channel, wxString username)
        : m_channel(channel), m_username(username){}
    CSubscribeData(){}
};

