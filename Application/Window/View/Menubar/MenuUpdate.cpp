#include "MenuUpdate.hpp"

namespace CornStarch
{;

CMenuUpdate::CMenuUpdate(void)
{
}


CMenuUpdate::~CMenuUpdate(void)
{
}


///////////////////////////////////


void CMenuUpdate::init(void)
{
    setTitle(wxT("更新(&U)"));
    append(
        MENU_UPDATE,
        wxT("更新\tF5"));
}

}