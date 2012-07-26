#include "MenuServer.hpp"

namespace CornStarch
{;

CMenuServer::CMenuServer(void)
{
}


CMenuServer::~CMenuServer(void)
{
}


///////////////////////////////////


void CMenuServer::init(void)
{
    setTitle(wxT("サーバ(&S)"));
    append(
        MENU_SERVER_SC_ADD,
        wxT("StarChatサーバの追加"));
    append(
        MENU_SERVER_IRC_ADD,
        wxT("IRCサーバの追加"));
    append(
        MENU_SERVER_DELETE,
        wxT("サーバの削除"));
    append(
        MENU_SERVER_NICK_CHANGE,
        wxT("ニックネーム変更"));
}

}