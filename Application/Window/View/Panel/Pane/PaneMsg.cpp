﻿#include "PaneMsg.hpp"
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

using namespace std;

namespace CornStarch
{
;

const wxColour CPaneMsg::COLOR_LIGHT_YELLOW = wxColour(255, 255, 180);
CPaneMsg::CPaneMsg(void)
{
}

CPaneMsg::~CPaneMsg(void)
{
}

//////////////////////////////////////////////////////////////////////

// 初期化を行う
void CPaneMsg::init(wxWindow* parent)
{
    // 画面の初期化
    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize,
            wxTE_MULTILINE | wxTE_READONLY | wxVSCROLL | wxTE_RICH2/*|wxTE_DONTWRAP*/);

    // フォント設定
    this->SetFont(wxFont(10, wxDEFAULT, wxNORMAL, wxNORMAL));
}

bool CPaneMsg::containsOver4ByteText(const wxString& content) const
{
    string body = string(content.c_str());
    int checkIndex = 0;
    while (checkIndex < body.size()){
        int length = mblen(&(body[checkIndex]), MB_CUR_MAX);
        if (length >= 4){
            return true;
        }
        checkIndex += length;
    }
    return false;
}
void CPaneMsg::clearUnreadBackgroundColor()
{
    int index = this->GetLastPosition();
    this->SetStyle(0, index,
            wxTextAttr(wxNullColour, *wxWHITE));
}
void CPaneMsg::addMessage(const CMessageData* message,
        const map<wxString, wxString>& nickTable)
{
    int index = this->GetLastPosition();

    // 時刻
    wxString date = message->getTime("%H:%M");
    this->AppendText(date);
    this->SetStyle(index, index + date.length(), wxTextAttr(*wxRED));

    // 名前
    int nickIndex = index + date.size();
    wxString nick = getNickName(message->m_username, nickTable);
    nick = " (" + nick + "):";
    if (message->m_tempNick != ""){
        nick += " (" + message->m_tempNick + ") ";
    }
    this->AppendText(nick);
    this->SetStyle(nickIndex, nickIndex + nick.size(), wxTextAttr(*wxBLUE));

    //本文
    int bodyIndex = nickIndex += nick.size();
    wxString body = message->m_body;

    // 4byte文字を非表示にする。
    if (containsOver4ByteText(body) == false){
        this->AppendText(body);
        this->SetStyle(bodyIndex, bodyIndex + body.Length(),
                wxTextAttr(*wxBLACK));
        // 未読の背景色設定
        if (message->m_isReaded == false){
            this->SetStyle(index, bodyIndex + body.Length(),
                    wxTextAttr(wxNullColour, COLOR_LIGHT_YELLOW));
        }
    }
    this->AppendText(" \n");
}
// メッセージを表示する
void CPaneMsg::displayMessages(const vector<CMessageData*>& messages,
        const map<wxString, wxString>& nickTable)
{
    this->Clear();
    int size = (int) messages.size();
    for (int i = 0; i < size; i++){
        addMessage(messages[i], nickTable);
        if (i < size - 1){
            drawDateLine(messages[i]->getTime("%Y/%m/%d(%a)"),
                    messages[i + 1]->getTime("%Y/%m/%d(%a)"));
        }
    }
}

//////////////////////////////////////////////////////////////////////

// ユーザ名に対応するニックネームを取得する
wxString CPaneMsg::getNickName(const wxString& userName,
        const map<wxString, wxString>& nickTable)
{
    // テーブルに存在しない時、本名を返す
    if (nickTable.find(userName) == nickTable.end()){
        return userName;
    }

    // ニックネームを返す
    return nickTable.find(userName)->second;
}

// 必要に応じて日付変更線を描画
void CPaneMsg::drawDateLine(const wxString& now, const wxString& next)
{
    if (now == next){
        return;
    }

    AppendText("\n------" + next + "--------\n\n");
}

}
