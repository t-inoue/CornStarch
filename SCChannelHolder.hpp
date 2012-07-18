#pragma once
#include <map>
#include "SCChannelStatus.hpp"
#include "ChannelData.hpp"

// チャンネル一覧を保持する
class CSCChannelHolder
{
private:
    std::map<wxString, CSCChannelStatus*> m_channels; // チャンネル一覧

public:
    CSCChannelHolder(void);
    ~CSCChannelHolder(void);

    // 初期化を行う
    void init(void);

    // チャンネル一覧をセットする
    void setChannels(const std::vector<CChannelData*>& channels);

    // チャンネル一覧を取得する
    std::vector<wxString> getChannels(void) const;

    // 既にチャンネル一覧を取得したか
    bool hasReceivedChannel(void) const;

    // チャンネルを追加する
    void setChannel(const CChannelData& channel);

    // チャンネルを削除する
    void popChannel(const wxString& channel);

    // チャンネル名からtopicを取得する
    wxString getTopic(const wxString& channel);

    // チャンネル一覧のメモリ領域を削除する
    void deleteChannels(void);

    // 一番頭のチャンネルを取得する
    wxString getFirstChannel(void);

    /////////////////////////////////////////////////////////////

    // チャンネルのメッセージ一覧を取得する
    std::vector<CMessageData*> getMessages(const wxString& channel);

    // チャンネルのメンバー一覧を取得する
    std::vector<CMemberData*> getMembers(const wxString& channel);

    // チャンネルのメッセージを追加する
    void pushMessage(const wxString& channel, const CMessageData& message);

    // チャンネルのメンバーを追加する
    void pushMember(const wxString& channel, const CMemberData& member);

    // チャンネルのメッセージ一覧をセットする
    void setMessages(const wxString& channel, const std::vector<CMessageData*>& messages);

    // チャンネルのメンバー一覧をセットする
    void setMembers(const wxString& channel, const std::vector<CMemberData*>& members);

    // メンバーを消す
    void popMember(const wxString& userName);

    // メンバー情報を更新する
    void updateMember(const CMemberData& member);

    // メッセージIDを更新する
    void onUpdateMessageId(const CMessageData& message);
    
    // チャンネルのメッセージ情報を収集したか
    bool hasReceivedMessage(const wxString& channel);

    // チャンネルのメッセージ情報を収集したか
    bool hasReceivedMember(const wxString& channel);

    // 同じメッセージ内容のものがあるか
    bool hasSameMessage(const CMessageData& message);
};

