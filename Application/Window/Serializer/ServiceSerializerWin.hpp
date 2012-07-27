#pragma once
#ifdef _WIN32
#include <wx/wxprec.h>
#include <wx/wx.h>
#include <wx/msw/registry.h>
#include <vector>
#include "../Service/IRCService/IRCService.hpp"
#include "../Service/SCService/SCService.hpp"

namespace CornStarch
{;

// 永続化情報を管理するクラス
class CServiceSerializer
{
    wxRegKey* m_regKey; // レジストリアクセス
    static const wxString KEY_PLACE; // Keyのフルパス

public:
    CServiceSerializer(void);
    ~CServiceSerializer(void);

    // 初期化を行う
    void init(void);

    // サービスを受け取り、保存する
    void saveService(const std::map<int,CChatServiceBase*>& services);

    // 保存されたサービス情報を基に、vectorにpushする
    void loadService(wxEvtHandler* handler, std::map<int,CChatServiceBase*>& services,
        int& serviceId);

private:

    // レジスタに保存する
    void saveReg(const CChatServiceBase* service, int uniqueId);

    // レジスタのサブキーからサービスを作成する
    CChatServiceBase* newService(wxEvtHandler* handler, const wxString& subKey,
        int serviceId);
};

}
#endif
