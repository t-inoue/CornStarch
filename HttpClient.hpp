#pragma once
#include "SocketClient.hpp"
#include "sstream"

// HTTP通信を行うためのクライアントクラス
class CHttpClient : public CSocketClient
{
	wxString  m_host;
protected:

    static const wxString HTTP_PORT;;
	static const wxString HTTP_VER;

public:
	CHttpClient(void);
	virtual ~CHttpClient(void);
	void init(void);
	std::string recvHttpResponseBody(void);

	wxString getHost() const
	{
		return m_host;
	}

	void setHost(wxString host)
	{
		setUrl(host);
		m_host = host;
	}

protected:
	void sendRequestMethod(const wxString& method, const wxString& uri);
	std::string getResponceBody(const std::string& str) const;
	void sendPostDefault(const wxString& str, const wxString& basic);
	void sendGetDefault(const wxString& basic);
	void sendPutDefault(const wxString& basic);
	void sendDeleteDefault(const wxString& basic);
	void sendStreamDefault(const wxString& basic);
	void sendPutParticular(const wxString& key, const wxString& value, const wxString& basic);
	bool isCorrectHttpResponse(void) const;

private:
	void sendCommonHeader(int length, const wxString& basic);

private:
	void sendHost(void);
	void sendAuth(const wxString& basic);
	void sendAccept(void);
	void sendLength(int length);
	void sendKeepAlive(void);
	void sendBody(const wxString& body);
};

