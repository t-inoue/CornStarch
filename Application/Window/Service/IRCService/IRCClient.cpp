#include "IRCClient.hpp"
#include "Task/IRCStartTask.hpp"
#include "Task/IRCReceiveTask.hpp"
#include "Task/IRCSendTask.hpp"

namespace CornStarch
{
;
namespace IRC
{
;
using namespace std;

CIRCClient::CIRCClient() :
        m_handler(NULL), m_isClosing(false), m_receiveTask(NULL)
{
    m_commandQueue = new wxMessageQueue<wxString>();
 //   m_mutex = new wxMutex();
}

CIRCClient::~CIRCClient(void)
{
    delete m_commandQueue;
  //  delete m_mutex;
}
void CIRCClient::init(int connectionId,wxEvtHandler* handler)
{
    CSocketClient::init();
    m_connectionId = connectionId;
    m_handler = handler;
}
void CIRCClient::startAsync(const wxString& userName,
        const wxString& password)
{
    if (m_socket->IsConnected()){
        return;
    }

    CIRCStartTask *task = new CIRCStartTask(wxTHREAD_JOINABLE);
    task->init(m_connectionId,m_handler,this);
    task->setUserName(userName);
    task->setPassword(password);
    startThread(task);

    task->Wait();
    delete task;

    CIRCSendTask *sendTask = new CIRCSendTask(wxTHREAD_JOINABLE);
    sendTask->init(m_connectionId,m_handler,this);
    m_sendTask = sendTask;
    startThread(sendTask);

    CIRCReceiveTask *receiveTask = new CIRCReceiveTask(wxTHREAD_JOINABLE);
    receiveTask->init(m_connectionId,m_handler,this);
    m_receiveTask = receiveTask;
    startThread(receiveTask);
//    Thread *thread = new Thread(this, &CIRCClient::connect, pass);
//    thread->start();
}

//void CIRCClient::connect(const wxString& userName,
//        const wxString& password)
//{
//    wxString pass(
//            wxString::Format(wxT( "PASS %s\r\nNICK %s\r\nUSER %s * 0 :%s\r\n"),
//                    password.c_str(), userName.c_str(), userName.c_str(),
//                    userName.c_str()));
//
//    setPort(this->m_port);
//    setUrl(this->m_host);
//    CSocketClient::connect();
//    //　IRCへの接続
//    sendCommand(pass);
//
//    recieveThread = new Thread(this, &CIRCClient::receiveLoop,wxTHREAD_JOINABLE);
//    recieveThread->start();
//}
void CIRCClient::addCommandQueue(const wxString& content)
{
    m_commandQueue->Post(content);
//    m_mutex->Lock();
//    send(content);
//    m_mutex->Unlock();
}
void CIRCClient::sendCommand(const wxString& command)
{
    send(command);
}
void CIRCClient::startThread(wxThread* task)
{

    if (task->Create() != wxTHREAD_NO_ERROR){
        delete task;
        task = NULL;
        return;
    }

    // 別スレッドを走らせる
    if (task->Run() != wxTHREAD_NO_ERROR){
        delete task;
        task = NULL;
        return;
    }
}
//void CIRCClient::receiveLoop()
//{
//    CIRCParser parser;
//    while (m_socket->IsConnected()){
//        this->m_buffer = "";
//
//        receive();
//        if (this->m_buffer != ""){
//            vector<string> messages = CStringUtility::split(this->m_buffer,
//                    "\n");
//            for (int i = 0; i < messages.size(); i++){
//                if (messages[i].find(string("PI") + "NG") == 0){
//                    string pingValue =
//                            CStringUtility::split(messages[i], ":")[1];
//                    pong(pingValue);
//                } else{
//                    CConnectionEventBase* event = parser.parse(messages[i]);
//                    if (event != NULL){
//                        event->setConnectionId(m_connectionId);
//                        wxQueueEvent(m_handler, event);
//                    }
//                }
//            }
//        }
//        wxUsleep(100);
//    }
//    if (m_isClosing != true){
//        CAuthEvent* event = new CAuthEvent();
//        event->setAuthResult(false);
//        event->SetEventType(myEVT_THREAD_GET_PING); // イベントの種類をセット
//        event->setConnectionId(m_connectionId);
//        wxQueueEvent(m_handler, event);
//    }
//}
//void CIRCClient::pong(const wxString& value)
//{
//    wxString content(wxString::Format(wxT("PONG %s\r\n"), value));
//    sendCommand(content);
//}
void CIRCClient::quitAsync(void)
{
    wxString content("QUIT\r\n");

    Thread *thread =new Thread(this, &CIRCClient::addCommandQueue,content);
    thread->start();
}
void CIRCClient::disconnect(void)
{
    if (m_isClosing == false){
        m_isClosing = true;
        this->close();
        if (m_receiveTask != NULL&& m_receiveTask->IsAlive()){
            if (m_receiveTask->IsRunning()){
                m_receiveTask->Wait();
                delete m_receiveTask;
            }
        }
    }
}
wxString CIRCClient::recieveData()
{
    this->m_buffer = "";
    this->receive();
    return this->m_buffer;
}
void CIRCClient::joinAsync(const wxString& channelName)
{
    wxString content(
            wxString::Format(wxString("JO") + wxString("IN %s\r\n"),
                    channelName));
    Thread *thread =new Thread(this, &CIRCClient::addCommandQueue,content);
    thread->start();
}
void CIRCClient::partAsync(const wxString& channelName)
{
    wxString content(
            wxString::Format(wxString("PA") + wxString("RT %s\r\n"),
                    channelName));
    Thread *thread =new Thread(this, &CIRCClient::addCommandQueue,content);
    thread->start();
}
void CIRCClient::getTopicAsync(const wxString& channelName)
{
    wxString content(wxString::Format(wxT("TOPIC %s\r\n"), channelName));
    Thread *thread =new Thread(this, &CIRCClient::addCommandQueue,content);
    thread->start();

}
void CIRCClient::getNamesAsync(const wxString& channelName)
{
    wxString content(wxString::Format(wxT("NAMES %s\r\n"), channelName));
    Thread *thread =new Thread(this, &CIRCClient::addCommandQueue,content);
    thread->start();
}

void CIRCClient::sendMessageAsync(const wxString& target, const wxString& content)
{
    wxString contentWxString(
            wxString::Format(wxString("PRIV") + wxString("MSG %s %s\r\n"),
                    target, content));
    Thread *thread =new Thread(this, &CIRCClient::addCommandQueue,contentWxString);
    thread->start();
}
void CIRCClient::sendNoticeAsync(const wxString& target, const wxString& content)
{
    wxString contentWxString(
            wxString::Format(wxT("NOTICE %s %s\r\n"), target, content));
    Thread *thread =new Thread(this, &CIRCClient::addCommandQueue,contentWxString);
    thread->start();
}
void CIRCClient::changeTopicAsync(const wxString& channelName,
        const wxString& content)
{
    wxString contentWxString(
            wxString::Format(wxT("TOPIC %s %s\r\n"), channelName, content));
    Thread *thread =new Thread(this, &CIRCClient::addCommandQueue,contentWxString);
    thread->start();
}
void CIRCClient::changeNicknameAsync(const wxString& content)
{
    wxString contentWxString(wxString::Format(wxT("NICK %s\r\n"), content));
    Thread *thread =new Thread(this, &CIRCClient::addCommandQueue,contentWxString);
    thread->start();

}
}
} /* namespace CornStarch */
