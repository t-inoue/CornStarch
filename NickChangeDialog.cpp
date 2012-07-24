#include "NickChangeDialog.hpp"


CNickChangeDialog::CNickChangeDialog(void) : m_nickText(NULL)
{
}


CNickChangeDialog::~CNickChangeDialog(void)
{
}


//////////////////////////////////////////////////////////////////////


// ���������s��
void CNickChangeDialog::init(wxWindow* parent, const wxString& title)
{
    wxDialog::Create(parent, wxID_ANY, title);

    // ���g�ɓ\��t����p�l�����쐬
    wxPanel* panel = new wxPanel(this, wxID_ANY);

    // �p�l����̃e�L�X�g�{�b�N�X
    m_nickText = new wxTextCtrl(
        panel, wxID_ANY, "", wxPoint(100, 50), wxSize(100, 30));

    // �p�l����̕���
    wxStaticText* sChannel = new wxStaticText(
        panel, wxID_ANY, "�j�b�N�l�[��", wxPoint(10, 50));

    // �p�l����̃{�^��
    wxButton* ok = new wxButton(panel, wxID_OK, "OK",  wxPoint(250, 150));

    // Esc�ŏ��������̋���
    SetEscapeId(wxID_CANCEL);

    // �G���^�[�L�[�������̋���
    SetDefaultItem(ok);
}

// �`�����l�������擾����
wxString CNickChangeDialog::getNickName(void) const
{
    if (m_nickText != NULL){
        return m_nickText->GetValue();
    }

    return "";
}

