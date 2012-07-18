#include "MyPersistent.hpp"

using namespace std;

// windows
#ifdef _WIN32
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
void CMyPersistent::saveInfo(const wxString& key, const wxString& value)
{
    // 値の保存
    m_regKey->SetValue(key, value);
}

// keyの情報を取得する
wxString CMyPersistent::loadInfo(const wxString& key)
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
void CMyPersistent::deleteInfo(const wxString& key)
{
    m_regKey->DeleteValue(key);
}


// linux
#elif defined __linux
CPersistentInfoLinux::CPersistentInfoLinux(void)
{
}


CPersistentInfoLinux::~CPersistentInfoLinux(void)
{
    map<wxString, wxString>::iterator it;
    for (it = m_value.begin(); it != m_value.end(); it++){
        m_ofs << it->first << " " << it->second << endl;;
    }
}


//////////////////////////////////////////////////////////////////////


// 初期化を行う
void CPersistentInfoLinux::init(void)
{
    // ファイルが開けない(存在しない)
    m_ifs.open("./.config");
    if (m_ifs.fail()){

        // ファイルを作成する
        m_ofs.open("./.config");
        chmod("./.config", S_IRUSR | S_IWUSR);
    } else {

        // ファイルが存在した場合
        while (!m_ifs.eof()){
            wxString key, value;
            m_ifs >> key >> value;
            m_value[key] = value;
        }
        m_ifs.close();
        m_ofs.open("./.config");
    }
}

// 情報を保存する
void CPersistentInfoLinux::saveInfo(const wxString& key, const wxString& value)
{
    m_value[key] = value;
}

// キーから情報を読み込む
wxString CPersistentInfoLinux::loadInfo(const wxString& key)
{
    return m_value[key];
}

// keyが保存されているか
bool CPersistentInfoLinux::isKeySaved(const wxString& key) const
{
    if (m_value.find(key) == m_value.end()){
        return false;
    }
    return true;
}

// 保存情報を削除する
void CPersistentInfoLinux::deleteInfo(const wxString& key)
{
    m_value.clear();
}


// mac
#else
CMyPersistent::CMyPersistent(void)
{
}


CMyPersistent::~CMyPersistent(void)
{
}


//////////////////////////////////////////////////////////////////////


// 初期化を行う
void CMyPersistent::init(void)
{
    // ファイルが開けない(存在しない)
    m_ifs.open("./.config");
    if (m_ifs.fail()){

        // ファイルを作成する
        m_ofs.open("./.config");
        chmod("./.config", S_IRUSR | S_IWUSR);
    } else {

        // ファイルが存在した場合
//        while (!m_ifs.eof()){
//            wxString key, value;
//            m_ifs >> string(key.mb_str(wxConvUTF8)) >> string(value.mb_str(wxConvUTF8));
//            m_value[key] = value;
//        }
        m_ifs.close();
        m_ofs.open("./.config");
    }}

// 情報を保存する
void CMyPersistent::saveInfo(const wxString& key, const wxString& value)
{
    m_value[key] = value;
}

// キーから情報を読み込む
wxString CMyPersistent::loadInfo(const wxString& key)
{
    return m_value[key];
}

// keyが保存されているか
bool CMyPersistent::isKeySaved(const wxString& key) const
{
    if (m_value.find(key) == m_value.end()){
        return false;
    }
    return true;
}

// 保存情報を削除する
void CMyPersistent::deleteInfo(const wxString& key)
{
    m_value.clear();
}

#endif
