#pragma once
#include "SCConnection.hpp"
#include "ChannelHolder.hpp"
#include "SCUser.hpp"
#include "NickTable.hpp"
#include "MyPersistent.hpp"
#include "IUser.h"
#include "IConnection.hpp"

// StarChat��Model�R���e���c�������N���X
class CConnectionContents
{
protected:
    // �C�x���g�n���h��
    wxEvtHandler* m_handler;

    // StarChat�̃f�[�^��
    IConnection* m_connect; // �ʐM���i��N���X
    CChannelHolder* m_channel; // �`�����l������ێ�
    IUser* m_user; // ���[�U���
    CNickTable* m_nickTable; // �j�b�N�l�[���e�[�u��

    // �ėp�N���X
    CMyPersistent* m_persist; // �i����������

public:
    CConnectionContents(void);
    ~CConnectionContents(void);

    // ������s��
    virtual void init(wxEvtHandler* handler);

    // ���[�U�����O�C�����Ă��邩
    bool isUserLogin(void) const;

    // ���[�U�o�^���s�����ۂ̃f�[�^�X�V
    void registerUser(const wxString& userName, const wxString& pass);

    // ���O�A�E�g��
    void logout(void);

    // �`�����l���ɎQ�����s����
    void joinChannel(const wxString& channel);

    // �`�����l�����痣�E�����
    void partChannel(const wxString& channel);

    // �Đڑ����s��
    void reconnect(void);

    // �e�`�����l���̏���j��
    void clearChannels(void);

    // �j�b�N�l�[���e�[�u����j��
    void clearNickTable(void);

    // ���݂̃`�����l�������擾
    wxString getCurrentChannel(void) const;

    // ���b�Z�[�W�𐶐�
    CMessageData generateMessage(const wxString& body);

    // �j�b�N�l�[�����擾
    wxString getNickName(void) const;

    // ���b�Z�[�W�𓊍e������
    void postMessage(const CMessageData& message);

    // �`�����l����I��������
    void selectChannel(const wxString& channel);

    // �`�����l���ꗗ���擾
    std::vector<wxString> getChannels(void) const;

    // ���b�Z�[�W�ꗗ���擾
    std::vector<CMessageData*> getMessages(const wxString& channel) const;

    // �����o�[�ꗗ���擾
    std::vector<CMemberData*> getMembers(const wxString& channel) const;

    // �j�b�N�l�[���e�[�u�����擾
    CNickTable getNickTable(void) const;

    // ���[�U���Ă΂ꂽ��
    bool isUserCalled(const wxString& message);

    // �����o�[�̃j�b�N�l�[�����擾
    wxString getMemberNick(const wxString& member);

    // �`�����l���̃g�s�b�N���擾
    wxString getTopic(const wxString& channel);

    // ���̃N���C�A���g���瓊�e���ꂽ���b�Z�[�W��
    bool isPostedThisClient(const CMessageData& message);



    // 
    void onUpdateMessageView(const wxString& channel);

    // 
    void onUpdateMemberView(const wxString& channel);

    // 
    void onUpdateChannelView(void);



    /////////////////////////////////////////

    // �F�؂����������ꍇ
    void onAuthSucceeed(void);

    // ���b�Z�[�W�ꗗ���擾�����ꍇ
    void onGetMessages(const std::vector<CMessageData*>& messages);

    // �����o�[�ꗗ���擾�����ꍇ
    void onGetMembers(const std::vector<CMemberData*>& members);

    // �`�����l���ꗗ���擾�����ꍇ
    void onGetChannels(const std::vector<CChannelData*>& channels);

    // �`�����l���Q��������
    void onJoinChannel(const wxString& channel);

    // �`�����l�����E������
    void onPartChannel(const wxString& channel);

    // �����o�[�����擾�����ꍇ
    void onGetMemberStatus(const CMemberData& member);

    // ���b�Z�[�W�X�g���[�����擾�����ꍇ
    void onGetMessageStream(const CMessageData& message);

    // �`�����l���Q���X�g���[������M
    void onGetJoinStream(const wxString& channel, const wxString& name);

    // �`�����l�����E�X�g���[������M
    void onGetPartStream(const wxString& channel, const wxString& name);

    // �`�����l�����X�V�X�g���[������M
    void onGetChannelStream(const CChannelData& channel);

    // ���[�U���X�V�X�g���[���̎�M
    void onGetUserStream(const CMemberData& member);
};

