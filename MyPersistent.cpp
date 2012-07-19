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


// linux
#elif defined __linux
const wxString CMyPersistent::FILE_PATH
    = "~/.CornStarch";

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
    // ファイルが存在しない場合に作成
    m_ifs.open(FILE_PATH);
    if (m_ifs.fail()){
        m_ofs.open(FILE_PATH);
        chmod(FILE_PATH, S_IRUSR | S_IWUSR);
        m_ofs.close();
    }
    m_ifs.close();
}

// 情報を保存する
void CMyPersistent::saveValue(const wxString& key, const wxString& value)
{
    // ファイルからmapとして読み込み
    map<string, string> data = loadFileAsMap();

    // mapに保存
    m_value[(string)key.mb_str(wxConvUTF8)] = (string)key.mb_str(wxConvUTF8);

    // mapからファイルに保存
    m_ofs.open(FILE_PATH, ios::trunc);
    map<string, string>::iterator it;
    for (it = m_value.begin(); it != m_value.end(); it++){
        m_ofs << it.first << it.second;
    }
    m_ofs.close();
}

// キーから情報を読み込む
wxString CMyPersistent::loadValue(const wxString& key)
{
    // ファイルからmapとして読み込み
    map<string, string> table = loadFileAsMap();

    return wxString(table[(string)key.mb_str(wxConvUTF8)].c_str(), wxConvUTF8);
}

// keyが保存されているか
bool CMyPersistent::isKeySaved(const wxString& key) const
{
    // ファイルからmapとして読み込み
    map<string, string> table = loadFileAsMap();

    // keyが保存されていたら
    if (table[(string)key.mb_str(wxConvUTF8)] != ""){
        return true;
    }

    return false;
}

// 保存情報を削除する
void CMyPersistent::deleteValue(const wxString& key)
{
    m_ofs.open(FILE_PATH, ios::trunc);
}

// ファイルをmapとして開く
map<string, string> CMyPersistent::loadFileAsMap(void) const
{
    map<string, string> table;

    // 保存情報をmapで読み込む
    m_ifs.open(FILE_PATH);
    while (!m_ifs.eof()){
        string key, value;
        m_ifs >> key >> value;        
        table[key] = value;
    }
    m_ifs.close();

    return table;
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

// ファイルをmapとして開く
map<string, string> CMyPersistent::loadFileAsMap(void) const
{
    return map<string, string>();
}


#endif
