#ifndef SCCONNECTIONCONTENTS_H_
#define SCCONNECTIONCONTENTS_H_

#include "../ChatServiceBase.hpp"
#include "SCConnection.hpp"
#include "SCUser.hpp"

namespace CornStarch
{;
namespace StarChat
{;

class CSCService: public CChatServiceBase {
public:
	CSCService();
	virtual ~CSCService();

	//初期化します。
	void init(wxEvtHandler* handler);

	//再接続します。
	void reconnect(void);

};

}
}
#endif /* SCCONNECTIONCONTENTS_H_ */
