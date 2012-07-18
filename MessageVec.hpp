#pragma once
#include <vector>
#include "MessageData.hpp"

// メッセージ一覧を管理する
class CMessageVec : public std::vector<CMessageData*>
{
private:
    static const size_t MAX_MESSAGE_NUM = 300; // メッセージの最大保有数

public:
    CMessageVec(void);
    ~CMessageVec(void);

    // メッセージを追加する
    void setMessages(const std::vector<CMessageData*>& messages);

    // メッセージを一つ追加する
    void push(const CMessageData& message);

    // メッセージが受信済みか
    bool hasSetMessage(void) const;

    // 同一内容のメッセージを含んでいるか
    bool hasSameMessage(const CMessageData& message) const;

    // ID不明のメッセージのIDを更新する
    void updateMessageId(const CMessageData& message);

    // 全メッセージを削除する
    void deleteAllMessages(void);
};
