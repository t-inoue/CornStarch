#include "IRCAuthDialog.hpp"


CIRCAuthDialog::CIRCAuthDialog(void)
{
}


CIRCAuthDialog::~CIRCAuthDialog(void)
{
}


//////////////////////////////////////////////////////////////////////


// ���������s��
void CIRCAuthDialog::init(wxWindow* parent, const wxString& title)
{
    CAuthDialog::init(parent, title);

    // �e�L�X�g�{�b�N�X
    m_nickText = new wxTextCtrl(
        m_panel, wxID_ANY, "", wxPoint(100, 90), wxSize(200, 30));

    // ����
    wxStaticText* shost = new wxStaticText(
        m_panel, wxID_ANY, "�j�b�N�l�[��", wxPoint(10, 90));
}

// �j�b�N�l�[�����擾����
wxString CIRCAuthDialog::getNick(void) const
{
    return m_nickText->GetValue();
}
