#pragma once
#include <wx/xml/xml.h>
#include <vector>
//#include "ConnectionContents.hpp"

// サービスのシリアライズを行うクラス
class CServiceSerializer
{
private:
    wxXmlDocument* m_doc;

public:
    CServiceSerializer(void);
    ~CServiceSerializer(void);

    // 初期化を行う
    void init(void);

    // サービスを受け取り、ファイルに保存する
    //void saveService(const std::vector<CConnectionContents*> services);
};

