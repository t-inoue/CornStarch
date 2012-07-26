//#include "IRCService.h"
//#include "IRCUser.hpp"
//#include "IRCConnection.h"
//namespace CornStarch
//{
//namespace IRC
//{
//CIRCService::CIRCService()
//{
//
//}
//
//CIRCService::~CIRCService()
//{
//}
//
//void CIRCService::init(wxEvtHandler* handler)
//{
//
//    CChatServiceBase::init(handler);
//
//    m_connect = new CIRCConnection();
//    m_connect->init(m_id, m_handler);
//
//    m_user = new CIRCUser();
//    m_user->init();
//    m_user->setChannel("");
//
//    // IRCのチャットタイプ
//    m_type = CChatServiceBase::IRC;
//
//}
//void CIRCService::onAuthSucceeed(void)
//{
//    CChatServiceBase::onAuthSucceeed();
//    vector<wxString>::iterator it = savedChannels.begin();
//    while (it != savedChannels.end()){
//        joinChannel(*it);
//        it++;
//    }
//}
//}
//}
