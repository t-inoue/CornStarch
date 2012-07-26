#pragma once
#include "header.hpp"
#include "ConnectionEventBase.hpp"
#include "StreamData.hpp"

namespace CornStarch
{;

// ストリーム受信時に発生させるイベント
class CStreamEvent : public CConnectionEventBase
{
private:
    CStreamData m_stream; // ストリームのデータ

public:
    CStreamEvent(wxEventType eventType = wxEVT_THREAD, int id = wxID_ANY);
    ~CStreamEvent(void);

    // ストリームを取得する
    CStreamData getStreamData(void) const;

    // ストリームをセットする
    void setStreamData(const CStreamData& stream);
};

}