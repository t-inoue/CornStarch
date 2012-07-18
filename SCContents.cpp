#include "SCContents.hpp"

using namespace std;

CSCContents::CSCContents(void) : m_handler(NULL), m_persist(NULL), 
    m_channel(NULL), m_user(NULL), m_nickTable(NULL), m_connect(NULL)
{
}


CSCContents::~CSCContents(void)
{
    delete m_connect;
    delete m_channel;
    delete m_user;
    delete m_nickTable;

    delete m_persist;
}


//////////////////////////////////////////////////////////////////////


// 初期化を行う
void CSCContents::init(wxEvtHandler* handler)
{
    // イベントハンドラの登録
    m_handler = handler;

    // 通信の初期化
    m_connect = new CSCConnection();
    m_connect->init();

    // データ保持部の初期化
    m_channel = new CSCChannelHolder(); // チャンネル
    m_channel->init();

    // ユーザ情報の初期化
    m_user = new CSCUser();
    m_user->init();
    m_user->setChannel("");

    // ニックネームテーブルの初期化
    m_nickTable = new CSCNickTable();

    // 永続化を扱うクラスの初期化
    m_persist = new CMyPersistent();
    m_persist->init();

    // パスワード情報が保存されていれば
    wxString basicKey = m_user->getBasicKey();
    wxString nameKey = m_user->getNameKey();
    if (m_persist->isKeySaved(basicKey) && m_persist->isKeySaved(nameKey)){

        // パスワード情報を読み込む
        m_user->setUserName(m_persist->loadInfo(nameKey));
        m_user->setBasic(m_persist->loadInfo(basicKey));

        // 認証タスクを開始する
        m_connect->startAuthTask(m_handler, m_user->getUserName(), m_user->getBasic());
    }
}

// ユーザがログインしているか
bool CSCContents::isUserLogin(void) const
{
    return m_user->isLogin();
}

// ユーザ登録を行った際のデータ更新
void CSCContents::registerUser(const wxString& userName, const wxString& pass)
{
    // ユーザ情報をセット
    m_user->setUserInfo(userName, pass);

    // 認証タスクの開始
    m_connect->startAuthTask(m_handler, m_user->getUserName(), m_user->getBasic());
}

// ログアウト時
void CSCContents::logout(void)
{
    // ログインしているとき、保存してある情報を削除
    if (isUserLogin()){
        m_persist->deleteInfo(m_user->getNameKey());
        m_persist->deleteInfo(m_user->getBasicKey());
    }
}

// チャンネルに参加を行う際
void CSCContents::joinChannel(const wxString& channel)
{
    // チャンネル参加タスクの開始
    m_connect->startJoinTask(m_handler, channel, m_user->getUserName(), m_user->getBasic());
}

// チャンネルから離脱する際
void CSCContents::partChannel(const wxString& channel)
{
    // チャンネル離脱タスクを開始
    m_connect->startPartTask(m_handler, channel, m_user->getUserName(), m_user->getBasic());
}

// 再接続を行う
void CSCContents::reconnect(void)
{
    // 通信を初期化
    delete m_connect;
    m_connect = new CSCConnection();
    m_connect->init();
    m_connect->startStreamTask(m_handler, m_user->getUserName(), m_user->getBasic());
}

// 各チャンネルの情報を破棄
void CSCContents::clearChannels(void)
{
    m_channel->deleteChannels();
}

// ニックネームテーブルを破棄
void CSCContents::clearNickTable(void)
{
    delete m_nickTable;
    m_nickTable = new CSCNickTable();
}

// 現在のチャンネル名を取得
wxString CSCContents::getCurrentChannel(void) const
{
    return m_user->getChannelString();
}

// メッセージを生成
CMessageData CSCContents::generateMessage(const wxString& body)
{
    return CMessageData(-1, m_user->getUserName(), body, m_user->getChannelString(), time(NULL));
}

// ニックネームを取得
wxString CSCContents::getNickName(void) const
{
    return m_user->getNickName();
}

// メッセージを投稿した際
void CSCContents::postMessage(const CMessageData& message)
{
    // メッセージ投稿タスクの開始
    wxString channel = m_user->getChannelString();
    m_connect->startPostMessageTask(m_handler, message.m_body, channel, m_user->getBasic());

    // メッセージを保存
    CMessageData data(-1, m_user->getUserName(), message.m_body, channel, time(NULL));
    m_channel->pushMessage(data.m_channel, data);
}

// チャンネルを選択した際
void CSCContents::selectChannel(const wxString& channel)
{
    m_user->setChannel(channel);
}

// チャンネル一覧を取得
vector<wxString> CSCContents::getChannels(void) const
{
    return m_channel->getChannels();
}

// メッセージ一覧を取得
vector<CMessageData*> CSCContents::getMessages(const wxString& channel) const
{
    return m_channel->getMessages(channel);
}

// メンバー一覧を取得
vector<CMemberData*> CSCContents::getMembers(const wxString& channel) const
{
    return m_channel->getMembers(channel);
}

// ニックネームテーブルを取得
CSCNickTable CSCContents::getNickTable(void) const
{
    return *m_nickTable;
}

// ユーザが呼ばれたか
bool CSCContents::isUserCalled(const wxString& message)
{
    return m_user->isCalled(message);
}

// メンバーのニックネームを取得
wxString CSCContents::getMemberNick(const wxString& member)
{
    return m_nickTable->getNickname(member);
}

// チャンネルのトピックを取得
wxString CSCContents::getTopic(const wxString& channel)
{
    return m_channel->getTopic(channel);
}

// このクライアントから投稿されたメッセージか
bool CSCContents::isPostedThisClient(const CMessageData& message)
{
    return m_channel->hasSameMessage(message);
}

// 
void CSCContents::onUpdateMessageView(const wxString& channel)
{
    // メッセージが受信済み
    if (!m_channel->hasReceivedMessage(channel)){

        // メッセージ取得タスクを開始
        m_connect->startGetMessageTask(m_handler, channel, m_user->getBasic());
    }
}

// 
void CSCContents::onUpdateMemberView(const wxString& channel)
{
    // メンバー受信済み
    if (!m_channel->hasReceivedMember(channel)){

        // メンバー取得タスクを開始
        m_connect->startGetMemberTask(m_handler, channel, m_user->getBasic());
    }
}

// 
void CSCContents::onUpdateChannelView(void)
{
    // チャンネル受信済みなら
    if (!m_channel->hasReceivedChannel()){

        // チャンネル取得タスクを開始
        m_connect->startGetChannelTask(m_handler, m_user->getUserName(), m_user->getBasic());
    }
}


/////////////////////////////////////////

// 認証が成功した場合
void CSCContents::onAuthSucceeed(void)
{
    // ユーザをログイン状態にする
    m_user->setLogin(true);

    // パスワード永続化
    m_persist->saveInfo(m_user->getNameKey(), m_user->getUserName());
    m_persist->saveInfo(m_user->getBasicKey(), m_user->getBasic());

    // ニックネーム取得タスク
    m_connect->startGetMemberInfoTask(m_handler, m_user->getUserName(), m_user->getBasic());

    // ストリーム受信タスク
    m_connect->startStreamTask(m_handler, m_user->getUserName(), m_user->getBasic());
}

// メッセージ一覧を取得した場合
void CSCContents::onGetMessages(const vector<CMessageData*>& messages)
{
    m_channel->setMessages(m_user->getChannelString(), messages);
}

// メンバー一覧を取得した場合
void CSCContents::onGetMembers(const vector<CMemberData*>& members)
{
    m_channel->setMembers(m_user->getChannelString(), members);
    m_nickTable->addTableFromMembers(members);
}

// チャンネル一覧を取得した場合
void CSCContents::onGetChannels(const vector<CChannelData*>& channels)
{
    m_channel->setChannels(channels);

    if (m_user->getChannelString() == ""){
        m_user->setChannel(m_channel->getFirstChannel());
    }
}

// チャンネル参加成功時
void CSCContents::onJoinChannel(const wxString& channel)
{
    // ユーザの現在のチャンネルを変更
    m_user->setChannel(channel);

    // チャンネル一覧取得タスクの開始
    m_connect->startGetChannelTask(m_handler,
        m_user->getUserName(), m_user->getBasic());
}

// チャンネル離脱成功時
void CSCContents::onPartChannel(const wxString& channel)
{
    // チャンネル情報を削除
    m_channel->popChannel(channel);

    // ユーザの現在のチャンネルを変更
    m_user->setChannel(m_channel->getFirstChannel());
}

// メンバー情報を取得した場合
void CSCContents::onGetMemberStatus(const CMemberData& member)
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
void CSCContents::onGetMessageStream(const CMessageData& message)
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
        m_connect->startGetMemberInfoTask(m_handler, message.m_username, m_user->getBasic());
    }

    // データ追加
    m_channel->pushMessage(message.m_channel, message);
}

// チャンネル参加ストリームを受信
void CSCContents::onGetJoinStream(const wxString& channel, const wxString& name)
{
    // 処理待ちに追加
    CSubscribeData data (channel, name);

    wxString nick = m_nickTable->getNickname(data.m_username);

    // ニックネームが未知の場合、メンバー情報取得タスクの開始
    if (!m_nickTable->isExist(data.m_username)){
        m_connect->startGetMemberInfoTask(m_handler,
            name, m_user->getBasic());
    }

    // メンバーを追加
    m_channel->pushMember(data.m_channel, CMemberData(data.m_username, nick));

    // 自分が参加したとき(別クライアントソフトから)
    if (data.m_username == m_user->getUserName()){

        // チャンネル情報取得タスクの開始
        m_connect->startGetChannelTask(
            m_handler, m_user->getUserName(), m_user->getBasic());
    }
}

// チャンネル離脱ストリームを受信
void CSCContents::onGetPartStream(const wxString& channel, const wxString& name)
{
    CSubscribeData data (channel, name);

    // データ更新
    wxString nick = m_nickTable->getNickname(name);
    m_channel->popMember(data.m_username);

    // ニックネームが未知の時、メンバー情報取得タスクの開始
    if (!m_nickTable->isExist(name)){
        m_connect->startGetMemberInfoTask(m_handler, name, m_user->getBasic());
    }
}

// チャンネル情報更新ストリームを受信
void CSCContents::onGetChannelStream(const CChannelData& channel)
{
    m_channel->setChannel(channel);
}

// ユーザ情報更新ストリームの受信
void CSCContents::onGetUserStream(const CMemberData& member)
{
    m_channel->updateMember(member);
    (*m_nickTable)[member.m_name] = member.m_nick;
}
