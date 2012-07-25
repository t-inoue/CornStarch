#include "MyPersistent.hpp"

using namespace std;

// windows
const wxString CMyPersistent::KEY_PLACE
    = "HKEY_CURRENT_USER\\Software\\CornStarch";

CMyPersistent::CMyPersistent(void) : m_regKey(NULL)
{
}


CMyPersistent::~CMyPersistent(void)
{
    delete m_regKey;
}


//////////////////////////////////////////////////////////////////////


// 初期化を行う
void CMyPersistent::init(void)
{
    m_regKey = new wxRegKey(KEY_PLACE);

    // 存在しなければ新規作成
    if (m_regKey->Exists()){
        m_regKey->Create();
    }
}

// keyとvalueを永続化する
void CMyPersistent::saveValue(const wxString& key, const wxString& value)
{
    // 値の保存
    m_regKey->SetValue(key, value);
}

// keyの情報を取得する
wxString CMyPersistent::loadValue(const wxString& key)
{
    // 文字列の読み込み
    wxString result;
    if (!m_regKey->QueryValue(key, result)){

        // valueが存在しない場合
        return "";
    }

    // 値の読み込み
    return result;
}

// keyが登録されているかどうか
bool CMyPersistent::isKeySaved(const wxString& key) const
{
    // キーが存在しない
    if (!m_regKey->Exists()){
        return false;
    }

    // キー名に対応する値が存在しない
    if (!m_regKey->HasValue(key)){
        return false;
    }

    return true;
}

// 永続化された情報を消す
void CMyPersistent::deleteValue(const wxString& key)
{
    m_regKey->DeleteValue(key);
}

// サービスを受け取り、ファイルに保存する
void CMyPersistent::saveService(const vector<CChatServiceBase*>& services)
{
    wxRegKey reg(*m_regKey, "a");
    reg.Create();

    //reg.QueryValue
}

// 保存されたサービス情報を基に、vectorにpushする
void CMyPersistent::loadService(wxEvtHandler* handler, vector<CChatServiceBase*>& services,
    int& serviceId)
{

}
