#pragma once
#include "header.hpp"

// チャンネル名指定用ダイアログ
class CChannelDialog : public wxDialog
{
private:
    wxTextCtrl* m_channelText; // チャンネル名入力欄

public:
    CChannelDialog(void);
    ~CChannelDialog(void);

    // 初期化を行う
    void init(wxWindow* parent, const wxString& title);

    // チャンネル名を取得する
    wxString getChannelName(void) const;
};

