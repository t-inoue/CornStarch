#pragma once
#include <wx/wxprec.h>
#include <wx/wx.h>
#include <wx/spinctrl.h>
#include <wx/stattext.h>
#include <wx/choice.h>
#include <wx/checkbox.h>
#include "../../Service/ChatServiceBase.hpp"

namespace CornStarch
{;

// ユーザ名登録用ダイアログ
class CAuthDialog : public wxDialog
{
    bool validateRegisterDialogResult() const;
protected:

    wxStaticText* m_staticText1;
    wxTextCtrl* m_textCtrlName;
    wxStaticText* m_staticText2;
    wxChoice* m_choiceType;
    wxStaticText* m_staticText3;
    wxTextCtrl* m_textCtrlHost;
    wxStaticText* m_staticText4;
    wxSpinCtrl* m_spinCtrlPort;
    wxStaticText* m_staticText5;
    wxTextCtrl* m_textCtrlUserName;
    wxStaticText* m_staticTextPassword;
    wxTextCtrl* m_textCtrlPassword;
    wxStaticText* m_staticText7;
    wxCheckBox* m_checkBoxType;

public:
    CAuthDialog(void);
    virtual ~CAuthDialog(void);

    // 初期化を行う
    void init(wxWindow* parent, const wxString& title);

    // ユーザ名を取得する
    wxString getName(void) const;

    // パスワードを取得する
    wxString getPass(void) const;

    // ホスト名を取得する
    wxString getHostName(void) const;

    // ポートを取得する。
    int getPort(void) const;

    // 名前を取得する
    wxString getServiceName(void) const;

    // すぐに接続するかの
    bool isStartSoon(void) const;

    // サービス名の取得
    wxString getServiceTypeName(void) const;

    CChatServiceBase* getNewService(void) const;
};

}
