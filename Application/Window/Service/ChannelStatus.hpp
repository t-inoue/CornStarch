﻿#pragma once
#include "MessageVec.hpp"
#include "MemberVec.hpp"

namespace CornStarch
{
;

// チャンネルの内部状態(誰がいるかやメッセージなど)を管理
class CChannelStatus
{
private:
    wxString m_topic; // トピック
    CMessageVec* m_messages; // メッセージ一覧
    CMemberVec* m_members; // メンバー一覧
    wxString m_channelName;
    int m_unreadCount;

public:
    CChannelStatus(void);
    ~CChannelStatus(void);

    // 初期化を行う
    void init(void);

    // トピックをセットする
    void setTopic(const wxString& topic);

    // トピックを取得する
    wxString getTopic(void) const;

    // メッセージ一覧を取得する
    std::vector<CMessageData*> getMessages(void) const;

    // メンバー一覧を取得する
    std::vector<CMemberData*> getMembers(void) const;

    // メッセージを追加する
    void pushMessage(const CMessageData& message);

    // メンバーを追加する
    void pushMember(const CMemberData& member);

    // メッセージ一覧をセットする
    void setMessages(const std::vector<CMessageData*>& messages);

    // メンバー一覧をセットする
    void setMembers(const std::vector<CMemberData*>& members);

    // メッセージを取得し終えたか
    bool hasReceivedMessage(void) const;

    // メンバを取得し終えたか
    bool hasReceivedMember(void) const;

    // ID不明かつ同じ投稿内容のメッセージがあるか
    bool hasSameMessage(const CMessageData& message) const;

    // 同じ内容のメッセージについてIDを更新
    void updateMessageId(const CMessageData& message);

    // メンバー情報を更新する
    void updateMember(const CMemberData& member);

    // メンバー情報を消す
    void popMember(const wxString& userName);

    // 未読をクリア
    void clearUnreadCount();

    // チャンネル名の取得
    wxString getChannelName() const
    {
        return m_channelName;
    }

    // チャンネル名の設定
    void setChannelName(wxString channelName)
    {
        m_channelName = channelName;
    }
    // 未読数の取得
    int getUnreadCount() const
    {
        return m_unreadCount;
    }

    // 未読数の追加
    void addUnreadCount()
    {
        m_unreadCount++;
    }

};

}
