#pragma once
#include "header.hpp"
#include "StreamData.hpp"
#include "ConnectionEventBase.hpp"

namespace CornStarch
{;

// ストリーム受信時のイベント
class CGetStreamEvent : public CConnectionEventBase
{
private:
    CStreamData m_stream; // ストリームのデータ

public:
    CGetStreamEvent(void);
    ~CGetStreamEvent(void);

    // ストリームを取得する
    CStreamData getStreamData(void) const;

    // ストリームをセットする
    void setStreamData(const CStreamData& stream);

};

}