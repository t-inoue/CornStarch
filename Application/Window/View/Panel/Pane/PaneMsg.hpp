#pragma once
#include "../../../../DataStruct/MessageData.hpp"
#include "../../../../DataStruct/MemberData.hpp"
#include <wx/wxprec.h>
#include <wx/wx.h>
#include <vector>
#include <map>

namespace CornStarch
{;

// メッセージ表示用ペイン
class CPaneMsg : public wxTextCtrl
{
public:
    CPaneMsg(void);
    ~CPaneMsg(void);

    // 初期化を行う
    void init(wxWindow* parent);
    bool containsOver4ByteText(const wxString& content) const;
    // メッセージを表示する
    void displayMessages(const std::vector<CMessageData*>& messages, 
        const std::map<wxString, wxString>& nickTable);
    void addMessage(const CMessageData* message,
            const std::map<wxString, wxString>& nickTable);
private:

    // ユーザ名に対応するニックネームを取得する
    wxString getNickName(const wxString& userName, 
        const std::map<wxString, wxString>& nickTable);

    // 必要に応じて日付変更線を描画
    void drawDateLine(const wxString& now, const wxString& next);
};

}
