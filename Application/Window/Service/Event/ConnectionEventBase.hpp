#ifndef CONNECTIONEVENTBASE_HPP_
#define CONNECTIONEVENTBASE_HPP_

#include <wx/wxprec.h>
#include <wx/wx.h>
#include "../../../DataStruct/MemberData.hpp"
#include "../../../DataStruct/StreamData.hpp"
#include "../../../DataStruct/ChannelData.hpp"
#include "../../../DataStruct/MessageData.hpp"

namespace CornStarch
{;

// 通信から発生するイベントの基底クラス
class CConnectionEventBase:public wxThreadEvent
{
	// 通信ID
	int m_connectionId;
public:
	CConnectionEventBase();
	CConnectionEventBase(wxEventType eventType, int id );
	virtual ~CConnectionEventBase();

	// 通信IDを取得
	int getConnectionId() const
	{
		return m_connectionId;
	}
	// 通信ID設定
	void setConnectionId(int connectionId)
	{
		m_connectionId = connectionId;
	}


};

}

#endif /* CONNECTIONEVENTBASE_HPP_ */
