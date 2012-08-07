#pragma once
#include "wx/treebase.h"

namespace CornStarch
{;

// チャンネルツリーペインで選択時に発生するイベント
class CChannelSelectEvent : public wxTreeEvent
{
private:
    wxString m_channelName; // 項目名
    wxString m_server; // サーバ名
    int m_serverId; // サーバID
    bool m_isServer; // サーバ名か否か

public:
    CChannelSelectEvent(void);
    ~CChannelSelectEvent(void);

    // 項目名をセット
    void setChannelName(const wxString& text);

    // サーバ名をセット
    void setServer(const wxString& server);

    // サーバIDをセット
    void setServerId(int server);

    // サーバ名か否かをセット
    void setServerOrNot(bool isServer);

    // 項目名を取得
    wxString getChannelName(void) const;

    // サーバ名を取得
    wxString getServer(void) const;

    // サーバIDを取得
    int getServerId(void) const;

    // サーバを選択したか否かを取得
    bool isServerSelected(void) const;
};

}
