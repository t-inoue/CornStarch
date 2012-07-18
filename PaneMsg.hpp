#pragma once
#include "MessageData.hpp"
#include "MemberData.hpp"
#include "header.hpp"
#include <vector>
#include <map>

// メッセージ表示用ペイン
class CPaneMsg : public wxTextCtrl
{
public:
    CPaneMsg(void);
    ~CPaneMsg(void);

    // 初期化を行う
    void init(wxWindow* parent);

    // メッセージを表示する
    void displayMessages(const std::vector<CMessageData*>& messages, 
        const std::map<wxString, wxString>& nickTable);

private:

    // ユーザ名に対応するニックネームを取得する
    wxString getNickName(const wxString& userName, 
        const std::map<wxString, wxString>& nickTable);

};

