
#ifndef IRCCONNECTIONCONTENTS_H_
#define IRCCONNECTIONCONTENTS_H_

#include "ConnectionContents.hpp"
namespace CornStarch
{
namespace IRC
{
//IRC用の通信モデルを保持するクラス
class CIRCConnectionContents: public CConnectionContents
{
public:
	CIRCConnectionContents();
	virtual ~CIRCConnectionContents();

	//初期化します。
	void init(wxEvtHandler* handler);

};
}
}
#endif /* IRCCONNECTIONCONTENTS_H_ */
