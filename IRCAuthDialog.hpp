#pragma once
#include "AuthDialog.hpp"

// IRC�̃T�[�o�ǉ��p�F�؃_�C�A���O
class CIRCAuthDialog : public CAuthDialog
{
private:
    wxTextCtrl* m_nickText;

public:
    CIRCAuthDialog(void);
    ~CIRCAuthDialog(void);

    // ���������s��
    void init(wxWindow* parent, const wxString& title);

    // �j�b�N�l�[�����擾����
    wxString getNick(void) const;
};

