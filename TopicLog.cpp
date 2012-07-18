#include "TopicLog.hpp"


CTopicLog::CTopicLog(void) : m_channel(NULL)
{
}


CTopicLog::~CTopicLog(void)
{
    delete m_channel;
}


//////////////////////////////////////////////////////////////////////


// 初期化を行う
void CTopicLog::init(const CChannelData& channel)
{
    if (m_channel == NULL){
        m_channel = new CChannelData();
    }
    *m_channel = channel;

    // タイプの指定
    m_type = LOG_TOPIC;
}

// ログを取得する
CChannelData CTopicLog::getLog(void) const
{
    return *m_channel;
}