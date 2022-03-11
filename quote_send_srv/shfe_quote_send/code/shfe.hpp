#pragma once

#include "../../../base/baseFun.hpp"
#include "../../../base/log.hpp"
#include "../../../base/xml.hpp"
#include "../../../base/thread.hpp"
#include "../../../base/db.hpp"

#include "../../../tcp_iocp/src/lance/ldebug.h"
#include "../../../tcp_iocp/src/lance/tcpsrv.hpp"
#include "../../../tcp_iocp/src/lance/systm.h"
#include "../../ees_interfaces/eqs_define.h"

#include <boost/shared_ptr.hpp>

//#include <stdio.h>
#include <fstream>
#include <vector>


using namespace pp;
using namespace std;
//using namespace lance;

#ifdef _WIN32
	
	
	#ifdef _DEBUG
	#pragma comment(lib, "base_jys_d.lib")
	#else
	#pragma comment(lib, "base_jys.lib")
	#endif
#endif

#define _MESSAGE_BUF_ 4096


boost::shared_ptr<CLog>					g_log = boost::shared_ptr<CLog>	(new CLog("quote_send_tcp", true));
vector<EESMarketDepthQuoteData>			g_shfeQuoteData;
map<string, EESMarketDepthQuoteData>	g_closeInfo;

class CQuoteShfe :  public lance::net::Client
{

public: 
	CQuoteShfe(); 
	~CQuoteShfe();

	void recvData();
	void wait();
	void swap(int procLen, int& dataLen);

#ifdef _WIN32
	static pthread_t WINAPI callQuoteSendFun(void* lParam);
#else
	static void* callQuoteSendFun(void* lParam);

#endif


	// 连接建立时被调动
	void OnConnect();
		
		// 连接断开时被调用
	void OnDisconnect();
		
		// 当有数据被接收时调用，接收的实际数据长度为len
	void OnRecv(int len);

		
private:
	char*							m_data;
	char*							m_swapData;
	bool							m_sendThreadFinishFlag;
	bool							m_disFlag;


	int								m_recvTempDataCount;

	bool							m_isLogon;
	size_t							m_sendQuoteIndex;
	string							m_logonID;
	map<string, bool>				m_registerSymbol;

	CThread							m_threadQuoteSend;

};
