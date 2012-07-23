#include "ChangeTopicDialog.hpp"


CChangeTopicDialog::CChangeTopicDialog(void)
{
}


CChangeTopicDialog::~CChangeTopicDialog(void)
{
}


//////////////////////////////////////////////////////////////////////


// ���������s��
void CChangeTopicDialog::init(wxWindow* parent, const wxString& title)
{
    wxDialog::Create(parent, wxID_ANY, title);

    // ���g�ɓ\��t����p�l�����쐬
    wxPanel* panel = new wxPanel(this, wxID_ANY);

    // �p�l����̃e�L�X�g�{�b�N�X
    m_topicText = new wxTextCtrl(
        panel, wxID_ANY, "", wxPoint(100, 50), wxSize(100, 30));

    // �p�l����̕���
    wxStaticText* sChannel = new wxStaticText(
        panel, wxID_ANY, "�g�s�b�N", wxPoint(10, 50));

    // �p�l����̃{�^��
    wxButton* ok = new wxButton(panel, wxID_OK, "OK",  wxPoint(250, 150));

    // Esc�ŏ��������̋���
    SetEscapeId(wxID_CANCEL);

    // �G���^�[�L�[�������̋���
    SetDefaultItem(ok);
}

// �`�����l�������擾����
wxString CChangeTopicDialog::getTopic(void) const
{
    if (m_topicText != NULL){
        return m_topicText->GetValue();
    }

    return "";
}

