#include "MessageVec.hpp"

using namespace std;

CMessageVec::CMessageVec(void)
{
}


CMessageVec::~CMessageVec(void)
{
    deleteAllMessages();
}


//////////////////////////////////////////////////////////////////////


// メッセージを追加する
void CMessageVec::setMessages(const vector<CMessageData*>& messages)
{
    // 全メッセージを削除
    deleteAllMessages();

    // 各メッセージを追加
    size_t length = messages.size();
    for (size_t i = 0; i < length; i++){
        push(*messages[i]);
    }
}

// メッセージを一つ追加する
void CMessageVec::push(const CMessageData& message)
{
    // メッセージを追加
    CMessageData* data = new CMessageData();
    *data = message;
    push_back(data);

    // メッセージ数が最大数だったら
    if (size() > MAX_MESSAGE_NUM){
        delete (*this)[0];
        erase(begin());
    }
}

// メッセージが受信済みか
bool CMessageVec::hasSetMessage(void) const
{
    // 未受信の場合
    if (size() == 0){
        return false;
    }

    return true;
}

// 同一内容のメッセージを含んでいるか
bool CMessageVec::hasSameMessage(const CMessageData& message) const
{
    size_t length = size();
    for (size_t i = 0; i < length; i++){

        // 未知のIDでかつメッセージが同じだったら
        if ((*this)[i]->m_id == -1 && (*this)[i]->m_body == message.m_body){
            return true;
        }
    }

    return false;
}

// メッセージのIDを更新する
void CMessageVec::updateMessageId(const CMessageData& message)
{
    size_t length = size();
    for (size_t i = 0; i < length; i++){

        // IDが未知で本文が同じだったら
        if ((*this)[i]->m_id == -1 && (*this)[i]->m_body == message.m_body){
            (*this)[i]->m_id = message.m_id;
            return;
        }
    }
}

// 全メッセージを削除する
void CMessageVec::deleteAllMessages(void)
{
    size_t length = size();
    for (size_t i = 0; i < length; i++){
        delete (*this)[i];
    }
    clear();
}
