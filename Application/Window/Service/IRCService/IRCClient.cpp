#include "IRCClient.hpp"
#include "Task/IRCStartTask.hpp"
#include "Task/IRCSendTask.hpp"
#include "IRCCommand.hpp"
#include "Task/IRCReceiveTask.hpp"
namespace CornStarch
{
;
namespace IRC
{
;
using namespace std;

CIRCClient::CIRCClient() :
        m_receiveTask(NULL), m_sendTask(NULL), m_isClosing(false), m_handler(
                NULL)
{
    m_commandQueue = new wxMessageQueue<wxString>();
}

CIRCClient::~CIRCClient(void)
{
    delete m_conenctTask;
    delete m_commandQueue;
    delete m_receiveTask;
    delete m_sendTask;
}
void CIRCClient::init(int connectionId, wxEvtHandler* handler)
{
    CSocketClient::init();
    m_connectionId = connectionId;
    m_handler = handler;
}
void CIRCClient::startAsync(const wxString& userName, const wxString& password)
{
    if (m_socket->IsConnected()){
        return;
    }

    // 通信開始用スレッド
    CIRCStartTask *task = new CIRCStartTask(wxTHREAD_JOINABLE);
    task->init(m_connectionId, m_handler, this);
    task->setUserName(userName);
    task->setPassword(password);
    m_conenctTask = task;

    // 送信用スレッド
    CIRCSendTask *sendTask = new CIRCSendTask(wxTHREAD_JOINABLE);
    sendTask->init(m_connectionId, m_handler, this);
    m_sendTask = sendTask;

    //　受信用スレッド
    CIRCReceiveTask *receiveTask = new CIRCReceiveTask(wxTHREAD_JOINABLE);
    receiveTask->init(m_connectionId, m_handler, this);
    m_receiveTask = receiveTask;

    task->continueWith(sendTask);
    task->continueWith(receiveTask);
    startThread(task);
}

void CIRCClient::addCommandQueue(const wxString& content)
{
    m_commandQueue->Post(content);
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
void CIRCClient::quitAsync(void)
{
    wxString content(IRCCommand::QUIT);
    addCommandQueue(content);
}
void CIRCClient::disconnect(void)
{
    if (m_isClosing == false){
        quitAsync();
        m_isClosing = true;
        //スレッドの終了待機
        if (m_conenctTask != NULL && m_conenctTask->IsAlive()){
                if (m_conenctTask->IsRunning()){
                    m_conenctTask->Delete();
                }
            }
        if (m_sendTask != NULL && m_sendTask->IsAlive()){
               if (m_sendTask->IsRunning()){
                   m_sendTask->Wait();
               }
           }
        if (m_receiveTask != NULL && m_receiveTask->IsAlive()){
            if (m_receiveTask->IsRunning()){
                m_receiveTask->Wait();
            }
        }

        this->close();
    }
}
wxString CIRCClient::recieveData()
{
    this->m_buffer = "";
    this->receive(100);
    return this->m_buffer;
}
void CIRCClient::joinAsync(const wxString& channelName)
{
    wxString content(
            wxString::Format(wxT("%s %s"),IRCCommand::JOIN, channelName));
    addCommandQueue(content);
}
void CIRCClient::partAsync(const wxString& channelName)
{
    wxString content(
            wxString::Format(wxT("%s %s"),IRCCommand::PART, channelName));
    addCommandQueue(content);
}
void CIRCClient::getTopicAsync(const wxString& channelName)
{
    wxString content(wxString::Format(wxT("%s %s") ,IRCCommand::TOPIC, channelName));
    addCommandQueue(content);

}
void CIRCClient::getNamesAsync(const wxString& channelName)
{
    wxString content(wxString::Format(wxT("%s %s"),IRCCommand::NAMES, channelName));
    addCommandQueue(content);
}

void CIRCClient::sendMessageAsync(const wxString& target,
        const wxString& content)
{
    wxString contentWxString(
            wxString::Format(wxT("%s %s %s"),IRCCommand::PRIVMSG, target,
                    content));
    addCommandQueue(contentWxString);
}
void CIRCClient::sendNoticeAsync(const wxString& target,
        const wxString& content)
{
    wxString contentWxString(
            wxString::Format(wxT("%s %s %s"),IRCCommand::NOTICE, target, content));

    addCommandQueue(contentWxString);
}
void CIRCClient::changeTopicAsync(const wxString& channelName,
        const wxString& content)
{
    wxString contentWxString(
            wxString::Format(wxT("%s %s %s"),IRCCommand::TOPIC, channelName, content));
    addCommandQueue(contentWxString);
}
void CIRCClient::changeNicknameAsync(const wxString& content)
{
    wxString contentWxString(wxString::Format(wxT("%s %s"),IRCCommand::NICK, content));
    addCommandQueue(contentWxString);
}
}
} /* namespace CornStarch */
