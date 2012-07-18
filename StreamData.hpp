#pragma once
#include "MemberData.hpp"
#include "ChannelData.hpp"
#include "MessageData.hpp"
#include "SubscribeData.hpp"

// ストリームの内容を表すクラス
class CStreamData
{
public:

    // ストリームのタイプ
    enum TYPE{
        TYPE_MESSAGE_ADD, // メッセージが投稿された
        TYPE_CHANNEL_MEMBER_SUB, // チャンネルから人が消えた
        TYPE_CHANNEL_MEMBER_ADD, // チャンネルに人が参加した
        TYPE_CHANNEL_UPDATE, // チャンネル情報が更新された
        TYPE_USER_UPDATE, // ユーザ情報が変更された
        TYPE_UNKNOWN, // 解析できない
        TYPE_NOSTREAM, // ストリームが来ていない
    };

    TYPE m_type; // ストリームタイプ
    CMemberData m_member; // メンバー
    CChannelData m_channel; // チャンネル
    CMessageData m_message; // メッセージ
    CSubscribeData m_sub; // チャンネル入退出
};

