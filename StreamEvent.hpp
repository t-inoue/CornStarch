#pragma once
#include "header.hpp"
#include "StreamData.hpp"

// ストリーム受信時に発生させるイベント
class CStreamEvent : public wxThreadEvent
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

