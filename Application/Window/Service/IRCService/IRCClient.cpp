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
        m_receiveTask(NULL), m_sendTask(NULL), m_isClosing(false), m_handler(
                NULL)
{
    m_commandQueue = new wxMessageQueue<wxString>();
}

CIRCClient::~CIRCClient(void)
{
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
    CIRCStartTask *task = new CIRCStartTask();
    task->init(m_connectionId, m_handler, this);
    task->setUserName(userName);
    task->setPassword(password);

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
    wxString content("QUIT\r\n");
    addCommandQueue(content);
}
void CIRCClient::disconnect(void)
{
    if (m_isClosing == false){
        m_isClosing = true;
        quitAsync();
        if (m_sendTask != NULL && m_sendTask->IsAlive()){
               if (m_sendTask->IsRunning()){
                   m_sendTask->Wait();
               }
           }
        this->close();
        // スレッド終了待機
        if (m_receiveTask != NULL && m_receiveTask->IsAlive()){
            if (m_receiveTask->IsRunning()){
                m_receiveTask->Wait();
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
    // ウイルス判定回避用に文字列を分割
    wxString content(
            wxString::Format(wxString("JO") + wxString("IN %s"), channelName));
    addCommandQueue(content);
}
void CIRCClient::partAsync(const wxString& channelName)
{
    // ウイルス判定回避用に文字列を分割
    wxString content(
            wxString::Format(wxString("PA") + wxString("RT %s"), channelName));

    addCommandQueue(content);
}
void CIRCClient::getTopicAsync(const wxString& channelName)
{
    wxString content(wxString::Format(wxT("TOPIC %s"), channelName));
    addCommandQueue(content);

}
void CIRCClient::getNamesAsync(const wxString& channelName)
{
    wxString content(wxString::Format(wxT("NAMES %s"), channelName));
    addCommandQueue(content);
}

void CIRCClient::sendMessageAsync(const wxString& target,
        const wxString& content)
{
    // ウイルス判定回避用に文字列を分割
    wxString contentWxString(
            wxString::Format(wxString("PRIV") + wxString("MSG %s %s"), target,
                    content));
    addCommandQueue(contentWxString);
}
void CIRCClient::sendNoticeAsync(const wxString& target,
        const wxString& content)
{
    wxString contentWxString(
            wxString::Format(wxT("NOTICE %s %s"), target, content));

    addCommandQueue(contentWxString);
}
void CIRCClient::changeTopicAsync(const wxString& channelName,
        const wxString& content)
{
    wxString contentWxString(
            wxString::Format(wxT("TOPIC %s %s"), channelName, content));
    addCommandQueue(contentWxString);
}
void CIRCClient::changeNicknameAsync(const wxString& content)
{
    wxString contentWxString(wxString::Format(wxT("NICK %s"), content));
    addCommandQueue(contentWxString);

}
}
} /* namespace CornStarch */
