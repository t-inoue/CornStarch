#pragma once
#include "MessageVec.hpp"
#include "MemberVec.hpp"

// �`�����l���̓������(�N�����邩�⃁�b�Z�[�W�Ȃ�)���Ǘ�
class CChannelStatus
{
private:
    wxString m_topic; // �g�s�b�N
    CMessageVec* m_messages; // ���b�Z�[�W�ꗗ
    CMemberVec* m_members; // �����o�[�ꗗ

public:
    CChannelStatus(void);
    ~CChannelStatus(void);

    // ������s��
    void init(void);

    // �g�s�b�N���Z�b�g����
    void setTopic(const wxString& topic);

    // �g�s�b�N���擾����
    wxString getTopic(void) const;

    // ���b�Z�[�W�ꗗ���擾����
    std::vector<CMessageData*> getMessages(void) const;

    // �����o�[�ꗗ���擾����
    std::vector<CMemberData*> getMembers(void) const;

    // ���b�Z�[�W��ǉ�����
    void pushMessage(const CMessageData& message);

    // �����o�[��ǉ�����
    void pushMember(const CMemberData& member);

    // ���b�Z�[�W�ꗗ���Z�b�g����
    void setMessages(const std::vector<CMessageData*>& messages);

    // �����o�[�ꗗ���Z�b�g����
    void setMembers(const std::vector<CMemberData*>& members);

    // ���b�Z�[�W���擾���I������
    bool hasReceivedMessage(void) const;

    // �����o���擾���I������
    bool hasReceivedMember(void) const;

    // ID�s�����������e���e�̃��b�Z�[�W�����邩
    bool hasSameMessage(const CMessageData& message) const;

    // �������e�̃��b�Z�[�W�ɂ���ID���X�V
    void updateMessageId(const CMessageData& message);

    // �����o�[�����X�V����
    void updateMember(const CMemberData& member);

    // �����o�[��������
    void popMember(const wxString& userName);
};

