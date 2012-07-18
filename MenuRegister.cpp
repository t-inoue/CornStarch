#include "MenuRegister.hpp"

CMenuRegister::CMenuRegister(void)
{
}


CMenuRegister::~CMenuRegister(void)
{
}


///////////////////////////////////


void CMenuRegister::init(void)
{
    setTitle(wxT("登録(&R)"));
    append(
        MENU_REGISTER_ADD,
        wxT("登録"));
}
