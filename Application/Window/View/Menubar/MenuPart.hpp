#pragma once
#include <wx/wxprec.h>
#include <wx/wx.h>

namespace CornStarch
{;

class CMenuPart : public wxMenu
{
public:
    // メニュー番号
    enum MENU{
        MENU_FILE_QUIT = 100,
        MENU_SERVER_ADD,
        MENU_SERVER_DELETE,
        MENU_SERVER_NICK_CHANGE,
        MENU_UPDATE,
        MENU_CHANNEL_JOIN,
        MENU_CHANNEL_PART,
        MENU_CHANNEL_TOPIC_CHANGE,
    };

protected:
    wxString m_title; // タイトル文字列

public:
    CMenuPart(void);
    virtual ~CMenuPart(void);

    // タイトルを取得する
    wxString getTitle(void);

protected:

    // メニュー項目に要素を追加する
    void append(int itemid, const wxString& text = wxEmptyString,
        const wxString& help = wxEmptyString, wxItemKind kind = wxITEM_NORMAL);

    // メニューバーにセパレータ
    void separate(void);

    // タイトルをセットする
    void setTitle(const wxString& title);

};

}
