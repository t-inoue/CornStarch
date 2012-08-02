

#ifndef _IRCParser_h
#define _IRCParser_h
#include <wx/wxprec.h>
#include <wx/wx.h>
#include <string>
#include <iostream>
#include <vector>
#include "StringUtility.hpp"

#include "IRCMessageData.hpp"

using namespace std;

namespace CornStarch
{
namespace IRC
{
//IRC用のイベントから呼び出します。
class CIRCParser
{
	// メッセージに設定するId
	int m_messageId;

public:

	CIRCParser();
	virtual ~CIRCParser(void);
	CIRCMessageData parse(const wxString& content);

};
}
}

#endif
