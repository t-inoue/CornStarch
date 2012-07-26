#ifndef CONNECTIONEVENTBASE_HPP_
#define CONNECTIONEVENTBASE_HPP_

#include "../../../../../header.hpp"

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
