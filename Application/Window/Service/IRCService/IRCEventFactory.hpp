#ifndef IRCEVENTFACTORY_HPP_
#define IRCEVENTFACTORY_HPP_

#include "IRCMessageData.hpp"
#include "../Event/ConnectionEventBase.hpp"
namespace CornStarch
{
;
namespace IRC
{
;
class CIRCEventFactory
{
    // 名前一覧のバッファ
    wxString m_namesBuffer;
    // 名前一覧の名前をバッファに追加します。
    void addNames(const CIRCMessageData& param);
    // ニックネームイベントを生成します。
    CConnectionEventBase* createNickMessageEvent(
            const CIRCMessageData& message) const;
    // トピックイベントを生成します。
    CConnectionEventBase* createTopicMessageEvent(
            const CIRCMessageData& message) const;
    // 参加イベントを生成します。
    CConnectionEventBase* createJoinMessageEvent(
            const CIRCMessageData& message) const;
    // 離脱イベントを作成します。
    CConnectionEventBase* createPartMessageEvent(
            const CIRCMessageData& message) const;
    // メッセージのイベントを作成します。
    CConnectionEventBase* createPrivateMessageEvent(
            const CIRCMessageData& message) const;
    //　名前一覧取得のイベントを作成します。
    CConnectionEventBase* createNamesEvent(const CIRCMessageData& message);
    // 招待イベントを作成します。
    CConnectionEventBase* createInviteEvent(
            const CIRCMessageData& message) const;
    // キックイベントを作成します。
    CConnectionEventBase* createKickEvent(const CIRCMessageData& message) const;
    // トピック取得のイベントを作成します。
    CConnectionEventBase* createTopicEvent(
            const CIRCMessageData& message) const;
public:
    CIRCEventFactory():m_namesBuffer("")
    {
    }
    virtual ~CIRCEventFactory()
    {
    }
    CConnectionEventBase* Create(const CIRCMessageData& message);
};
}
}
#endif /* IRCEVENTFACTORY_HPP_ */
