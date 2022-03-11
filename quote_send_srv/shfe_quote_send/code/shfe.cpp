#include "shfe.hpp"

CQuoteShfe::CQuoteShfe()
{
	m_isLogon = m_disFlag = m_sendThreadFinishFlag = false;
	m_sendQuoteIndex = 0;
	m_data = (char*)malloc(_MESSAGE_BUF_);
	m_swapData = (char*)malloc(_MESSAGE_BUF_);
	assert(m_data && m_swapData);
}

CQuoteShfe::~CQuoteShfe()
{}

void CQuoteShfe::OnConnect()
{
	g_log->log("info on client connectedd fd=%08x, ip=%d, port=%d", fd, ip, port);
	for(size_t i = 0; i < g_shfeQuoteData.size(); ++i)
	{
		m_registerSymbol[string(g_shfeQuoteData[i].ExchangeInstID)] = false;
	}

	recvData();
	m_threadQuoteSend.init(callQuoteSendFun, this);
}

void CQuoteShfe::OnDisconnect()
{		
	m_disFlag = true;
	g_log->log("info on client disconnect fd=%08x, ip=%d, port=%d", fd, ip, port);	
	m_threadQuoteSend.Cancl();
	while(1)
	{
		_sleep_(_TIME_MS_);
		if(m_sendThreadFinishFlag)
		{
			return;
		}
	}
}

void CQuoteShfe::swap(int procLen, int& dataLen)
{
	if(dataLen <= procLen)
	{
		dataLen = 0;
		return;
	}
	memcpy(m_swapData, m_data + procLen, dataLen - procLen);
	memcpy(m_data, m_swapData, dataLen - procLen);
	dataLen -= procLen;
}

void CQuoteShfe::OnRecv(int len)
{
	m_data[len] = 0;
	char msgID = *m_data;
	if(0 == len || 0 == msgID)
	{
		_sleep_(10 * _TIME_MS_);
		if(++m_recvTempDataCount > 10000) 
		{
			m_disFlag = true;
			g_log->log("info on client time out fd=%08x ", fd);			
		}
		return;
	}

	//g_log->log("info on client recv data fd=%08x len=%d", fd, len);
	
	// 需要切包
	while(len > 1)
	{
		msgID = *m_data;
		// 登录
		if(EES_EQS_CTOS_LOGIN_REQ == msgID)
		{	
			m_logonID = m_data + 3;
			g_log->log("info on user logon %s ", m_logonID.c_str());

			eqs_login_resp resp;
			// 直接登录成功
			m_isLogon = true;
			resp.m_result = EQS_LOGIN_SUCCESS;
			resp.m_Header.m_MsgType = EES_EQS_CTOS_LOGIN_RESP;
			swap(sizeof(eqs_login_req), len);
			send((char*)&resp, sizeof(eqs_login_resp));
		}

		// 注册合约
		else if(EES_EQS_CTOS_REG_SYMBOL_REQ == msgID)
		{
			eqs_reg_symbol_req* req = (eqs_reg_symbol_req*)(m_data); 
			eqs_reg_symbol_resp resp;
			if( m_registerSymbol.find(string(req->m_symbol)) != m_registerSymbol.end())
			{
				//g_log->log("info on user %s reg symbol %s ", m_logonID.c_str(), req->m_symbol);
				resp = *req;
				resp.m_Header.m_MsgType = EES_EQS_CTOS_REG_SYMBOL_RESP;
				resp.set_reg_good(true);			

				m_registerSymbol[string(req->m_symbol)] = true;
				swap(sizeof(eqs_reg_symbol_req), len);
				send((char*)&resp, sizeof(eqs_reg_symbol_resp));
			}
		}

		// 注销合约
		else if(EES_EQS_CTOS_UNREG_SYMBOL_REQ == msgID)
		{
			eqs_unreg_symbol_req* req = (eqs_unreg_symbol_req*)(m_data); 
			eqs_unreg_symbol_resp resp;
			if( m_registerSymbol.find(string(req->m_symbol)) != m_registerSymbol.end())
			{
				//g_log->log("info on user %s unreg symbol %s ", m_logonID.c_str(), req->m_symbol);
				resp.m_Header.m_MsgType = EES_EQS_CTOS_UNREG_SYMBOL_RESP;
				resp = *req;
				resp.set_unreg_good(true);

				(m_registerSymbol[string(req->m_symbol)]) = false;
				swap(sizeof(eqs_unreg_symbol_req), len);
				send((char*)&resp, sizeof(eqs_unreg_symbol_resp));
			}
		}

		// 请求合约列表
		else if(EES_EQS_CTOS_SYMBOL_LIST_REQ == msgID)
		{
			eqs_symbol_list_resp resp;
			resp.m_Header.m_MsgType = EES_EQS_CTOS_SYMBOL_LIST_RESP;
			resp.m_end.set_msg_end();
			map<string, bool>::const_iterator symbolIter = m_registerSymbol.begin();
			while(symbolIter != m_registerSymbol.end())
			{
				strcpy(resp.m_symbol, symbolIter->first.c_str());
				send((char*)&resp, sizeof(eqs_symbol_list_resp));			
				++symbolIter;
			}

			eqs_symbol_list_resp respEnd;
			respEnd.m_Header.m_MsgType = EES_EQS_CTOS_SYMBOL_LIST_RESP;
			respEnd.m_end.set_msg_end();
			respEnd.m_msgflag = '1';
			swap(8, len);
			send((char*)&respEnd, sizeof(eqs_symbol_list_resp));
		}
		else
		{
			// 其余消息不做处理
			g_log->log("warn other msg id %d len:%d", msgID, len);
			len = 0;
			*m_data = 0;
		}
	}

	m_recvTempDataCount = 0;
	if(!m_disFlag)
	{
		recvData();
	}
}

void CQuoteShfe::recvData()
{
	recv(m_data, _MESSAGE_BUF_ - 1);
}

pthread_t CQuoteShfe::callQuoteSendFun(void* lParam)
{
	CQuoteShfe* m = (CQuoteShfe*)lParam;
	while(1)
	{
		_sleep_(_TIME_MS_);
		if(!(m->m_isLogon))
		{
			continue;
		}

		Time t;		
		while(m->m_sendQuoteIndex < g_shfeQuoteData.size())
		{
			EESMarketDepthQuoteData nowQuote = g_shfeQuoteData[m->m_sendQuoteIndex];
			//g_log->log("info now send quote symbol:%s", nowQuote.ExchangeInstID);
			if(m->m_registerSymbol[string(nowQuote.ExchangeInstID)])
			{
				CLog::getTime(t);
				memcpy(nowQuote.TradingDay, CLog::getDate().c_str(), sizeof(nowQuote.UpdateTime));
				memcpy(nowQuote.UpdateTime, t.TimeS.c_str(), sizeof(nowQuote.UpdateTime));

				eqs_quote_snapshot snap;
				snap.m_Header.m_MsgType = EES_EQS_CTOS_QUOTE_SNAP;
				snap.m_instrument_type = '6';
				strncpy(snap.m_symbol, nowQuote.ExchangeInstID, sizeof(EESQuoteExchangeInstIDType));
				memcpy((char*)&snap.m_snapshot, (char*)&nowQuote, sizeof(EESMarketDepthQuoteData));

				if(m->m_disFlag)
				{
					m->m_sendThreadFinishFlag = true;
					return NULL;
				}

				m->send((char*)&snap, sizeof(eqs_quote_snapshot));
				m->m_sendQuoteIndex++;

				_sleep_(_TIME_US_ * 250);
			}
		}

		g_log->log("info send all quote data to client finished fd=%08x user id=%s rows=%d", m->fd, m->m_logonID.c_str(), g_shfeQuoteData.size());
		m->m_sendQuoteIndex = 0;
	}

	return NULL;
}


int main()
{
	string xmlParamName = "ees_db_entry.xml";
	CXmlAnalisys xml(xmlParamName);
	
	xml.mobToChildNodeByName("ot_conf");


	string ip = xml.getValueByName("server", "ip");
	int port = atoi(xml.getValueByName("server", "port").c_str());
	string user = xml.getValueByName("server", "uid");
	string pwd = xml.getValueByName("server", "pwd");
	string dataBase = xml.getValueByName("server", "database");
	int quoteSrvPort = atoi(xml.getValueByName("server", "quote_srv_port").c_str());
	string file = xml.getValueByName("server", "source_file");
	vector<string> quoteSourceV;
	splitStr(quoteSourceV, file, ',');
	string sourceType = xml.getValueByName("server", "source_type") == "file" ? "file" : "db";

	if("db" == sourceType)
	{
		CDB configDB(ip, port, dataBase, user, pwd, g_log);

		configDB.query("select setting_value from t_global_settings where setting_key = 'TRADING_DATA_DB' ;");
		DataType data = configDB.getData();
		string tradeBDString = data[0]["setting_value"];
		if(tradeBDString.empty())
		{
			g_log->log("error get trading db conf failed");
			return -1;
		}

		vector<string> tradingDBInfo;
		splitStr(tradingDBInfo, tradeBDString, ';');
		size_t i = 0;
		string tradingDBName;
		string tradingDBHost;
		while(i < tradingDBInfo.size())
		{
			vector<string> childInfo;
			if(string::npos != tradingDBInfo[i].find("database"))
			{
				string childStr = tradingDBInfo[i];
				splitStr(childInfo, childStr, '=');
				tradingDBName = childInfo[1];
			}

			if(string::npos != tradingDBInfo[i].find("server"))
			{
				string childStr = tradingDBInfo[i];
				splitStr(childInfo, childStr, '=');
				tradingDBHost = childInfo[1];
			}

			++i;
		}

		CDB tradingDB(tradingDBHost.c_str(), 3306, tradingDBName, "shengli", "shengli0", g_log);
		tradingDB.query("select * from t_close_report;" );
		DataType closeData = tradingDB.getData();
		tradingDB.query("select * from t_close_report_opt;");
		DataType closeDataOpt = tradingDB.getData();

		for(size_t i = 0; i < closeData.size(); ++i)
		{
			string symbol = closeData[i]["symbol"];
			strcpy(g_closeInfo[symbol].ExchangeID, closeData[i]["exchange"].c_str());
			g_closeInfo[symbol].PreSettlementPrice = atof(closeData[i]["settle_price"].c_str());
			g_closeInfo[symbol].PreClosePrice = atof(closeData[i]["close_price"].c_str());
			g_closeInfo[symbol].UpperLimitPrice = atof(closeData[i]["upper_limit"].c_str());
			g_closeInfo[symbol].LowerLimitPrice = atof(closeData[i]["lower_limit"].c_str());

			g_log->log("info get symbol quote symbol:%s exchange:%s presettle:%f preclose:%f uplimit:%f lowlimit:%f", 
				symbol.c_str(), g_closeInfo[symbol].ExchangeID, g_closeInfo[symbol].PreSettlementPrice, g_closeInfo[symbol].PreClosePrice,
				g_closeInfo[symbol].UpperLimitPrice, g_closeInfo[symbol].LowerLimitPrice  );

		}

		for(size_t i = 0; i < closeDataOpt.size(); ++i)
		{
			string symbol = closeData[i]["symbol"];
			strcpy(g_closeInfo[closeDataOpt[i]["symbol"]].ExchangeID, closeDataOpt[i]["exchange"].c_str());
			g_closeInfo[closeDataOpt[i]["symbol"]].PreSettlementPrice = atof(closeDataOpt[i]["settle_price"].c_str());
			g_closeInfo[closeDataOpt[i]["symbol"]].UpperLimitPrice = atof(closeDataOpt[i]["upper_limit"].c_str());
			g_closeInfo[closeDataOpt[i]["symbol"]].LowerLimitPrice = atof(closeDataOpt[i]["lower_limit"].c_str());
			g_closeInfo[closeDataOpt[i]["symbol"]].PreClosePrice = atof(closeDataOpt[i]["close_price"].c_str());
			g_log->log("info get symbol quote symbol:%s exchange:%s presettle:%f preclose:%f uplimit:%f lowlimit:%f",
				symbol.c_str(), g_closeInfo[symbol].ExchangeID, g_closeInfo[symbol].PreSettlementPrice, g_closeInfo[symbol].PreClosePrice,
				g_closeInfo[symbol].UpperLimitPrice, g_closeInfo[symbol].LowerLimitPrice);
		}

	}
	else
	{
		ifstream quoteClose("quote.csv");
		if(!quoteClose.is_open())
		{
			return -1;
		}

		string tmp;
		vector<string> line;
		// 忽略第一行
		getline(quoteClose, tmp);
		while (getline(quoteClose, tmp))
		{
			line.clear();
			splitStr(line, tmp.c_str(), ',');
			if(!line.empty())
			{
				string symbol = line[0];
				strcpy(g_closeInfo[line[0]].ExchangeID, line[2].c_str());
				g_closeInfo[symbol].PreSettlementPrice = atof(line[10].c_str());
				g_closeInfo[symbol].PreClosePrice = atof(line[9].c_str());
				g_closeInfo[symbol].UpperLimitPrice = atof(line[14].c_str());
				g_closeInfo[symbol].LowerLimitPrice = atof(line[15].c_str());

				g_log->log("info get symbol quote symbol:%s exchange:%s presettle:%f preclose:%f uplimit:%f lowlimit:%f", 
					symbol.c_str(), g_closeInfo[symbol].ExchangeID, g_closeInfo[symbol].PreSettlementPrice, g_closeInfo[symbol].PreClosePrice,
					g_closeInfo[symbol].UpperLimitPrice, g_closeInfo[symbol].LowerLimitPrice  );
			}
		}

		ifstream quoteCloseOpt("quote_opt.csv");
		if(!quoteCloseOpt.is_open())
		{
			return -1;
		}

		getline(quoteCloseOpt, tmp);
		while (getline(quoteCloseOpt, tmp))
		{
			line.clear();
			splitStr(line, tmp.c_str(), ',');
			if(!line.empty())
			{
				string symbol = line[0];
				strcpy(g_closeInfo[line[0]].ExchangeID, line[2].c_str());
				g_closeInfo[symbol].PreSettlementPrice = atof(line[10].c_str());
				g_closeInfo[symbol].PreClosePrice = atof(line[9].c_str());
				g_closeInfo[symbol].UpperLimitPrice = atof(line[14].c_str());
				g_closeInfo[symbol].LowerLimitPrice = atof(line[15].c_str());

				g_log->log("info get symbol quote symbol:%s exchange:%s presettle:%f preclose:%f uplimit:%f lowlimit:%f", 
					symbol.c_str(), g_closeInfo[symbol].ExchangeID, g_closeInfo[symbol].PreSettlementPrice, g_closeInfo[symbol].PreClosePrice,
					g_closeInfo[symbol].UpperLimitPrice, g_closeInfo[symbol].LowerLimitPrice  );
			}
		}


	}
	
	for(size_t i = 0; i < quoteSourceV.size(); ++i)
	{
		string exchangeFileQoute = quoteSourceV[i];
		ifstream quote(exchangeFileQoute.c_str());
		string tmp;
		vector<string> line;
		if(!quote.is_open())
		{
			return -1;
		}


		while (getline(quote, tmp))
		{
			line.clear();
			splitStr(line, tmp.c_str(), ',');
			if(!line.empty())
			{
				EESMarketDepthQuoteData q;
				memset(&q, 0, sizeof(EESMarketDepthQuoteData));

				strcpy(q.ExchangeInstID, line[7].c_str());
				strcpy(q.InstrumentID, line[7].c_str());

				q.BidPrice1 = atof(line[15].c_str());
				q.BidVolume1 = atoi(line[16].c_str());
				q.AskPrice1 = atof(line[18].c_str());
				q.AskVolume1 = atoi(line[19].c_str());
				q.UpdateMillisec = atoi(line[9].c_str());
				q.PreClosePrice = 0;
				string lastInfo = line[12];
				vector<string> last;
				splitStr(last, lastInfo, '|');
				if(!last.empty())
				{
					q.Turnover = atof(last[0].c_str());
					q.OpenInterest = atof(last[1].c_str());
					q.LastPrice = atof(last[2].c_str());
				}

				q.Volume = atoi(line[13].c_str());

				strcpy(q.ExchangeID, g_closeInfo[q.InstrumentID].ExchangeID);
				q.PreClosePrice = g_closeInfo[q.InstrumentID].PreClosePrice;
				q.PreSettlementPrice = g_closeInfo[q.InstrumentID].PreSettlementPrice;
				q.UpperLimitPrice = g_closeInfo[q.InstrumentID].UpperLimitPrice;
				q.LowerLimitPrice= g_closeInfo[q.InstrumentID].LowerLimitPrice;

				g_shfeQuoteData.push_back(q);
			}
		}

		quote.close();
	}
	
	

	g_log->log("info quote row count %d", g_shfeQuoteData.size());
	

	lance::net::TCPSrv<CQuoteShfe> srv;
	srv.ip = 0;
	srv.port = 0 == quoteSrvPort ? 20006 : quoteSrvPort;
	srv.ptr = NULL;
	srv.backlogs = 10;
	// 处理线程池线程数
	srv.threads = 1;
	srv.scheds = 0;
	// 启动网络服务
	srv.start();
	g_log->log("info on srv start listen port %d", srv.port);

	while(true)
	{
		_sleep_(_TIME_S_);
	}

	g_log->log("info on srv finish! bye!");

	return 0;
}


