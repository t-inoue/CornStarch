/*
 * SCConnectionContents.h
 *
 *  Created on: 2012/07/19
 *      Author: yasuo_tanaka
 */

#ifndef SCCONNECTIONCONTENTS_H_
#define SCCONNECTIONCONTENTS_H_

#include "ConnectionContents.hpp"

class CSCConnectionContents: public CConnectionContents {
public:
	CSCConnectionContents();
	virtual ~CSCConnectionContents();


	void init(wxEvtHandler* handler);
};

#endif /* SCCONNECTIONCONTENTS_H_ */
