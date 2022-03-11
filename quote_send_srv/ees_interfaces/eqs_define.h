#pragma once
#include "ees_define.h"
#include "EESQuoteDefine.h"

#pragma pack(push, 1)

#define EQS_VERSION		("10")

#define EQS_QUOTE_PRICE_BELOW  0.01
#define EQS_QUOTE_PRICE_ABOVE  99999999.00
#define EQS_QUOTE_PRICE_PRECISION 1

#define EES_EQS_OT_MODULE_TYPE ("OT")
#define EES_EQS_BK_MODULE_ID ("BK")
#define EES_EQS_BK_MODULE_TYPE ("BK")


#define EES_EQS_RS_MODULE_ID     ("RS")
#define EES_EQS_RS_MODULE_TYPE   ("RS")

#define EES_EQS_HDS_MODULE_ID   ("CNF")
#define EES_EQS_HDS_MODULE_TYPE ("CONF")

#define EES_EQS_CTOS_LOGIN_REQ				'L'
#define EES_EQS_CTOS_LOGOUT_REQ				'O'
#define EES_EQS_CTOS_REG_SYMBOL_REQ			'N'
#define EES_EQS_CTOS_UNREG_SYMBOL_REQ		'R'
#define EES_EQS_CTOS_SYMBOL_LIST_REQ		'S'
#define EES_EQS_CTOS_HEATBEATE_REQ			'H'
#define EES_EQS_CTOS_QUOTE_REQ				'Z'

#define EES_EQS_CTOS_LOGIN_RESP				'A'
#define EES_EQS_CTOS_REG_SYMBOL_RESP		'I'
#define EES_EQS_CTOS_UNREG_SYMBOL_RESP		'F'
#define EES_EQS_CTOS_QUOTE_SNAP				'Q'
#define EES_EQS_CTOS_SYMBOL_LIST_RESP		'M'
#define EES_EQS_CTOS_HEATBEATE_RESP			'H'


//定义一个特殊字符串，用这个字符串作为密码登录TCP的EQS，被认为是内部服务，直接可以登录
//第一个是明文密码，第二个是第一个字符串的MD5。服务器检测第二个，客户端填入第一个
#define EES_EQS_INTERNAL_TCP_LOGIN_PWD	    ("\001\002\00351070496004B4123BDF27A4A95AF")
#define EES_EQS_INTERNAL_TCP_MD5_LOGIN_PWD  ("C1B8CA0E0BD9E2CDFCB441008B91FCD4")

// 定义消息的基本长度

#define EES_EQS_REASON_LEN     19

///所有消息的标准头
struct msg_standard_hdr
{
	char	m_MsgType;

	msg_standard_hdr()
	{
		m_MsgType = 0;
	}
};


enum ees_login_result
{
	EQS_LOGIN_SUCCESS = 'Y',
	EQS_LOGIN_UNSUCCESS = 'N',
};

enum ees_reg_symbol_result
{
	EQS_REG_SUCCESS = '0',
	EQS_REG_FAIL = '1',
	EQS_ALREADY_ADDED = '2',
};

enum ees_unreg_symbol_result
{
	EQS_UNREG_SUCCESS = '0',
	EQS_UNREG_FAIL = '1',
};

//交易所对应的multicast地址信息结构体
struct eqs_mc_info
{
	eqs_mc_info()
	{
		m_eqs_id[0]=0x00 ;
		m_exchange_id = rem_exchange::EXCH_SHH ;		
		m_multicast_ip[0] = 0x00 ;	
		m_multicast_port = 0 ;		
		m_local_ip[0] = 0x00 ;
		m_multicast_local_port = 0;
	}
	char			m_eqs_id[EES_EQS_ID_LEN+1];//每个exchange id可以有多组服务器作为备份，这个值相同的作为同一组服务器	
	T_EXCHANGE		m_exchange_id;//101,102等
	char			m_multicast_ip[EES_IP_LEN+1];//组播IP地址
	u16_sl			m_multicast_port;//组播端口号
	char			m_local_ip[EES_IP_LEN+1];//本地IP地址，组播socket创建绑定需要用到	
	u16_sl			m_multicast_local_port;//本地端口号，组播socket创建绑定需要用到	
};

struct eqs_msg_end
{
	eqs_msg_end()
	{
		set_msg_end() ;
	}

	void set_msg_end()
	{
		m_end_r = '\r' ;
		m_end_n = '\n' ;
	}
	i8_sl m_end_r ; 
	i8_sl m_end_n ; 
};


// EQS登陆请求
struct eqs_login_req
{
	eqs_login_req()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = quote_types::QUOTE_LOGON_REQ;
		m_end.set_msg_end();
		//assert(m_Header.m_MsgLen == );
	}

	msg_standard_hdr	m_Header;	
	u32_sl				m_protocol_ver;
	T_LOGON_ID			m_user_id;
	T_PASSWORD_MD5		m_password;	
	eqs_msg_end			m_end;          // '\r\n'
};

// EQS登陆响应
struct eqs_login_resp
{
	eqs_login_resp()
	{
		memset(this, 0, sizeof(*this));
		m_end.set_msg_end();
	}
	msg_standard_hdr			m_Header;
	
	char m_result; 
	char m_reason[EES_EQS_REASON_LEN + 1];
	eqs_msg_end  m_end;  // '\r\n'
};


struct unknow_stu
{
	unknow_stu()
	{
		one = 0x08;
		two = 0xac;
		three = 0x09;
		four = 0xb0;
		frive = 0xe1;
		six = 0x7f;
	}

	char one;
	char two;
	char three;
	char four;
	char frive;
	char six;

};

struct eqs_symbol_list_resp
{
	eqs_symbol_list_resp()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = EES_EQS_CTOS_SYMBOL_LIST_RESP;
		m_infoformation_type = '0';
		m_msgflag = '0';
		m_instrument_type = '6';
		m_res = unknow_stu();
		
	}

	msg_standard_hdr m_Header;
	char m_infoformation_type;
	char m_msgflag;
	char m_instrument_type;
	char m_symbol[20];
	unknow_stu m_res;
	eqs_msg_end m_end;

};


// eqs 注册行情
struct eqs_reg_symbol_req
{
	eqs_reg_symbol_req()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = quote_types::QUOTE_REG_SYMBOL_REQ;
		m_end.set_msg_end();
	}
	msg_standard_hdr			m_Header;	
	char m_information_type ; 
	char m_exchange_id ; 
	char m_symbol[27];	
	eqs_msg_end	m_end;
};

// eqs 注册行情回复
struct eqs_reg_symbol_resp
{
	eqs_reg_symbol_resp()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = quote_types::QUOTE_REG_SYMBOL_RESP;
		m_end.set_msg_end();
		m_result = '1' ;
		m_information_type = '0' ;	
	}
	
	eqs_reg_symbol_resp & operator=( const eqs_reg_symbol_req req )
	{
		m_information_type = req.m_information_type ;
		m_instrument_type = req.m_exchange_id;
		strcpy(m_symbol, req.m_symbol);
		return *this ;
	}

	void set_reg_good( bool b_good )
	{
		m_result = b_good ? '0' : '1' ;
	}
	
	msg_standard_hdr			m_Header;
	char m_result ;
	char m_information_type ; 
	char m_instrument_type;
	char m_symbol[20];
	unknow_stu m_res;
	eqs_msg_end	m_end;
};

// eqs 注销行情
struct eqs_unreg_symbol_req
{
	eqs_unreg_symbol_req()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = quote_types::QUOTE_UNREG_SYMBOL_REQ;
		m_end.set_msg_end();
		m_information_type = '0' ;		
	}
	msg_standard_hdr			m_Header;
		
	char m_information_type ; 
	char m_exchange_id ; 
	char m_symbol[20];
	unknow_stu m_res;
	eqs_msg_end	m_end;
};

// eqs 注销行情回复
struct eqs_unreg_symbol_resp
{
	eqs_unreg_symbol_resp()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = quote_types::QUOTE_UNREG_SYMBOL_RESP;
		m_end.set_msg_end();
		m_result = '0' ;
		m_information_type = '0' ;		
	}
	msg_standard_hdr			m_Header;

	eqs_unreg_symbol_resp & operator=( const eqs_unreg_symbol_req req )
	{
		m_information_type = req.m_information_type ;
		m_exchange_id = req.m_exchange_id ;
		strcpy(m_symbol, req.m_symbol);


		return *this ;
	}

	void set_unreg_good( bool b_good )
	{
		m_result = b_good ? '0' : '1' ;
	}	
	char m_result ;
	char m_information_type ; 
	char m_exchange_id ; 
	char m_symbol[20];	
	eqs_msg_end	m_end;
};



// eqs 查询行情
struct eqs_query_symbol_quote_req
{
	eqs_query_symbol_quote_req()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = quote_types::QUOTE_QUOTE_QRY_QUOTE;
		m_end.set_msg_end();
	}
	msg_standard_hdr			m_Header;	
	char m_exchange_id;
	char m_symbol[20];
	eqs_msg_end	m_end;
};

// eqs 查询行情回复
struct eqs_query_symbol_quote_resp
{
	eqs_query_symbol_quote_resp()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = quote_types::QUOTE_QUOTE_QRY_QUOTE_RESP;
		m_end.set_msg_end();
	}
	msg_standard_hdr			m_Header;
	unsigned char				m_code ; // 0 ;成功 其它 错误
	char						m_exchange_id;
	char						m_symbol[20];
	EESMarketDepthQuoteData		m_snapshot;
	eqs_msg_end					m_end;
};

// eqs 行情快照
struct eqs_quote_snapshot
{
	eqs_quote_snapshot()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = quote_types::QUOTE_QUOTE_SNAPSHOT;
	}
	msg_standard_hdr			m_Header;
	
	char m_instrument_type;
	char m_symbol[20];
	EESMarketDepthQuoteData m_snapshot;
};

//eqs 行情快照1.0
struct eqs_quote_snapshot_version_one
{
	eqs_quote_snapshot_version_one()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = quote_types::QUOTE_QUOTE_SNAPSHOT;
	}
	msg_standard_hdr			m_Header;

	char m_symbol[20] ;
	char m_exchange_id;
//	EESMarketDepthQuoteDataVersionOne m_snapshot;
};


// EQS 心跳回复
struct eqs_heartbeat_req
{
	eqs_heartbeat_req()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = qmcs_types::QMCS_HEARTBEAT_REQ;
	}

	msg_standard_hdr			m_Header;
	long long   m_time ;
	eqs_msg_end	m_end;  
};

// EQS 心跳回复
struct eqs_heartbeat_resp
{
	eqs_heartbeat_resp()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = qmsc_types::QMSC_HEARTBEAT_RESP;
	}

	msg_standard_hdr			m_Header;
	long long	m_time ;
	eqs_msg_end m_end;  // '\r\n'
};



#pragma pack(pop)
