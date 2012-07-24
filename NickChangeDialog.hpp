#pragma once
#include "header.hpp"

// �j�b�N�l�[���ύX�p�_�C�A���O
class CNickChangeDialog : public wxDialog
{
private:
    wxTextCtrl* m_nickText; // �j�b�N�l�[�����͗�
public:
    CNickChangeDialog(void);
    ~CNickChangeDialog(void);

    // ���������s��
    void init(wxWindow* parent, const wxString& title);

    // �j�b�N�l�[�����擾����
    wxString getNickName(void) const;
};

