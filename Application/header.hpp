#pragma once

#pragma warning(disable:4996) // scanf等のセキュアじゃない関数のwarningを消す

#ifdef _DEBUG
#pragma comment(lib, "wxmsw29ud_core.lib")
#pragma comment(lib, "wxmsw29ud_adv.lib")
#pragma comment(lib, "wxbase29ud_xml.lib")
#pragma comment(lib, "wxbase29ud.lib")
#pragma comment(lib, "wxtiffd.lib")
#pragma comment(lib, "wxjpegd.lib")
#pragma comment(lib, "wxpngd.lib")
#pragma comment(lib, "wxzlibd.lib")
#pragma comment(lib, "wxregexud.lib")
#pragma comment(lib, "wxexpatd.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "rpcrt4.lib")
#pragma comment(lib, "wsock32.lib")
#pragma comment(lib, "odbc32.lib")
#pragma comment(lib, "wininet.lib")
#pragma comment(lib, "wxbase29ud_net.lib")


#else
#pragma comment(lib, "wxmsw29u_core.lib")
#pragma comment(lib, "wxmsw29u_adv.lib")
#pragma comment(lib, "wxbase29u_xml.lib")
#pragma comment(lib, "wxbase29u.lib")
#pragma comment(lib, "wxtiff.lib")
#pragma comment(lib, "wxjpeg.lib")
#pragma comment(lib, "wxpng.lib")
#pragma comment(lib, "wxzlib.lib")
#pragma comment(lib, "wxregexu.lib")
#pragma comment(lib, "wxexpat.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "rpcrt4.lib")
#pragma comment(lib, "wsock32.lib")
#pragma comment(lib, "odbc32.lib")
#pragma comment(lib, "wininet.lib")
#pragma comment(lib, "wxbase29u_net.lib")


#endif