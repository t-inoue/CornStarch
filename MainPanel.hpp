#pragma once
#include "SplitPanel.hpp"
#include "PaneMsg.hpp"
#include "PanePost.hpp"
#include "PaneRecord.hpp"
#include "PaneCn.hpp"
#include "PaneMember.hpp"
#include <wx/sizer.h>

class CMainPanel : public CSplitPanel
{
private:

    CPaneMsg* m_msgPane; // メッセージ表示
    CPanePost* m_postPane; // メッセージ投稿
    CPaneRecord* m_recordPane; // メッセージ一覧表示
    CPaneCn* m_cnBox; // チャンネル表示用リストボックス
    CPaneMember* m_memBox; // メンバ表示用リストボックス

public:
    CMainPanel(void);
    ~CMainPanel(void);

    // 初期化を行う
    void init(wxWindow* parent);

    // メッセージペインにメッセージを表示
    void displayMessages(const std::vector<CMessageData*>& messages,
        const std::map<wxString, wxString>& nickTable);

    // メンバーペインにメンバーを表示
    void displayMembers(const std::vector<CMemberData*>& members);

    // チャンネルペインにチャンネルを表示
    void displayChannels(const std::vector<wxString>& channels);

    // ログ一覧ペインにログを表示
    void displayLogs(const std::vector<CChatLog*>& logs);

public:
    // 投稿ペインの文字列をクリアする
    void clearPostPaneText(void);

    // 選択済みチャンネルを決める
    void setSelectedChannel(const wxString& channel);

    // 投稿ペインのIDを取得する
    wxWindowID getPostPaneID(void) const;

    // チャンネルペインのIDを取得する
    wxWindowID getCnPaneID(void) const;

    // チャンネルペインで選ばれている項目の名前を返す
    wxString getSelectedChannel(void) const;

private:

    // 画面分割を行う
    void split(void);


};

