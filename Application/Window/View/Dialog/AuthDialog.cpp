#include "AuthDialog.hpp"
#include "../../Service/IRCService/IRCService.hpp"
#include "../../Service/SCService/SCService.hpp"

using namespace std;

namespace CornStarch
{
;

CAuthDialog::CAuthDialog(void)
{
}

CAuthDialog::~CAuthDialog(void)
{
}

//////////////////////////////////////////////////////////////////////

// 初期化を行う
void CAuthDialog::init(wxWindow* parent, const wxString& title)
{
    wxDialog::Create(parent, wxID_ANY, title);
    this->SetSize(400, 300);

    wxBoxSizer* bSizer9;
    bSizer9 = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* bSizer;
    bSizer = new wxBoxSizer(wxHORIZONTAL);

    m_staticText1 = new wxStaticText(this, wxID_ANY, wxT("名前:"),
            wxPoint(-1, -1), wxSize(100, -1), wxALIGN_RIGHT);
    m_staticText1->Wrap(-1);
    bSizer->Add(m_staticText1, 0, wxALIGN_CENTER, 5);

    m_textCtrlName = new wxTextCtrl(this, wxID_ANY, wxEmptyString,
            wxDefaultPosition, wxSize(150, -1), 0);
    bSizer->Add(m_textCtrlName, 0, wxALIGN_CENTER_VERTICAL, 5);

    bSizer9->Add(bSizer, 1, wxEXPAND, 5);

    wxBoxSizer* bSizer12;
    bSizer12 = new wxBoxSizer(wxHORIZONTAL);

    m_staticText2 = new wxStaticText(this, wxID_ANY, wxT("タイプ："),
            wxDefaultPosition, wxSize(100, -1), wxALIGN_RIGHT);
    m_staticText2->Wrap(-1);
    bSizer12->Add(m_staticText2, 0, wxALIGN_CENTER, 5);

    wxString m_choiceTypeChoices[] = { wxT("StarChat"), wxT("IRC") };
    int m_choiceTypeNChoices = sizeof(m_choiceTypeChoices) / sizeof(wxString);
    m_choiceType = new wxChoice(this, wxID_ANY, wxDefaultPosition,
            wxDefaultSize, m_choiceTypeNChoices, m_choiceTypeChoices, 0);
    m_choiceType->SetSelection(0);
    bSizer12->Add(m_choiceType, 0, wxALIGN_CENTER, 5);

    bSizer9->Add(bSizer12, 1, 0, 5);

    wxBoxSizer* bSizer13;
    bSizer13 = new wxBoxSizer(wxHORIZONTAL);

    m_staticText3 = new wxStaticText(this, wxID_ANY, wxT("ホスト："),
            wxDefaultPosition, wxSize(100, -1), wxALIGN_RIGHT);
    m_staticText3->Wrap(-1);
    bSizer13->Add(m_staticText3, 0, wxALIGN_CENTER_VERTICAL, 5);

    m_textCtrlHost = new wxTextCtrl(this, wxID_ANY, wxEmptyString,
            wxDefaultPosition, wxSize(200, -1), 0);
    bSizer13->Add(m_textCtrlHost, 0, wxALIGN_CENTER_VERTICAL, 5);

    bSizer9->Add(bSizer13, 1, wxEXPAND, 5);

    wxBoxSizer* bSizer14;
    bSizer14 = new wxBoxSizer(wxHORIZONTAL);

    m_staticText4 = new wxStaticText(this, wxID_ANY, wxT("ポート："),
            wxDefaultPosition, wxSize(100, -1), wxALIGN_RIGHT);
    m_staticText4->Wrap(-1);
    bSizer14->Add(m_staticText4, 0, wxALIGN_CENTER_VERTICAL, 5);

    m_spinCtrlPort = new wxSpinCtrl(this, wxID_ANY, wxEmptyString,
            wxDefaultPosition, wxSize(100, -1), wxSP_ARROW_KEYS, 0, 99999, 0);
    bSizer14->Add(m_spinCtrlPort, 0, wxALIGN_CENTER_VERTICAL, 5);

    bSizer9->Add(bSizer14, 1, wxEXPAND, 5);

    wxBoxSizer* bSizer15;
    bSizer15 = new wxBoxSizer(wxHORIZONTAL);

    m_staticText5 = new wxStaticText(this, wxID_ANY, wxT("ユーザー名："),
            wxDefaultPosition, wxSize(100, -1), wxALIGN_RIGHT);
    m_staticText5->Wrap(-1);
    bSizer15->Add(m_staticText5, 0, wxALIGN_CENTER_VERTICAL, 5);

    m_textCtrlUserName = new wxTextCtrl(this, wxID_ANY, wxEmptyString,
            wxDefaultPosition, wxDefaultSize, 0);
    bSizer15->Add(m_textCtrlUserName, 0, wxALIGN_CENTER_VERTICAL, 5);

    bSizer9->Add(bSizer15, 1, wxEXPAND, 5);

    wxBoxSizer* bSizer16;
    bSizer16 = new wxBoxSizer(wxHORIZONTAL);

    m_staticTextPassword = new wxStaticText(this, wxID_ANY, wxT("パスワード："),
            wxDefaultPosition, wxSize(100, -1), wxALIGN_RIGHT);
    m_staticTextPassword->Wrap(-1);
    bSizer16->Add(m_staticTextPassword, 0, wxALIGN_CENTER_VERTICAL, 5);

    m_textCtrlPassword = new wxTextCtrl(this, wxID_ANY, wxEmptyString,
            wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
    bSizer16->Add(m_textCtrlPassword, 0, wxALIGN_CENTER_VERTICAL, 5);

    bSizer9->Add(bSizer16, 1, wxEXPAND, 5);

    wxBoxSizer* bSizer17;
    bSizer17 = new wxBoxSizer(wxHORIZONTAL);

    m_staticText7 = new wxStaticText(this, wxID_ANY, wxT("オプション："),
            wxPoint(-1, -1), wxSize(100, -1), wxALIGN_RIGHT);
    m_staticText7->Wrap(-1);
    bSizer17->Add(m_staticText7, 0, wxALL, 5);

    m_checkBoxType = new wxCheckBox(this, wxID_ANY, wxT("接続を開始する。"),
            wxDefaultPosition, wxDefaultSize, 0);
    m_checkBoxType->SetValue(true);
    bSizer17->Add(m_checkBoxType, 0, wxALIGN_LEFT, 5);

    bSizer9->Add(bSizer17, 1, wxEXPAND, 5);

    this->SetSizer(bSizer9);
    this->Layout();

    this->Centre(wxBOTH);

    // タイトルバーで消した時の挙動
    SetEscapeId(wxID_CANCEL);
    // 基本ボタン
    wxSizer* buttonSizer = wxDialog::CreateButtonSizer(wxOK | wxCANCEL);
    bSizer9->Add(buttonSizer, 0, wxALIGN_RIGHT, 0);

}

// ユーザ名を取得する
wxString CAuthDialog::getName(void) const
{
    return m_textCtrlUserName->GetValue();
}

// パスワードを取得する
wxString CAuthDialog::getPass(void) const
{
    return m_textCtrlPassword->GetValue();
}

// ホスト名を取得する
wxString CAuthDialog::getHostName(void) const
{
    return m_textCtrlHost->GetValue();
}
// ポートを取得する。
int CAuthDialog::getPort(void) const
{
    return m_spinCtrlPort->GetValue();
}

// 名前を取得する
wxString CAuthDialog::getServiceName(void) const
{
    return m_textCtrlName->GetValue();
}

// すぐに接続するかの
bool CAuthDialog::isStartSoon(void) const
{
    return m_checkBoxType->IsChecked();
}

// サービスの名前を取得
wxString CAuthDialog::getServiceTypeName(void) const
{
    return m_choiceType->GetStringSelection();
}

CChatServiceBase* CAuthDialog::getNewService(void) const
{
    if (validateRegisterDialogResult()){
        CChatServiceBase* service;
        if (getServiceTypeName() == "IRC"){
            service = new IRC::CIRCService();
        } else{
            service = new StarChat::CSCService();
        }
        service->setName(getServiceName());
        service->setHost(getHostName());
        service->setPort(getPort());
        service->registerUser(getName(), getPass());
        return service;
    }
    return NULL;
}
bool CAuthDialog::validateRegisterDialogResult() const
{
    if (getHostName() == ""){
        wxMessageBox("ホスト名を入力してください");
        return false;
    }
    if (getName().IsAscii() == false || getHostName().IsAscii() == false){
        wxMessageBox("半角英数を入力してください");
        return false;
    }
    return true;
}
}

