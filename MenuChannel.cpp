#include "MenuChannel.hpp"


CMenuChannel::CMenuChannel(void)
{
}


CMenuChannel::~CMenuChannel(void)
{
}


///////////////////////////////////


void CMenuChannel::init(void)
{
    setTitle(wxT("チャンネル(&C)"));
    append(
        MENU_CHANNEL_JOIN,
        wxT("チャンネルに参加"));
    append(
        MENU_CHANNEL_PART,
        wxT("チャンネルから離脱"));
}