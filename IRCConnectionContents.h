/*
 * IRCConnectionContents.h
 *
 *  Created on: 2012/07/19
 *      Author: yasuo_tanaka
 */

#ifndef IRCCONNECTIONCONTENTS_H_
#define IRCCONNECTIONCONTENTS_H_

#include "ConnectionContents.hpp"
namespace CornStarch {
namespace IRC {
class CIRCConnectionContents: public CConnectionContents {
public:
	CIRCConnectionContents();
	virtual ~CIRCConnectionContents();

	void init(wxEvtHandler* handler);

};
}
}
#endif /* IRCCONNECTIONCONTENTS_H_ */
