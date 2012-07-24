
#ifndef IRCCONNECTIONCONTENTS_H_
#define IRCCONNECTIONCONTENTS_H_

#include "ChatServiceBase.hpp"
namespace CornStarch
{
namespace IRC
{
//IRC用の通信モデルを保持するクラス
class CIRCService: public CChatServiceBase
{
public:
	CIRCService();
	virtual ~CIRCService();

	//初期化します。
	void init(wxEvtHandler* handler);

};
}
}
#endif /* IRCCONNECTIONCONTENTS_H_ */
