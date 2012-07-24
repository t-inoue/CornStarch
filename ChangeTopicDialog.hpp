#pragma once
#include "header.hpp"

// チャンネルトピック変更用ダイアログ
class CChangeTopicDialog : public wxDialog
{
private:
    wxTextCtrl* m_topicText; // 新トピック入力用ダイアログ

public:
    CChangeTopicDialog(void);
    ~CChangeTopicDialog(void);

    // 初期化を行う
    void init(wxWindow* parent, const wxString& title);

    // トピックを取得する
    wxString getTopic(void) const;
};

