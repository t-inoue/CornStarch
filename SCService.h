
#ifndef SCCONNECTIONCONTENTS_H_
#define SCCONNECTIONCONTENTS_H_

#include "ChatServiceBase.hpp"

class CSCService: public CChatServiceBase {
public:
	CSCService();
	virtual ~CSCService();

	//初期化します。
	void init(wxEvtHandler* handler);
};

#endif /* SCCONNECTIONCONTENTS_H_ */
