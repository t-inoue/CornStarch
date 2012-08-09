#include "MenuServer.hpp"

namespace CornStarch
{
;

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
    append(MENU_SERVER_ADD, wxT("サーバの追加"));
    append(MENU_SERVER_DELETE, wxT("サーバの削除"));
    append(MENU_SERVER_NICK_CHANGE, wxT("ニックネーム変更"));
}

}
