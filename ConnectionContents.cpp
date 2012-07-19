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


// 初期化を行う
void CConnectionContents::init(wxEvtHandler* handler)
{
    // イベントハンドラの登録
    m_handler = handler;

    // データ保持部の初期化
    m_channel = new CChannelHolder(); // チャンネル
    m_channel->init();


    // ニックネームテーブルの初期化
    m_nickTable = new CNickTable();

    // 永続化を扱うクラスの初期化
    m_persist = new CMyPersistent();
    m_persist->init();

}

// ユーザがログインしているか
bool CConnectionContents::isUserLogin(void) const
{
    return m_user->isLogin();
}

// ユーザ登録を行った際のデータ更新
void CConnectionContents::registerUser(const wxString& userName, const wxString& pass)
{
    // ユーザ情報をセット
    m_user->setUserInfo(userName, pass);

    // 認証タスクの開始
    m_connect->startAuthTask(m_user);
}

// ログアウト時
void CConnectionContents::logout(void)
{
    // ログインしているとき、保存してある情報を削除
    if (isUserLogin()){
        m_persist->deleteValue(m_user->getNameKey());
        m_persist->deleteValue(m_user->getBasicKey());
    }
}

// チャンネルに参加を行う際
void CConnectionContents::joinChannel(const wxString& channel)
{
    // チャンネル参加タスクの開始
    m_connect->startJoinTask(m_user, channel);
}

// チャンネルから離脱する際
void CConnectionContents::partChannel(const wxString& channel)
{
    // チャンネル離脱タスクを開始
    m_connect->startPartTask(m_user, channel);
}

// 再接続を行う
void CConnectionContents::reconnect(void)
{
    // 通信を初期化
    delete m_connect;
    m_connect = new CSCConnection();
    m_connect->init(m_id, m_handler);
    m_connect->startStreamTask( m_user);
}

// 各チャンネルの情報を破棄
void CConnectionContents::clearChannels(void)
{
    m_channel->deleteChannels();
}

// ニックネームテーブルを破棄
void CConnectionContents::clearNickTable(void)
{
    delete m_nickTable;
    m_nickTable = new CNickTable();
}

// 現在のチャンネル名を取得
wxString CConnectionContents::getCurrentChannel(void) const
{
    return m_user->getChannelString();
}

// メッセージを生成
CMessageData CConnectionContents::generateMessage(const wxString& body)
{
    return CMessageData(-1, m_user->getUserName(), body, m_user->getChannelString(), time(NULL));
}

// ニックネームを取得
wxString CConnectionContents::getNickName(void) const
{
    return m_user->getNickName();
}

// メッセージを投稿した際
void CConnectionContents::postMessage(const CMessageData& message)
{
    // メッセージ投稿タスクの開始
    wxString channel = m_user->getChannelString();
    m_connect->startPostMessageTask(m_user, message.m_body, channel );

    // メッセージを保存
    CMessageData data(-1, m_user->getUserName(), message.m_body, channel, time(NULL));
    m_channel->pushMessage(data.m_channel, data);
}

// チャンネルを選択した際
void CConnectionContents::selectChannel(const wxString& channel)
{
    m_user->setChannel(channel);
}

// チャンネル一覧を取得
vector<wxString> CConnectionContents::getChannels(void) const
{
    return m_channel->getChannels();
}

// メッセージ一覧を取得
vector<CMessageData*> CConnectionContents::getMessages(const wxString& channel) const
{
    return m_channel->getMessages(channel);
}

// メンバー一覧を取得
vector<CMemberData*> CConnectionContents::getMembers(const wxString& channel) const
{
    return m_channel->getMembers(channel);
}

// ニックネームテーブルを取得
CNickTable CConnectionContents::getNickTable(void) const
{
    return *m_nickTable;
}

// ユーザが呼ばれたか
bool CConnectionContents::isUserCalled(const wxString& message)
{
    return m_user->isCalled(message);
}

// メンバーのニックネームを取得
wxString CConnectionContents::getMemberNick(const wxString& member)
{
    return m_nickTable->getNickname(member);
}

// チャンネルのトピックを取得
wxString CConnectionContents::getTopic(const wxString& channel)
{
    return m_channel->getTopic(channel);
}

// このクライアントから投稿されたメッセージか
bool CConnectionContents::isPostedThisClient(const CMessageData& message)
{
    return m_channel->hasSameMessage(message);
}

// メッセージ表示を行う際
void CConnectionContents::onUpdateMessageView(const wxString& channel)
{
    // メッセージが受信済み
    if (!m_channel->hasReceivedMessage(channel)){

        // メッセージ取得タスクを開始
        m_connect->startGetMessageTask(m_user, channel);
    }
}

// メンバー表示を行う際
void CConnectionContents::onUpdateMemberView(const wxString& channel)
{
    // メンバー受信済み
    if (!m_channel->hasReceivedMember(channel)){

        // メンバー取得タスクを開始
        m_connect->startGetMemberTask(m_user, channel);
    }
}

// チャンネル表示を行う際
void CConnectionContents::onUpdateChannelView(void)
{
    // チャンネル受信済みなら
    if (!m_channel->hasReceivedChannel()){

        // チャンネル取得タスクを開始
        m_connect->startGetChannelTask( m_user);
    }
}


/////////////////////////////////////////


// 認証が成功した場合
void CConnectionContents::onAuthSucceeed(void)
{
    // ユーザをログイン状態にする
    m_user->setLogin(true);

    // パスワード永続化
    m_persist->saveValue(m_user->getNameKey(), m_user->getUserName());
    m_persist->saveValue(m_user->getBasicKey(), m_user->getBasic());

    // ニックネーム取得タスク
    m_connect->startGetMemberInfoTask(m_user,m_user->getUserName());

    // ストリーム受信タスク
    m_connect->startStreamTask(m_user);
}

// メッセージ一覧を取得した場合
void CConnectionContents::onGetMessages(const vector<CMessageData*>& messages)
{
    m_channel->setMessages(m_user->getChannelString(), messages);
}

// メンバー一覧を取得した場合
void CConnectionContents::onGetMembers(const vector<CMemberData*>& members)
{
    m_channel->setMembers(m_user->getChannelString(), members);
    m_nickTable->addTableFromMembers(members);
}

// チャンネル一覧を取得した場合
void CConnectionContents::onGetChannels(const vector<CChannelData*>& channels)
{
    m_channel->setChannels(channels);

    if (m_user->getChannelString() == ""){
        m_user->setChannel(m_channel->getFirstChannel());
    }
}

// チャンネル参加成功時
void CConnectionContents::onJoinChannel(const wxString& channel)
{
    // ユーザの現在のチャンネルを変更
    m_user->setChannel(channel);

    // チャンネル一覧取得タスクの開始
    m_connect->startGetChannelTask(
    		m_user);
}

// チャンネル離脱成功時
void CConnectionContents::onPartChannel(const wxString& channel)
{
    // チャンネル情報を削除
    m_channel->popChannel(channel);

    // ユーザの現在のチャンネルを変更
    m_user->setChannel(m_channel->getFirstChannel());
}

// メンバー情報を取得した場合
void CConnectionContents::onGetMemberStatus(const CMemberData& member)
{
    // 自分の情報だったら
    if (member.m_name == m_user->getUserName()){
        m_user->setNickName(member.m_nick);
        m_user->setKeywords(member.m_keywords);
    }

    m_channel->updateMember(member);
    (*m_nickTable)[member.m_name] = member.m_nick;
}

// メッセージストリームを取得した場合
void CConnectionContents::onGetMessageStream(const CMessageData& message)
{
    // 別クライアントからのメッセージだったら、データ更新のみ
    if (m_channel->hasSameMessage(message)){
        m_channel->onUpdateMessageId(message);
        return;
    }

    // データ更新
    wxString nick = m_nickTable->getNickname(message.m_username);

    // ニックネームが未知の場合、メンバー情報取得タスクの開始
    if (!m_nickTable->isExist(message.m_username)){
        m_connect->startGetMemberInfoTask(m_user, message.m_username);
    }

    // データ追加
    m_channel->pushMessage(message.m_channel, message);
}

// チャンネル参加ストリームを受信
void CConnectionContents::onGetJoinStream(const wxString& channel, const wxString& name)
{
    // 処理待ちに追加
    CSubscribeData data (channel, name);

    wxString nick = m_nickTable->getNickname(data.m_username);

    // ニックネームが未知の場合、メンバー情報取得タスクの開始
    if (!m_nickTable->isExist(data.m_username)){
        m_connect->startGetMemberInfoTask(m_user,
            name);
    }

    // メンバーを追加
    m_channel->pushMember(data.m_channel, CMemberData(data.m_username, nick));

    // 自分が参加したとき(別クライアントソフトから)
    if (data.m_username == m_user->getUserName()){

        // チャンネル情報取得タスクの開始
        m_connect->startGetChannelTask(
        		m_user);
    }
}

// チャンネル離脱ストリームを受信
void CConnectionContents::onGetPartStream(const wxString& channel, const wxString& name)
{
    CSubscribeData data (channel, name);

    // データ更新
    wxString nick = m_nickTable->getNickname(name);
    m_channel->popMember(data.m_username);

    // ニックネームが未知の時、メンバー情報取得タスクの開始
    if (!m_nickTable->isExist(name)){
        m_connect->startGetMemberInfoTask(m_user, name);
    }
}

// チャンネル情報更新ストリームを受信
void CConnectionContents::onGetChannelStream(const CChannelData& channel)
{
    m_channel->setChannel(channel);
}

// ユーザ情報更新ストリームの受信
void CConnectionContents::onGetUserStream(const CMemberData& member)
{
    m_channel->updateMember(member);
    (*m_nickTable)[member.m_name] = member.m_nick;
}
