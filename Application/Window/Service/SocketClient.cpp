#include "SocketClient.hpp"

using namespace std;

namespace CornStarch
{;

CSocketClient::CSocketClient(void) :
		m_address(NULL), m_socket(NULL)
{
}

CSocketClient::~CSocketClient(void)
{
	delete m_address;
	delete m_socket;
}

///////////////////////////////////////////////////////////////////////////

// クライアントの初期化を行う
void CSocketClient::init(void)
{
	// ソケット通信の準備
	m_address = new wxIPV4address();
	m_socket = new wxSocketClient();
}

// 接続を行う
bool CSocketClient::connect(void)
{
	return m_socket->Connect(*m_address);
}

// 接続を閉じる
void CSocketClient::close(void)
{
	if (m_socket->IsConnected()){
		m_socket->Close();
	}
}

// ポート番号をセット
void CSocketClient::setPort(const wxString& port)
{
	m_address->Service(port);
}

// ホスト名からIPアドレスをセット
void CSocketClient::setUrl(const wxString& url)
{
	m_address->Hostname(url);
}

///////////////////////////////////////////////////////////////////////////

// 受信を行う(待機デフォルト1000usec = 1msec)
int CSocketClient::receive(long waitTimeUsec)
{
	// 受信バッファ
	char recvBuf[MAX_LENGTH];
	memset(&recvBuf, '\0', sizeof(recvBuf));

	int recvSize = 0; // 受信済みサイズ
	int result; // recv関数の戻り値

	while (1){

		// waitTimeUsecの間、受信可能か調べる
		if (waitRecv(waitTimeUsec) == 0){
			break;
		}
		// 受信
		m_socket->Read(recvBuf, MAX_LENGTH - recvSize);

		// エラー時、もしくはソケットクローズ時
		result = m_socket->LastCount();
		if (result <= 0){

			// これ以上受信しないで接続を閉じる
			break;
		}

		// 受信結果を反映
		recvSize += result;
		m_buffer += recvBuf;
		memset(&recvBuf, '\0', sizeof(recvBuf));

		// 最大長まで受信したら
		if (recvSize >= MAX_LENGTH){
			// これ以上受信しない
			break;
		}
		if( m_socket->Error())
		{
		    close();
		    break;
		}
	}
	return recvSize;
}

// 改行込みで送信を行う
void CSocketClient::send(const wxString& message)
{
	int sendSize = 0; // 送信済みサイズ
	int result; // send関数の戻り値
	string msg(message.mb_str(wxConvUTF8));

	// 送信するデータ長
	int length = (int) msg.size();

	// 送信し終わるまで
	while (sendSize < length){

		// 残りの文字列を取得
		string buffer = msg.substr(sendSize);

		// 送信
		m_socket->Write(buffer.c_str(), length - sendSize);

		// 送信が失敗したら
		if (m_socket->LastError() == wxSOCKET_IOERR){

			// 接続を閉じる
			close();
			return;
		}

		// 送信済みサイズを足す
		result = m_socket->LastCount();
		sendSize += result;
	}

	// 改行コードを送信する
	m_socket->Write("\n", 1);
}

// 改行を送信する
void CSocketClient::sendLF(void)
{
	m_socket->Write("\n", 1);
}

// 指定された時間受信待機する(デフォルト1msec)
int CSocketClient::waitRecv(int usec, int sec)
{
	// ソケットの登録
	if (m_socket->WaitForRead((long) sec, usec / 1000)){
		return true;
	}
	return false;
}

}
