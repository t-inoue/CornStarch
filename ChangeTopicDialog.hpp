#pragma once
#include "header.hpp"

// �`�����l���g�s�b�N�ύX�p�_�C�A���O
class CChangeTopicDialog : public wxDialog
{
private:
    wxTextCtrl* m_topicText; // �V�g�s�b�N���͗p�_�C�A���O

public:
    CChangeTopicDialog(void);
    ~CChangeTopicDialog(void);

    // ���������s��
    void init(wxWindow* parent, const wxString& title);

    // �g�s�b�N���擾����
    wxString getTopic(void) const;
};

