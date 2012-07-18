#pragma once
#include "header.hpp"
#include <wx/splitter.h>

// アプリケーション用の画面分割クラス
class CSplitPanel : public wxSplitterWindow
{
private:
    // ウィンドウのID
    enum SPLIT_WINDOW_ID{
        LEFT_WINDOW_ID = 10000,
        MSG_WINDOW_ID,
        RIGHT_WINDOW_ID,
    };

protected:

    wxSplitterWindow* m_spHorL; // 左画面を一覧とm_spMsgに分割
    wxSplitterWindow* m_spMsg; // メッセージ表示とメッセージ投稿画面に分割
    wxSplitterWindow* m_spHorR; // 右画面を上下に分割

    // wxWindowイベントを処理させたいクラスに利用するマクロ
    DECLARE_EVENT_TABLE()

public:
    CSplitPanel(void);
    virtual ~CSplitPanel(void);

    // 初期化を行う
    void init(wxWindow* parent);

    // sashの位置を更新する
    void updateSashPos(const wxSize& size);

protected:

    // 分割を行う際のパラメータを設定する
    void setSplitParam(void);

    // メッセージ表示パネルを取得する
    wxSplitterWindow* getMsgPane(void);

    // メンバー表示パネルを取得する
    wxSplitterWindow* getMemPane(void);

    // チャンネル表示パネルを取得する
    wxSplitterWindow* getCnPane(void);

    // メッセージ投稿パネルを取得する
    wxSplitterWindow* getPostPane(void);

    // 一覧表示パネルを取得する
    wxSplitterWindow* getRecordPane(void);

private:

    // 左のsash位置が変更された
    void onLeftSashPosChanged(wxSplitterEvent& event);
    
};

