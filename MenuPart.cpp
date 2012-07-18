#include "MenuPart.hpp"


CMenuPart::CMenuPart(void)
{
}


CMenuPart::~CMenuPart(void)
{
}


/////////////////////////////////


// タイトルを取得する
wxString CMenuPart::getTitle(void)
{
    return m_title;
}


/////////////////////////////////


// メニュー項目に要素を追加する
void CMenuPart::append(int itemid, const wxString& text, const wxString& help, wxItemKind kind)
{
    this->Append(itemid, text, help, kind);
}

// メニュー項目をセパレータで区切る
void CMenuPart::separate(void)
{
    this->AppendSeparator();
}

// タイトルをセットする
void CMenuPart::setTitle(const wxString& title)
{
    m_title = title.Clone();
}

