#pragma once
#include <wx/xml/xml.h>
#include <vector>
#include "IRCService.h"
#include "SCService.h"

// サービスのシリアライズを行うクラス
class CServiceSerializer
{
private:
    wxXmlDocument* m_doc;
    static const wxString PATH;

public:
    CServiceSerializer(void);
    ~CServiceSerializer(void);

    // 初期化を行う
    void init(void);

    // サービスを受け取り、ファイルに保存する
    void saveService(const std::vector<CChatServiceBase*>& services);

    // 保存されたサービス情報を基に、vectorにpushする
    void loadService(wxEvtHandler* handler, std::vector<CChatServiceBase*>& services);
};

