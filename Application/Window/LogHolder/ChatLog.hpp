#pragma once
#include <wx/string.h>
#include "../../DataStruct/MemberData.hpp"
#include "../../DataStruct/MessageData.hpp"
#include "../../DataStruct/SubscribeData.hpp"
#include "../../DataStruct/ChannelData.hpp"

namespace CornStarch
{
;

// チャットのログを管理
class CChatLog
{
    wxString m_ServiceName;
public:
    // チャットログのタイプ
    enum LOG_TYPE
    {
        LOG_MESSAGE, LOG_JOIN, LOG_PART, LOG_TOPIC, LOG_USER, LOG_INVITE,
        LOG_KICK
    };

protected:
    LOG_TYPE m_type; // ログのタイプ

public:
    CChatLog(void);
    virtual ~CChatLog(void);

    // ログの種類を取得
    LOG_TYPE getLogType(void) const;

    // 本名に対応するニックネームが未知か
    virtual bool isUnknownNick(const wxString& name) const;

    // ニックネームを更新する
    virtual void updateNick(const wxString& nick);

    wxString getServiceName() const
    {
        return m_ServiceName;
    }

    void setServiceName(wxString serviceName)
    {
        m_ServiceName = serviceName;
    }
};

}
