#include "MenuFile.hpp"

namespace CornStarch
{;

CMenuFile::CMenuFile(void)
{
}


CMenuFile::~CMenuFile(void)
{
}


///////////////////////////////////


void CMenuFile::init(void)
{
    setTitle(wxT("ファイル(&F)"));
    append(
        MENU_FILE_QUIT,
        wxT("終了(&X)\tAlt-X"));
}

}