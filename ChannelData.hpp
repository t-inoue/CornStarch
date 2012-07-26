#pragma once
#include <wx/string.h>

namespace CornStarch
{;

// チャンネルの情報を格納するクラス
class CChannelData
{
public:
    wxString m_name; // チャンネル名
    wxString m_topic; // トピック
};

}