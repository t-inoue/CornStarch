#include "MainWindow.hpp"
#include "wx/event.h"

// typedef
typedef void (wxEvtHandler::*MyEventFunction)(CAuthEvent&);
typedef void (wxEvtHandler::*delPartEvtFunction)(wxThreadEvent&);
typedef void (wxEvtHandler::*GetMemberEvtFunc)(CGetMemberEvent&);
typedef void (wxEvtHandler::*GetChannelEvtFunc)(CGetChannelEvent&);
typedef void (wxEvtHandler::*GetMessageEvtFunc)(CGetMessageEvent&);
typedef void (wxEvtHandler::*GetMemberInfoEvtFunc)(CGetMemberInfoEvent&);
typedef void (wxEvtHandler::*GetMsgStreamEvtFunc)(CMsgStreamEvent&);
typedef void (wxEvtHandler::*GetMemStreamEvtFunc)(CUserStreamEvent&);
typedef void (wxEvtHandler::*GetChStreamEvtFunc)(CChannelStreamEvent&);
typedef void (wxEvtHandler::*GetChPartStreamEvtFunc)(CPartStreamEvent&);
typedef void (wxEvtHandler::*GetChJoinStreamEvtFunc)(CJoinStreamEvent&);
typedef void (wxEvtHandler::*JoinEvtFunc)(CJoinEvent&);

// define
wxDEFINE_EVENT(myEVT_THREAD_GET_PING, CAuthEvent);
wxDEFINE_EVENT(myEVT_THREAD_DELETE_PART, wxThreadEvent);
wxDEFINE_EVENT(myEVT_THREAD_GET_CHANNEL, CGetChannelEvent);
wxDEFINE_EVENT(myEVT_THREAD_GET_MESSAGE, CGetMessageEvent);
wxDEFINE_EVENT(myEVT_THREAD_GET_MEMBER, CGetMemberEvent);
wxDEFINE_EVENT(myEVT_THREAD_GET_MEMBER_INFO, CGetMemberInfoEvent);
wxDEFINE_EVENT(myEVT_THREAD_STREAM_MSG_ADD, CMsgStreamEvent);
wxDEFINE_EVENT(myEVT_THREAD_STREAM_CH_JOIN, CJoinStreamEvent);
wxDEFINE_EVENT(myEVT_THREAD_STREAM_CH_PART, CPartStreamEvent);
wxDEFINE_EVENT(myEVT_THREAD_STREAM_CH_UPDATE, CChannelStreamEvent);
wxDEFINE_EVENT(myEVT_THREAD_STREAM_USER_UPDATE, CUserStreamEvent);
wxDEFINE_EVENT(myEVT_THREAD_PUT_JOIN, CJoinEvent);
wxDEFINE_EVENT(myEVT_THREAD_POST_MESSAGE, wxThreadEvent);

// イベントハンドラ
#define MyEventHandler(func) wxEVENT_HANDLER_CAST(MyEventFunction, func)
#define delPartEventHandler(func) wxEVENT_HANDLER_CAST(delPartEvtFunction, func)
#define getMemberEventHandler(func) wxEVENT_HANDLER_CAST(GetMemberEvtFunc, func)
#define getChannelEventHandler(func) wxEVENT_HANDLER_CAST(GetChannelEvtFunc, func)
#define getMessageEventHandler(func) wxEVENT_HANDLER_CAST(GetMessageEvtFunc, func)
#define getMemberInfoEventHandler(func) wxEVENT_HANDLER_CAST(GetMemberInfoEvtFunc, func)
#define getMsgStreamEventHandler(func) wxEVENT_HANDLER_CAST(GetMsgStreamEvtFunc, func)
#define getMemStreamEventHandler(func) wxEVENT_HANDLER_CAST(GetMemStreamEvtFunc, func)
#define getChStreamEventHandler(func) wxEVENT_HANDLER_CAST(GetChStreamEvtFunc, func)
#define getChJoinStreamEventHandler(func) wxEVENT_HANDLER_CAST(GetChJoinStreamEvtFunc, func)
#define getChPartStreamEventHandler(func) wxEVENT_HANDLER_CAST(GetChPartStreamEvtFunc, func)
#define joinEventHandler(func) wxEVENT_HANDLER_CAST(JoinEvtFunc, func)

#define EVT_DEL_PART(evt, id, func) wx__DECLARE_EVT1(evt, id, delPartEventHandler(func))
#define EVT_GET_AUTH(evt, id, func) wx__DECLARE_EVT1(evt, id, MyEventHandler(func))
#define EVT_GET_MEMBER(evt, id, func) wx__DECLARE_EVT1(evt, id, getMemberEventHandler(func))
#define EVT_GET_CHANNEL(evt, id, func) wx__DECLARE_EVT1(evt, id, getChannelEventHandler(func))
#define EVT_GET_MESSAGE(evt, id, func) wx__DECLARE_EVT1(evt, id, getMessageEventHandler(func))
#define EVT_GET_MEMBER_INFO(evt, id, func) wx__DECLARE_EVT1(evt, id, getMemberInfoEventHandler(func))
#define EVT_GET_MSG_STREAM(evt, id, func) wx__DECLARE_EVT1(evt, id, getMsgStreamEventHandler(func))
#define EVT_GET_MEM_STREAM(evt, id, func) wx__DECLARE_EVT1(evt, id, getMemStreamEventHandler(func))
#define EVT_GET_CH_STREAM(evt, id, func) wx__DECLARE_EVT1(evt, id, getChStreamEventHandler(func))
#define EVT_GET_JOIN_STREAM(evt, id, func) wx__DECLARE_EVT1(evt, id, getChJoinStreamEventHandler(func))
#define EVT_GET_PART_STREAM(evt, id, func) wx__DECLARE_EVT1(evt, id, getChPartStreamEventHandler(func))
#define EVT_PUT_JOIN(evt, id, func) wx__DECLARE_EVT1(evt, id, joinEventHandler(func))

// イベントテーブルの登録
BEGIN_EVENT_TABLE(CMainWindow, wxFrame)

    // メニューバー
    EVT_MENU(CMenuPart::MENU_FILE_QUIT, CMainWindow::onQuit) // 終了
    EVT_MENU(CMenuPart::MENU_REGISTER_ADD, CMainWindow::onRegister) // 登録
    EVT_MENU(CMenuPart::MENU_FILE_LOGOUT, CMainWindow::onLogout) // ログアウトして終了
    EVT_MENU(CMenuPart::MENU_CHANNEL_JOIN, CMainWindow::onJoin) // チャンネルに参加
    EVT_MENU(CMenuPart::MENU_CHANNEL_PART, CMainWindow::onPart) // チャンネルから離脱
    EVT_MENU(CMenuPart::MENU_UPDATE, CMainWindow::onUpdateDisplay) // 更新

    // 通信による結果を受け取ったとき
    EVT_GET_AUTH(myEVT_THREAD_GET_PING, wxID_ANY, CMainWindow::onGetAuth)
    EVT_DEL_PART(myEVT_THREAD_DELETE_PART, wxID_ANY, CMainWindow::onPartChannel)
    EVT_GET_MEMBER(myEVT_THREAD_GET_MEMBER, wxID_ANY, CMainWindow::onGetMembers)
    EVT_GET_MESSAGE(myEVT_THREAD_GET_MESSAGE, wxID_ANY, CMainWindow::onGetMessages)
    EVT_GET_CHANNEL(myEVT_THREAD_GET_CHANNEL, wxID_ANY, CMainWindow::onGetChannels)
    EVT_GET_MEMBER_INFO(myEVT_THREAD_GET_MEMBER_INFO, wxID_ANY, CMainWindow::onGetMemberInfo)    
    EVT_GET_MSG_STREAM(myEVT_THREAD_STREAM_MSG_ADD, wxID_ANY, CMainWindow::onMsgStream)
    EVT_GET_MEM_STREAM(myEVT_THREAD_STREAM_USER_UPDATE, wxID_ANY, CMainWindow::onUserStream)
    EVT_GET_CH_STREAM(myEVT_THREAD_STREAM_CH_UPDATE, wxID_ANY, CMainWindow::onChannelStream)
    EVT_GET_JOIN_STREAM(myEVT_THREAD_STREAM_CH_JOIN, wxID_ANY, CMainWindow::onJoinStream)
    EVT_GET_PART_STREAM(myEVT_THREAD_STREAM_CH_PART, wxID_ANY, CMainWindow::onPartStream)
    EVT_PUT_JOIN(myEVT_THREAD_PUT_JOIN, wxID_ANY, CMainWindow::onJoinChannel)
        
    // ウィンドウサイズ変更
    EVT_SIZE(CMainWindow::OnSize)

END_EVENT_TABLE();

