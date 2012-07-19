#include "ConnectionContents.hpp"

using namespace std;

CConnectionContents::CConnectionContents(void) : m_handler(NULL), m_persist(NULL), 
    m_channel(NULL), m_user(NULL), m_nickTable(NULL), m_connect(NULL)
{
}


CConnectionContents::~CConnectionContents(void)
{
    delete m_connect;
    delete m_channel;
    delete m_user;
    delete m_nickTable;

    delete m_persist;
}


//////////////////////////////////////////////////////////////////////


// ������s��
void CConnectionContents::init(wxEvtHandler* handler)
{
    // �C�x���g�n���h���̓o�^
    m_handler = handler;



    // �f�[�^�ێ����̏���
    m_channel = new CChannelHolder(); // �`�����l��
    m_channel->init();



    // �j�b�N�l�[���e�[�u���̏���
    m_nickTable = new CNickTable();

    // �i�����������N���X�̏���
    m_persist = new CMyPersistent();
    m_persist->init();


//    // �ʐM�̏���
//    m_connect = new CSCConnection();
//    m_connect->init(m_handler);
//    // ���[�U���̏���
//    m_user = new CSCUser();
//    m_user->init();
//    m_user->setChannel("");
//
//    // �p�X���[�h��񂪕ۑ�����Ă����
//    wxString basicKey = m_user->getBasicKey();
//    wxString nameKey = m_user->getNameKey();
//    if (m_persist->isKeySaved(basicKey) && m_persist->isKeySaved(nameKey)){
//
//        // �p�X���[�h����ǂݍ���
//        m_user->setUserName(m_persist->loadInfo(nameKey));
//        m_user->setBasic(m_persist->loadInfo(basicKey));
//
//        // �F�؃^�X�N���J�n����
//        m_connect->startAuthTask(m_handler, m_user->getUserName(), m_user->getBasic());
//    }
}

// ���[�U�����O�C�����Ă��邩
bool CConnectionContents::isUserLogin(void) const
{
    return m_user->isLogin();
}

// ���[�U�o�^���s�����ۂ̃f�[�^�X�V
void CConnectionContents::registerUser(const wxString& userName, const wxString& pass)
{
    // ���[�U�����Z�b�g
    m_user->setUserInfo(userName, pass);

    // �F�؃^�X�N�̊J�n
    m_connect->startAuthTask(m_handler, m_user->getUserName(), m_user->getBasic());
}

// ���O�A�E�g��
void CConnectionContents::logout(void)
{
    // ���O�C�����Ă���Ƃ��A�ۑ����Ă�������폜
    if (isUserLogin()){
        m_persist->deleteInfo(m_user->getNameKey());
        m_persist->deleteInfo(m_user->getBasicKey());
    }
}

// �`�����l���ɎQ�����s����
void CConnectionContents::joinChannel(const wxString& channel)
{
    // �`�����l���Q���^�X�N�̊J�n
    m_connect->startJoinTask(m_handler, channel, m_user->getUserName(), m_user->getBasic());
}

// �`�����l�����痣�E�����
void CConnectionContents::partChannel(const wxString& channel)
{
    // �`�����l�����E�^�X�N���J�n
    m_connect->startPartTask(m_handler, channel, m_user->getUserName(), m_user->getBasic());
}

// �Đڑ����s��
void CConnectionContents::reconnect(void)
{
    // �ʐM������
    delete m_connect;
    m_connect = new CSCConnection();
    m_connect->init(m_handler);
    m_connect->startStreamTask(m_handler, m_user->getUserName(), m_user->getBasic());
}

// �e�`�����l���̏���j��
void CConnectionContents::clearChannels(void)
{
    m_channel->deleteChannels();
}

// �j�b�N�l�[���e�[�u����j��
void CConnectionContents::clearNickTable(void)
{
    delete m_nickTable;
    m_nickTable = new CNickTable();
}

// ���݂̃`�����l�������擾
wxString CConnectionContents::getCurrentChannel(void) const
{
    return m_user->getChannelString();
}

// ���b�Z�[�W�𐶐�
CMessageData CConnectionContents::generateMessage(const wxString& body)
{
    return CMessageData(-1, m_user->getUserName(), body, m_user->getChannelString(), time(NULL));
}

// �j�b�N�l�[�����擾
wxString CConnectionContents::getNickName(void) const
{
    return m_user->getNickName();
}

// ���b�Z�[�W�𓊍e������
void CConnectionContents::postMessage(const CMessageData& message)
{
    // ���b�Z�[�W���e�^�X�N�̊J�n
    wxString channel = m_user->getChannelString();
    m_connect->startPostMessageTask(m_handler, message.m_body, channel, m_user->getBasic());

    // ���b�Z�[�W��ۑ�
    CMessageData data(-1, m_user->getUserName(), message.m_body, channel, time(NULL));
    m_channel->pushMessage(data.m_channel, data);
}

// �`�����l����I��������
void CConnectionContents::selectChannel(const wxString& channel)
{
    m_user->setChannel(channel);
}

// �`�����l���ꗗ���擾
vector<wxString> CConnectionContents::getChannels(void) const
{
    return m_channel->getChannels();
}

// ���b�Z�[�W�ꗗ���擾
vector<CMessageData*> CConnectionContents::getMessages(const wxString& channel) const
{
    return m_channel->getMessages(channel);
}

// �����o�[�ꗗ���擾
vector<CMemberData*> CConnectionContents::getMembers(const wxString& channel) const
{
    return m_channel->getMembers(channel);
}

// �j�b�N�l�[���e�[�u�����擾
CNickTable CConnectionContents::getNickTable(void) const
{
    return *m_nickTable;
}

// ���[�U���Ă΂ꂽ��
bool CConnectionContents::isUserCalled(const wxString& message)
{
    return m_user->isCalled(message);
}

// �����o�[�̃j�b�N�l�[�����擾
wxString CConnectionContents::getMemberNick(const wxString& member)
{
    return m_nickTable->getNickname(member);
}

// �`�����l���̃g�s�b�N���擾
wxString CConnectionContents::getTopic(const wxString& channel)
{
    return m_channel->getTopic(channel);
}

// ���̃N���C�A���g���瓊�e���ꂽ���b�Z�[�W��
bool CConnectionContents::isPostedThisClient(const CMessageData& message)
{
    return m_channel->hasSameMessage(message);
}

// 
void CConnectionContents::onUpdateMessageView(const wxString& channel)
{
    // ���b�Z�[�W����M�ς�
    if (!m_channel->hasReceivedMessage(channel)){

        // ���b�Z�[�W�擾�^�X�N���J�n
        m_connect->startGetMessageTask(m_handler, channel, m_user->getBasic());
    }
}

// 
void CConnectionContents::onUpdateMemberView(const wxString& channel)
{
    // �����o�[��M�ς�
    if (!m_channel->hasReceivedMember(channel)){

        // �����o�[�擾�^�X�N���J�n
        m_connect->startGetMemberTask(m_handler, channel, m_user->getBasic());
    }
}

// 
void CConnectionContents::onUpdateChannelView(void)
{
    // �`�����l����M�ς݂Ȃ�
    if (!m_channel->hasReceivedChannel()){

        // �`�����l���擾�^�X�N���J�n
        m_connect->startGetChannelTask(m_handler, m_user->getUserName(), m_user->getBasic());
    }
}


/////////////////////////////////////////

// �F�؂����������ꍇ
void CConnectionContents::onAuthSucceeed(void)
{
    // ���[�U�����O�C����Ԃɂ���
    m_user->setLogin(true);

    // �p�X���[�h�i����
    m_persist->saveInfo(m_user->getNameKey(), m_user->getUserName());
    m_persist->saveInfo(m_user->getBasicKey(), m_user->getBasic());

    // �j�b�N�l�[���擾�^�X�N
    m_connect->startGetMemberInfoTask(m_handler, m_user->getUserName(), m_user->getBasic());

    // �X�g���[����M�^�X�N
    m_connect->startStreamTask(m_handler, m_user->getUserName(), m_user->getBasic());
}

// ���b�Z�[�W�ꗗ���擾�����ꍇ
void CConnectionContents::onGetMessages(const vector<CMessageData*>& messages)
{
    m_channel->setMessages(m_user->getChannelString(), messages);
}

// �����o�[�ꗗ���擾�����ꍇ
void CConnectionContents::onGetMembers(const vector<CMemberData*>& members)
{
    m_channel->setMembers(m_user->getChannelString(), members);
    m_nickTable->addTableFromMembers(members);
}

// �`�����l���ꗗ���擾�����ꍇ
void CConnectionContents::onGetChannels(const vector<CChannelData*>& channels)
{
    m_channel->setChannels(channels);

    if (m_user->getChannelString() == ""){
        m_user->setChannel(m_channel->getFirstChannel());
    }
}

// �`�����l���Q��������
void CConnectionContents::onJoinChannel(const wxString& channel)
{
    // ���[�U�̌��݂̃`�����l����ύX
    m_user->setChannel(channel);

    // �`�����l���ꗗ�擾�^�X�N�̊J�n
    m_connect->startGetChannelTask(m_handler,
        m_user->getUserName(), m_user->getBasic());
}

// �`�����l�����E������
void CConnectionContents::onPartChannel(const wxString& channel)
{
    // �`�����l�������폜
    m_channel->popChannel(channel);

    // ���[�U�̌��݂̃`�����l����ύX
    m_user->setChannel(m_channel->getFirstChannel());
}

// �����o�[�����擾�����ꍇ
void CConnectionContents::onGetMemberStatus(const CMemberData& member)
{
    // �����̏�񂾂�����
    if (member.m_name == m_user->getUserName()){
        m_user->setNickName(member.m_nick);
        m_user->setKeywords(member.m_keywords);
    }

    m_channel->updateMember(member);
    (*m_nickTable)[member.m_name] = member.m_nick;
}

// ���b�Z�[�W�X�g���[�����擾�����ꍇ
void CConnectionContents::onGetMessageStream(const CMessageData& message)
{
    // �ʃN���C�A���g����̃��b�Z�[�W��������A�f�[�^�X�V�̂�
    if (m_channel->hasSameMessage(message)){
        m_channel->onUpdateMessageId(message);
        return;
    }

    // �f�[�^�X�V
    wxString nick = m_nickTable->getNickname(message.m_username);

    // �j�b�N�l�[�������m�̏ꍇ�A�����o�[���擾�^�X�N�̊J�n
    if (!m_nickTable->isExist(message.m_username)){
        m_connect->startGetMemberInfoTask(m_handler, message.m_username, m_user->getBasic());
    }

    // �f�[�^�ǉ�
    m_channel->pushMessage(message.m_channel, message);
}

// �`�����l���Q���X�g���[������M
void CConnectionContents::onGetJoinStream(const wxString& channel, const wxString& name)
{
    // �����҂��ɒǉ�
    CSubscribeData data (channel, name);

    wxString nick = m_nickTable->getNickname(data.m_username);

    // �j�b�N�l�[�������m�̏ꍇ�A�����o�[���擾�^�X�N�̊J�n
    if (!m_nickTable->isExist(data.m_username)){
        m_connect->startGetMemberInfoTask(m_handler,
            name, m_user->getBasic());
    }

    // �����o�[��ǉ�
    m_channel->pushMember(data.m_channel, CMemberData(data.m_username, nick));

    // �������Q�������Ƃ�(�ʃN���C�A���g�\�t�g����)
    if (data.m_username == m_user->getUserName()){

        // �`�����l�����擾�^�X�N�̊J�n
        m_connect->startGetChannelTask(
            m_handler, m_user->getUserName(), m_user->getBasic());
    }
}

// �`�����l�����E�X�g���[������M
void CConnectionContents::onGetPartStream(const wxString& channel, const wxString& name)
{
    CSubscribeData data (channel, name);

    // �f�[�^�X�V
    wxString nick = m_nickTable->getNickname(name);
    m_channel->popMember(data.m_username);

    // �j�b�N�l�[�������m�̎��A�����o�[���擾�^�X�N�̊J�n
    if (!m_nickTable->isExist(name)){
        m_connect->startGetMemberInfoTask(m_handler, name, m_user->getBasic());
    }
}

// �`�����l�����X�V�X�g���[������M
void CConnectionContents::onGetChannelStream(const CChannelData& channel)
{
    m_channel->setChannel(channel);
}

// ���[�U���X�V�X�g���[���̎�M
void CConnectionContents::onGetUserStream(const CMemberData& member)
{
    m_channel->updateMember(member);
    (*m_nickTable)[member.m_name] = member.m_nick;
}
