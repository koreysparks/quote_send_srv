#pragma once 

#include "msg_define.h"


//编译期检查结构体大小是否8字节对齐
#define CHECK_SZ_ALIGN_TO_8		((void)(1/!(sizeof(*this) & 0x7)))

// 向上8字节对齐所需字节数
#define NEED_SZ_ALIGN_TO_8(s)	(((s) & 0x7) ? (0x8 - ((s) & 0x7)) : 0)

#pragma pack(push, 1)
///#START，股票版消息结构体定义


///#START，硬件相关协议
///#START，交易类，Client通道
///#START，交易类，Client发往REM
///前缀tmcs: Trade Message, Client to Server

//订单请求(10-112)
struct tmcs_new_order_req
{
	tmcs_new_order_req()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = tmcs_types::TMCS_NEW_ORDER_REQ;
		m_Header.m_MsgLen = sizeof(*this);
		assert(m_Header.m_MsgLen == sizeof(msg_standard_hdr) + sizeof(client_order_req_body));
	}
	msg_standard_hdr			m_Header;
	client_order_req_body		m_Body;
};

//撤单请求(13-80)
struct tmcs_cxl_req
{
	tmcs_cxl_req()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = tmcs_types::TMCS_CXL_REQ;
		m_Header.m_MsgLen = sizeof(*this);
		assert(m_Header.m_MsgLen == sizeof(msg_standard_hdr) + sizeof(client_cxl_req_body));
	}
	msg_standard_hdr			m_Header;
	client_cxl_req_body			m_Body;
};

//#END，交易类，Client发往REM

///#START，交易类，REM发往Client
///前缀tmsc: Trade Message, Server to Client


//REM订单接受 (1010-240)
struct tmsc_order_accept
{
	tmsc_order_accept()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = tmsc_types::TMSC_ORDER_ACCEPT;
		m_Header.m_MsgLen = sizeof(*this);
		assert(m_Header.m_MsgLen == sizeof(msg_standard_hdr) + sizeof(client_accept_order_body));
	}
	msg_standard_hdr				m_Header;
	client_accept_order_body		m_ClientAcceptBody;
};

//订单拒绝(1011-136)
struct tmsc_order_reject
{
	tmsc_order_reject()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = tmsc_types::TMSC_ORDER_REJECT;
		m_Header.m_MsgLen = sizeof(*this);
		assert(m_Header.m_MsgLen == sizeof(msg_standard_hdr) + sizeof(client_order_reject_body));
	}
	msg_standard_hdr			m_Header;
	client_order_reject_body	m_ClientOrderRejectedBody;
};

//成交回报(1012-152)
struct tmsc_order_execution
{
	tmsc_order_execution()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = tmsc_types::TMSC_ORDER_EXECUTION;
		m_Header.m_MsgLen = sizeof(*this);
		assert(m_Header.m_MsgLen == sizeof(msg_standard_hdr) + sizeof(client_exec_body));
	}

	msg_standard_hdr			m_Header;
	client_exec_body			m_ExecBody;
};

//客户端撤单成功(1013-136)
struct tmsc_order_cxled
{
	tmsc_order_cxled()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = tmsc_types::TMSC_ORDER_CXLED;
		m_Header.m_MsgLen = sizeof(*this);
		assert(m_Header.m_MsgLen == sizeof(msg_standard_hdr) + sizeof(client_cxled_body));
	}
	msg_standard_hdr			m_Header;
	client_cxled_body			m_ClientCxledBody;
};

//客户端撤单拒绝(1014-136)
struct tmsc_cxl_reject
{
	tmsc_cxl_reject()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = tmsc_types::TMSC_CXL_REJECTED;
		m_Header.m_MsgLen = sizeof(*this);
		assert(m_Header.m_MsgLen == sizeof(msg_standard_hdr) + sizeof(client_cxl_reject_body));
	}
	msg_standard_hdr			m_Header;
	client_cxl_reject_body		m_ClientCxlRejectBody;
};

//ETF申购赎回成交回报(1015-184)
struct tmsc_etf_execution
{
	tmsc_etf_execution()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = tmsc_types::TMSC_ETF_EXEC;
		m_Header.m_MsgLen = sizeof(*this);
		assert(m_Header.m_MsgLen == 184);
	}
	msg_standard_hdr			m_Header;
	client_etf_exec_body		m_ClientEtfExecBody;

};

//#END，交易类，REM发往Client


///#START，Client查询类和响应类
///#START，Client查询

//协议版本号校验(2000-16)
struct qmcs_protocol_version_report
{
	qmcs_protocol_version_report()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = qmcs_types::QMCS_PROTOCOL_VERSION_REPORT;
		m_Header.m_MsgLen = sizeof(*this);
		m_ProtoVersion = REM_TRADE_PROTO_VERSION;
		assert(m_Header.m_MsgLen == 16);
	}
	msg_standard_hdr			m_Header;
	uInt32						m_ProtoVersion;
	uInt8						m_Reserved[4];
};


//登录请求(2001-128)
struct qmcs_logon_req
{
	qmcs_logon_req()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = qmcs_types::QMCS_LOGON_REQ;
		m_Header.m_MsgLen = sizeof(*this);
		assert(m_Header.m_MsgLen == 256);
	}
	msg_standard_hdr			m_Header;
	uInt32						m_ProtoVersion;
	T_LOGON_ID					m_LogonID;
	T_PASSWORD_MD5				m_Password;
	T_MAC_ADDR					m_ClientMac;
	T_CLIENT_PROD_INFO			m_ClientProdInfo;
	T_APP_ID					m_AppID;
	uInt8						m_Reserved1[7];
	T_APP_AUTH_CODE				m_AppAuthCode;
	uInt8						m_Reserved2[7];

	// 下面的两个信息， 是采集到的， 不是用户自己填写的。
	unsigned char 				m_CapIP[4];
	uInt8						m_Reserved3[4];
	unsigned char				m_CapMac[6];
	uInt8						m_Reserved4[2];
};


// 向服务端报告看穿式监管客户端资料
struct tmcs_report_client_rptr
{
	tmcs_report_client_rptr()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = qmcs_types::QMCS_REQ_REPORT_CAPTURE_CLIENT_INFO_REQ;
		m_Header.m_MsgLen = sizeof(*this);
		assert(m_Header.m_MsgLen == sizeof(tmcs_report_client_rptr));
	}
	msg_standard_hdr			m_Header;
	uInt32						m_UserID;
	uInt32						m_SocketID;
	unsigned char				m_NeedRptr;
	char						m_nBaseCaptureInfo[512];
};


struct check_item
{
	unsigned char m_check_type;
	unsigned char m_count;
	unsigned char m_data[0];
};


struct qmcs_logon_req_last
{
	unsigned char m_version;

};



// 客户端请求心跳包
struct qmcs_heartbeat_req
{
	qmcs_heartbeat_req()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = qmcs_types::QMCS_HEARTBEAT_REQ;
		m_Header.m_MsgLen = sizeof(*this);
		assert(m_Header.m_MsgLen == 16);
	}
	msg_standard_hdr			m_Header;
	uInt32						m_UserID;
	uInt8						m_Reserved[4];
};


///  lgl 20180226
//查询端口登录请求
struct qmcs_query_logon_req
{
	qmcs_query_logon_req()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = qmcs_types::QMCS_QUERY_LOGON_REQ;
		m_Header.m_MsgLen = sizeof(*this);
		assert(m_Header.m_MsgLen == 48);
	}
	msg_standard_hdr			m_Header;
	T_SESSION_ID				m_QuerySessionID;
	uInt32						m_UserID;
	uInt8						m_Reserved[3];
};
//

///修改密码请求(2002-80)
struct qmcs_change_password_req
{
	qmcs_change_password_req()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = qmcs_types::QMCS_CHANGE_PASSWORD_REQ;
		m_Header.m_MsgLen = sizeof(*this);
		assert(m_Header.m_MsgLen == 80);
	}
	msg_standard_hdr			m_Header;
	uInt32						m_UserID;
	T_PASSWORD_MD5				m_OldPassword;
	T_PASSWORD_MD5				m_NewPassword;
	uInt8						m_Reserved[2];
};

///客户号列表查询(2003-16)
struct qmcs_client_id_list_req
{
	qmcs_client_id_list_req()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = qmcs_types::QMCS_CLIENT_ID_LIST_REQ;
		m_Header.m_MsgLen = sizeof(*this);
		CHECK_SZ_ALIGN_TO_8;
	}
	msg_standard_hdr			m_Header;

	Int32						m_RequestID;
	uInt32						m_UserID;

};

///资金账号列表查询(2004-32)
struct qmcs_fund_account_list_req
{
	qmcs_fund_account_list_req()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = qmcs_types::QMCS_FUND_ACCOUNT_LIST_REQ;
		m_Header.m_MsgLen = sizeof(*this);
		CHECK_SZ_ALIGN_TO_8;
	}
	msg_standard_hdr			m_Header;

	Int32						m_RequestID;
	uInt32						m_UserID;

	T_CUST_ID					m_ClientID;
	uInt8						m_Reserved[7];
};

///证券代码列表查询(2005-16)
struct qmcs_security_code_list_req
{
	qmcs_security_code_list_req()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = qmcs_types::QMCS_SECURITY_CODE_LIST_REQ;
		m_Header.m_MsgLen = sizeof(*this);
		CHECK_SZ_ALIGN_TO_8;
	}
	msg_standard_hdr			m_Header;

	Int32						m_RequestID;
	uInt32						m_UserID;

	uInt32						m_ComboSecurityType;
	uInt8						m_Reserved[4];
};

///ETF成份股查询(2006-24)
struct qmcs_etf_member_list_req
{
	qmcs_etf_member_list_req()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = qmcs_types::QMCS_ETF_MEMBER_LIST_REQ;
		m_Header.m_MsgLen = sizeof(*this);
		CHECK_SZ_ALIGN_TO_8;
	}
	msg_standard_hdr			m_Header;

	Int32						m_RequestID;
	uInt32						m_UserID;

	T_EXCHANGE					m_ExchID;
	T_SECURITY_CODE				m_SecurityCode;
	uInt8						m_Reserved[6];
};

///期权细节查询(2007-24)
struct qmcs_opt_detail_list_req
{
	qmcs_opt_detail_list_req()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = qmcs_types::QMCS_OPT_DETAIL_LIST_REQ;
		m_Header.m_MsgLen = sizeof(*this);
		CHECK_SZ_ALIGN_TO_8;
	}
	msg_standard_hdr			m_Header;

	Int32						m_RequestID;
	uInt32						m_UserID;

	T_EXCHANGE					m_ExchID;
	T_SECURITY_CODE				m_UnderlyingSecurityCode;
	uInt8						m_Reserved[6];
};

///账户费率查询(2008-32)
struct qmcs_fee_query_req
{
	qmcs_fee_query_req()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = qmcs_types::QMCS_FEE_QUERY_REQ;
		m_Header.m_MsgLen = sizeof(*this);
		CHECK_SZ_ALIGN_TO_8;
	}
	msg_standard_hdr			m_Header;

	Int32						m_RequestID;
	uInt32						m_UserID;

	T_CUST_ID					m_ClientID;
	uInt8						m_Reserved[7];
};


///股票仓位查询(2009-32)
struct qmcs_normal_position_query_req
{
	qmcs_normal_position_query_req()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = qmcs_types::QMCS_NORMAL_POSITION_QUERY_REQ;
		m_Header.m_MsgLen = sizeof(*this);
		CHECK_SZ_ALIGN_TO_8;
	}
	msg_standard_hdr			m_Header;

	Int32						m_RequestID;
	uInt32						m_UserID;

	T_CUST_ID					m_ClientID;
	uInt8						m_Reserved[7];
};

///期权仓位查询(2009-32)
struct qmcs_option_position_query_req
{
	qmcs_option_position_query_req()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = qmcs_types::QMCS_OPTION_POSITION_QUERY_REQ;
		m_Header.m_MsgLen = sizeof(*this);
		CHECK_SZ_ALIGN_TO_8;
	}
	msg_standard_hdr			m_Header;

	Int32						m_RequestID;
	uInt32						m_UserID;

	T_CUST_ID					m_ClientID;
	uInt8						m_Reserved[7];
};

///交易信息rewind请求(2010-32)
struct qmcs_trade_rewind_req
{
	qmcs_trade_rewind_req()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = qmcs_types::QMCS_TRADE_REWIND_REQ;
		m_Header.m_MsgLen = sizeof(*this);
		assert(m_Header.m_MsgLen == 32);
	}
	msg_standard_hdr			m_Header;
	uInt32						m_UserID;
	T_CUST_ID					m_ClientID;
	uInt8						m_Reserved[3];
};

///客户号资金状态查询请求(2011-32)
struct qmcs_bp_query_req
{
	qmcs_bp_query_req()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = qmcs_types::QMCS_BP_QUERY_REQ;
		m_Header.m_MsgLen = sizeof(*this);
		assert(m_Header.m_MsgLen == 32);
	}
	msg_standard_hdr			m_Header;
	uInt32						m_UserID;
	T_CUST_ID					m_ClientID;
	uInt8						m_Reserved[3];
};

///交易所席位连接查询请求(2012-16)
struct qmcs_exch_sess_req
{
	qmcs_exch_sess_req()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = qmcs_types::QMCS_EXCH_SESS_REQ;
		m_Header.m_MsgLen = sizeof(*this);
		assert(m_Header.m_MsgLen == 16);
	}
	msg_standard_hdr			m_Header;
	uInt32						m_UserID;
	uInt8						m_Reserved[4];
};

///非symbol级风控累加值查询请求(2013-48)
struct qmcs_non_symbol_risk_accum_val_req
{
	qmcs_non_symbol_risk_accum_val_req()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = qmcs_types::QMCS_NON_SYMBOL_RISK_ACCUM_VAL_REQ;
		m_Header.m_MsgLen = sizeof(*this);
		assert(m_Header.m_MsgLen == 56);
	}
	msg_standard_hdr			m_Header;
	uInt32						m_UserID;
	T_CUST_ID			m_ClientID;
	T_FUND_ACCOUNT_TYPE			m_FundAccountType;
	T_FUND_ACCOUNT				m_FundAccount;
	uInt32						m_RequestID;
	uInt8						m_Reserved[5];
};

///symbol级风控累加值查询请求(2014-56)
struct qmcs_symbol_risk_accum_val_req
{
	qmcs_symbol_risk_accum_val_req()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = qmcs_types::QMCS_SYMBOL_RISK_ACCUM_VAL_REQ;
		m_Header.m_MsgLen = sizeof(*this);
		assert(m_Header.m_MsgLen == 64);
	}
	msg_standard_hdr			m_Header;
	uInt32						m_UserID;
	T_CUST_ID					m_ClientID;
	T_FUND_ACCOUNT_TYPE			m_FundAccountType;
	T_FUND_ACCOUNT				m_FundAccount;
	T_EXCHANGE					m_ExchangeID;
	T_SECURITY_CODE				m_SecurityCode;
	uInt32						m_RequestID;
	uInt8						m_Reserved[3];
};

/// 查询标的券数(2017-)
struct qmcs_qry_underlying_symbol_qty_req
{
	qmcs_qry_underlying_symbol_qty_req()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = qmcs_types::QMCS_QRY_UNDERLYING_SYMBOL_QTY_REQ;
		m_Header.m_MsgLen = sizeof(*this);
		//CHECK_SZ_ALIGN_TO_8;
	}
	msg_standard_hdr			m_Header;

	Int32						m_RequestID;
	uInt32						m_UserID;

	T_EXCHANGE					m_ExchangeID;
	T_CUST_ID					m_ClientID;
	T_FUND_ACCOUNT				m_FundAccount;
	T_SECURITY_CODE				m_SecurityCode;
	uInt8						m_Reserved[4];
};

/// 向主席锁定/解锁标的券数量(2018-)
struct qmcs_frz_underlying_symbol_qty_req
{
	qmcs_frz_underlying_symbol_qty_req()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = qmcs_types::QMCS_FRZ_UNDERLYING_SYMBOL_QTY_REQ;
		m_Header.m_MsgLen = sizeof(*this);
		//CHECK_SZ_ALIGN_TO_8;
	}
	msg_standard_hdr			m_Header;

	Int32						m_RequestID;
	uInt32						m_UserID;

	T_EXCHANGE					m_ExchangeID;
	T_FROZEN_FLAG				m_FrzFlag;
	T_CUST_ID					m_ClientID;
	T_FUND_ACCOUNT				m_FundAccount;
	T_SECURITY_CODE				m_SecurityCode;
	uInt8						m_Reserved[7];
	uInt32						m_Quantity;

	T_MSG_TEXT					m_Remark;
};


/// 同主席划入划出资金 (2019-)
struct qmcs_inout_fund_account_amount_req
{
	qmcs_inout_fund_account_amount_req()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = qmcs_types::QMCS_INOUT_FUND_ACCOUNT_AMOUNT_REQ;
		m_Header.m_MsgLen = sizeof(*this);
		//CHECK_SZ_ALIGN_TO_8;
	}
	msg_standard_hdr			m_Header;

	Int32						m_RequestID;
	uInt32						m_UserID;

	T_PRICE_4					m_Amount;

	T_FROZEN_FLAG				m_FrzFlag;
	T_CUST_ID					m_ClientID;
	T_FUND_ACCOUNT				m_FundAccount;
	uInt8						m_Reserved[5];

	T_MSG_TEXT					m_Remark;
};
/// 同其他节点划入划出资金 (2022-)
struct qmcs_out_fund_account_amount_node_req
{
	qmcs_out_fund_account_amount_node_req()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = qmcs_types::QMCS_OUT_FUND_ACCOUNT_AMOUNT_NODE_REQ;
		m_Header.m_MsgLen = sizeof(*this);
		//CHECK_SZ_ALIGN_TO_8;
	}
	msg_standard_hdr			m_Header;

	Int32						m_RequestID;
	uInt32						m_UserID;

	T_CUST_ID					m_ClientID;
	T_FUND_ACCOUNT				m_FundAccount;
	T_FUND_ACCOUNT_TYPE			m_FundAccountType;
	T_EXCHANGE					m_Exchange;
	uInt8						m_Reserved[4];
	T_PRICE_4					m_Amount;
};
/// 查询股东账户(2023-)
struct qmcs_trade_account_list_req
{
	qmcs_trade_account_list_req()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = qmcs_types::QMCS_TRADE_ACCOUNT_LIST_REQ;
		m_Header.m_MsgLen = sizeof(*this);
	}
	msg_standard_hdr			m_Header;
	uInt32						m_UserID;
	T_CUST_ID					m_ClientID;
	uInt8						m_Reserved[3];
};



//#END，Client查询

///#START，REM响应
///协议版本号校验回报(3000-16)
struct qmsc_protocol_version_resp
{
	qmsc_protocol_version_resp()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = qmsc_types::QMSC_PROTOCOL_VERSION_RESP;
		m_Header.m_MsgLen = sizeof(*this);
		assert(m_Header.m_MsgLen == 16);
	}
	msg_standard_hdr			m_Header;
	uInt32						m_ProtoVersion;
	uInt8						m_Reserved[4];
};

///登录请求回应(3001-80)
struct qmsc_logon_resp
{
	qmsc_logon_resp()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = qmsc_types::QMSC_LOGON_RESP;
		m_Header.m_MsgLen = sizeof(*this);
		assert(m_Header.m_MsgLen == 80);
	}
	msg_standard_hdr			m_Header;
	uInt32						m_ProtoVersion;
	T_REM_LOGON_RESULT			m_Result;
	T_SESSION_ID				m_TradeSessionID;
	uInt32						m_UserID;
	uInt32						m_TradingDate;
	uInt32						m_MaxClOrdToken;
	T_CUST_ID					m_DefClientID;
	uInt8						m_Reserved[5];
};

///  lgl 20180226
/// 查询端口登录请求回应
struct qmsc_query_logon_resp
{
	qmsc_query_logon_resp()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = qmsc_types::QMSC_QUERY_LOGON_RESP;
		m_Header.m_MsgLen = sizeof(*this);
		assert(m_Header.m_MsgLen == 529);
	}
	msg_standard_hdr		m_Header;
	uInt32					m_UserID;
	uInt8					m_Result;		/// 0 成功
	uInt8					m_Reserved[3];
	unsigned char			m_NeedRptr;
	char					m_RsaPubKey[512];
};

/// 心跳的回复消息
struct qmsc_heartbeat_resp
{
	qmsc_heartbeat_resp()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = qmsc_types::QMSC_HEARTBEAT_RESP;
		m_Header.m_MsgLen = sizeof(*this);
		assert(m_Header.m_MsgLen == 16);
	}
	msg_standard_hdr		m_Header;
	uInt32					m_UserID;
	uInt8					m_Reserved[4];
};

///修改密码响应(3002-16)
struct qmsc_change_password_resp
{
	qmsc_change_password_resp()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = qmsc_types::QMSC_CHANGE_PASSWORD_RESP;
		m_Header.m_MsgLen = sizeof(*this);
		assert(m_Header.m_MsgLen == 16);
	}
	msg_standard_hdr			m_Header;
	uInt32						m_UserID;
	T_CHANGE_PWD_RESULT			m_Result;
	uInt8						m_Reserved[3];
};

///客户号列表查询响应(3003-40)
struct qmsc_client_id_list_resp
{
	qmsc_client_id_list_resp()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = qmsc_types::QMSC_CLIENT_ID_LIST_RESP;
		m_Header.m_MsgLen = sizeof(*this);
		CHECK_SZ_ALIGN_TO_8;
	}
	msg_standard_hdr			m_Header;

	Int32						m_RequestID;
	T_LAST_RECORD_FLAG			m_LastRecordFlag;
	uInt8						m_Reserved1[3];

	uInt32						m_UserID;
	//目前没有 不过可以在customter_mgr_impl::load_node_cust_acct;里面加上				/// < 名字
	T_CUST_ID					m_ClientID;
	T_CUST_NAME					m_CustName;
	T_BRANCH_ID					m_BranchID;//	customter_unit::get_branch_id				/// < 营业部
	uInt8						m_Reserved2[2];

	uInt64						m_Previlege;
};

///资金账户列表查询响应(3004-56)
struct qmsc_fund_account_list_resp
{
	qmsc_fund_account_list_resp()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = qmsc_types::QMSC_FUND_ACCOUNT_LIST_RESP;
		m_Header.m_MsgLen = sizeof(*this);
		CHECK_SZ_ALIGN_TO_8;
	}
	msg_standard_hdr			m_Header;

	Int32						m_RequestID;
	T_LAST_RECORD_FLAG			m_LastRecordFlag;
	uInt8						m_Reserved1[3];

	uInt32						m_UserID;
	T_FUND_ACCOUNT_TYPE			m_FundAccountType;
	T_ACCOUNT_PREVILEGE			m_Previlege;
	T_ACCOUNT_FINANCHING_EXERCISE m_AccountFinanchingExercise;  ///< 是否融资行权  //fund_account_unit::get_finanching_exercise
	T_CUST_ID					m_ClientID;
	T_FUND_ACCOUNT				m_FundAccount;
	T_FUND_ACCOUNT_NAME			m_CustAcctName;  			//目前没有 不过可以在customter_mgr_impl::load_node_cust_acct;里面加上	
	uInt8						m_Reserved2[7];
};

///证券代码列表查询响应(3005-24)
struct qmsc_security_code_list_resp
{
	qmsc_security_code_list_resp()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = qmsc_types::QMSC_SECURITY_CODE_LIST_RESP;
		m_Header.m_MsgLen = sizeof(*this);
		CHECK_SZ_ALIGN_TO_8;
	}
	msg_standard_hdr			m_Header;

	Int32						m_RequestID;
	T_LAST_RECORD_FLAG			m_LastRecordFlag;
	uInt8						m_Reserved1[3];

	uInt32						m_UserID;
	T_SECURITY_CODE				m_SecurityCode;
	T_SECURITY_NAME				m_SecurityName;
	uInt8						m_Reserved2[3];

	T_SECU_FULL_TYPE			m_SecurityFullType;
	T_EXCHANGE					m_ExchID;
	T_COVER_TODAY_FLAG			m_CoverTodayFlag;
	uInt8						m_Reserved3[4];

	///在对应的数据获取部分的的结构体里面对应的数据都有
	double						m_ParValue; ///< 面值	`par_value` DECIMAL(15, 3) NULL DEFAULT NULL,
	uInt32						m_BuyMinQty; ///< 买最小数量	`buy_min_qty` INT(10) UNSIGNED NULL DEFAULT NULL,
	uInt32						m_SellMinQty;///< 卖最小数量	`sell_min_qty` INT(10) UNSIGNED NULL DEFAULT NULL,
	uInt32						m_MinOrderQty; ///< 单个订单最小委托数量	`min_order_qty` INT(10) UNSIGNED NULL DEFAULT NULL,
	uInt32						m_MaxOrderQty; ///< 单个订单最大委托数量	`max_order_qty` INT(10) UNSIGNED NULL DEFAULT NULL,
	double						m_PreClosePrice; ///< 昨收价	`pre_close_price` DECIMAL(11, 3) UNSIGNED NULL DEFAULT NULL,
	double						m_MinTickPrice; ///< 最小价格变动	`min_tick_price` DECIMAL(11, 3) UNSIGNED NULL DEFAULT NULL,
	double						m_UpLimitPrice; ///< 涨停价	`up_limit_price` DECIMAL(11, 3) NULL DEFAULT NULL,
	double						m_LowLimitPrice; ///< 跌停价	`low_limit_price` DECIMAL(11, 3) NULL DEFAULT NULL,
	fix_str<4>					m_Currency; 	///< 币种	`currency` VARCHAR(3) NULL DEFAULT NULL,
	char						m_IsFinancing; ///< 是否可融资	`is_financing` CHAR(1) NULL DEFAULT NULL,
	char						m_IsLending;  ///< 是否可融券	`is_lending` CHAR(1) NULL DEFAULT NULL,

	uInt8						m_Reserved4[2];
};

/// ETF信息查询
struct qmsc_etf_list_resp
{
	// 这个是新添加的查询，原来没有的

	///<	`exchange` INT(11) NOT NULL COMMENT '交易所',
	///<	`secu_code` VARCHAR(8) NOT NULL COMMENT 'ETF代码',
	///<	`secu_name` VARCHAR(54) NULL DEFAULT NULL COMMENT '证券名称',
	///<	`fund_management_comp` VARCHAR(54) NULL DEFAULT NULL COMMENT '基金公司名称',
	///<	`underlyin_secu_code` VARCHAR(8) NULL DEFAULT NULL COMMENT '拟合指数代码',
	///<	`exchange_under_secu_code` INT(11) NULL DEFAULT NULL COMMENT '拟合指数代码交易所',
	///<	`creation_redemption_unit` DECIMAL(15, 2) NULL DEFAULT NULL COMMENT '最小申赎单位',
	///<	`estimate_cash_component` DECIMAL(11, 2) NULL DEFAULT NULL COMMENT '预估现金差额',
	///<	`max_cash_ratio` DECIMAL(6, 5) NULL DEFAULT NULL COMMENT '最大现金替代比例 ',
	///<	`publish_iopv` CHAR(1) NULL DEFAULT NULL COMMENT '是否发布iopv',
	///<	`can_creation` CHAR(1) NULL DEFAULT NULL COMMENT '是否允许申购',
	///<	`can_redemption` CHAR(1) NULL DEFAULT NULL COMMENT '是否允许赎回',
	///<	`sze_record_num` INT(11) NULL DEFAULT NULL COMMENT '深市成份证券数目',
	///<	`total_record_num` INT(11) NULL DEFAULT NULL COMMENT '所有成份证券数目',
	///<	`trading_date` DATE NULL DEFAULT NULL COMMENT '交易日',
	///<	`pre_trading_date` DATE NULL DEFAULT NULL COMMENT '前交易日',
	///<	`cash_component` DECIMAL(11, 2) NULL DEFAULT NULL COMMENT '现金余额',
	///<	`nav_per_cu` DECIMAL(12, 2) NULL DEFAULT NULL COMMENT '申购赎回基准单位净值',
	///<	`creation_limit` DECIMAL(18, 2) NULL DEFAULT NULL COMMENT '累计申购总额限制',
	///<	`redemption_limit` DECIMAL(18, 2) NULL DEFAULT NULL COMMENT '累计赎回总额限制',
	///<	`creation_limit_user` DECIMAL(18, 2) NULL DEFAULT NULL COMMENT '单个账户累计申购总额限制 ',
	///<	`redeption_limit_user` DECIMAL(18, 2) NULL DEFAULT NULL COMMENT '单个账户累计赎回总额限制',
	///<	`net_creation_limit` DECIMAL(18, 2) NULL DEFAULT NULL COMMENT '净申购总额限制',
	///<	`net_redemption_limit` DECIMAL(18, 2) NULL DEFAULT NULL COMMENT '净赎回总额限制',
	///<	`net_creation_limit_user` DECIMAL(18, 2) NULL DEFAULT NULL COMMENT '单个账户净申购总额限制',
	///<	`net_redemption_limit_user` DECIMAL(18, 2) NULL DEFAULT NULL COMMENT '单个账户净赎回总额限制',

};

///ETF成份股查询响应(3006-56)
struct qmsc_etf_member_list_resp
{
	qmsc_etf_member_list_resp()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = qmsc_types::QMSC_ETF_MEMBER_LIST_RESP;
		m_Header.m_MsgLen = sizeof(*this);
		CHECK_SZ_ALIGN_TO_8;
	}
	msg_standard_hdr			m_Header;

	Int32						m_RequestID;
	T_LAST_RECORD_FLAG			m_LastRecordFlag;
	uInt8						m_Reserved1[3];

	uInt32						m_UserID;
	T_EXCHANGE					m_ExchID;
	T_SECURITY_CODE				m_SecurityCode;
	T_SECURITY_CODE				m_MemberSecurityCode;
	uInt8						m_Reserved2;

	T_EXCHANGE					m_MemberExchID;
	uInt8						m_Reserved3[7];
	uInt32						m_ComponentShare;				// 成份证券数
	uInt32						m_SubstituteFlag;				// 现金替代标志,
	T_RATE64_4					m_PermiumRatio;					//  '溢价比例',
	T_RATE64_4					m_DiscountRatio;				// 折价比例
	T_AMOUNT_4					m_CreationCashSubstitute;		// 申购替代金额',
	T_AMOUNT_4					m_RedemptionCashSubstitute;		//  '赎回替代金额',	
};

///期权细节查询响应(3007-80)
struct qmsc_opt_detail_list_resp
{
	qmsc_opt_detail_list_resp()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = qmsc_types::QMSC_OPT_DETAIL_LIST_RESP;
		m_Header.m_MsgLen = sizeof(*this);
		CHECK_SZ_ALIGN_TO_8;
	}
	msg_standard_hdr			m_Header;

	Int32						m_RequestID;
	T_LAST_RECORD_FLAG			m_LastRecordFlag;
	uInt8						m_Reserved1[3];

	uInt32						m_UserID;
	T_EXCHANGE					m_ExchID;
	T_EXCHANGE					m_UnderlyingExchID;
	T_OPT_CALL_PUT				m_CallOrPut;
	T_SECURITY_CODE				m_SecurityCode;
	T_REASON_TEXT				m_SecurityName;
	T_SECURITY_CODE				m_UnderlyingSecurityCode;
	T_CONTRACT_ACCOUNT_CODE		m_ContractAccountCode;
	T_OPT_CONTRACT_ID			m_ContractID;
	uInt8						m_Reserved2[3];

	T_PRICE_4					m_StrikePrice;

	///在对应的数据获取部分的的结构体里面对应的数据都有
	T_SECU_FULL_TYPE			m_SecuFullType;					 ///< 类型	`secu_type` TINYINT(4) NOT NULL DEFAULT '9',
																 ///< 子类型	`secu_sub_type` TINYINT(4) NOT NULL DEFAULT '0',
	uInt8						m_Reserved3[6];

	T_SECURITY_NAME				m_UnderlyingSymbol; ///< 标的物名称	`underlying_symbol` VARCHAR(8) NOT NULL,

	T_SECU_FULL_TYPE			m_UnderlyingSecuFullType;							///<	`underlying_secu_type` TINYINT(4) UNSIGNED NOT NULL,
																					///<	`underlying_secu_sub_type` TINYINT(4) NOT NULL,
	char						m_OptionType;              	///<	`option_type` ENUM('E', 'A') NULL DEFAULT NULL,
	uInt8						m_Reserved4;
	uInt32						m_VolMultipler;  ///<	`vol_multipler` INT(11) UNSIGNED NOT NULL DEFAULT '10000',

	int							m_StartDate;///<	`start_date` VARCHAR(8) NOT NULL,
	int							m_EndDate;	///<	`end_date` VARCHAR(8) NOT NULL,
	int							m_ExerciseDate;	///<	`exercise_date` VARCHAR(8) NOT NULL,
	int							m_DeliveryDate;	   	///<	`delivery_date` VARCHAR(8) NOT NULL,
	int							m_ExpireDate;///<	`expire_date` VARCHAR(8) NOT NULL,
	char						m_UpdateVersion; ///<	`update_version` CHAR(1) NOT NULL,
	char						m_DailyPriceUpLimit; ///< 	`daily_price_up_limit` DECIMAL(11, 4) NOT NULL,
	uInt8						m_Reserved5[2];
	Int64						m_TotalLongPosition; ///<	`total_long_position` INT(12) NOT NULL,
	double						m_SecurityClosePx; ///<	`security_close_px` DECIMAL(11, 4) NOT NULL,
	double						m_SettlePrice; ///<	`settle_price` DECIMAL(11, 4) NOT NULL,
	double						m_UnderlyingClosePx; ///<	`underlying_close_px` DECIMAL(11, 4) NOT NULL,
	double						m_DailyPriceDownLimit; ///< 	`daily_price_down_limit` DECIMAL(11, 4) NOT NULL,

	Int64						m_LmtOrdMinFloor; ///< 限价最小委托数量	`lmt_ord_min_floor` INT(12) NOT NULL,
	Int64						m_LmtOrdMaxFloor; ///< 限价最大委托数量	`lmt_ord_max_floor` INT(12) NOT NULL,
	Int64						m_MktOrdMinFloor; ///< 市价最小委托数量	`mkt_ord_min_floor` INT(12) NOT NULL,
	Int64						m_MktOrdMaxFloor; ///< 市价最大委托数量	`mkt_ord_max_floor` INT(12) NOT NULL,
	double						m_TickSize; ///< 最小价格变动	`tick_size` DECIMAL(11, 4) NOT NULL,

};

///账户费率查询响应(3008)
struct qmsc_fee_query_resp
{
	qmsc_fee_query_resp()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = qmsc_types::QMSC_FEE_QUERY_RESP;
		m_Header.m_MsgLen = sizeof(*this);
		CHECK_SZ_ALIGN_TO_8;
	}
	msg_standard_hdr			m_Header;

	Int32						m_RequestID;
	T_LAST_RECORD_FLAG			m_LastRecordFlag;
	uInt8						m_Reserved1[3];

	uInt32						m_UserID;
	uInt8						m_Reserved2[4];

	hwcm_fee_config_body		m_FeeConfigBody;
	uInt8						m_Reserved3[NEED_SZ_ALIGN_TO_8(sizeof(hwcm_fee_config_body))];
};


///证券仓位信息，完整结构体，可用于表示股票/ETF/仓位
struct normal_position_info
{
	normal_position_info()
	{
		memset(this, 0, sizeof(*this));
	}
	//股票/ETF属性，均为多头
	uInt32				m_InitOvnQty;//初始昨仓量	
	uInt32				m_CurOvnQty;//剩余昨仓, 所持量, 不考虑备兑锁定, 平仓锁定等
	uInt32				m_CurQty;//总仓位，包括今仓, 所持量, 不考虑备兑锁定, 平仓锁定等
	uInt32				m_AvailQty;//总可平仓数量, 考虑所有锁定数量
	uInt32				m_OvnCoveredLockedQty;//备兑锁定量中昨仓部分
	uInt32				m_CoveredLockedQty;//总备兑锁定量
	uInt32				m_OvnCoveredLockPendingQty;//备兑锁定挂单量中，影响昨仓的部分。
	uInt32				m_CoveredLockPendingQty;//总备兑锁定挂单量
	uInt32				m_CoveredPledgedQty;//备兑担保量
	uInt32				m_CoveredNotEnoughQty;//备兑不足量
	uInt32				m_AvailCoveredQty; //	可用于开备兑的量
	uInt32				m_CoveredUnlockPendingQty;//总备兑解锁挂单量
	uInt32				m_ClosePosPendingQty;	//总平仓挂单量
	double				m_AvgPx;
	uInt8				m_Reserved1[32];//预留


};


///期权仓位信息，完整结构体，
struct option_position_info
{
	option_position_info()
	{
		memset(this, 0, sizeof(*this));
	}

	T_EXCHANGE			m_UnderlyingExchID;
	T_SECURITY_CODE		m_UnderlyingSecurityCode;
	T_SECU_FULL_TYPE	m_UnderlyingSecurityFullType;

	//期权属性, 多仓
	uInt32				m_OptLongInitOvnQty;//初始昨仓
	uInt32				m_OptLongCurQty;//当前仓位
	uInt32				m_OptLongAvailQty;//当前可平仓位
	double				m_OptLongAvgPx;
	double				m_OptLongBcost;
	double				m_OptLongMktVal;
	double				m_OptLongPremium;
	uInt32				m_OptLongOpeningQty;
	uInt32				m_OptLongCoveringQty;


	//期权属性, 空仓
	uInt32				m_OptShortInitOvnQty;// 初始昨仓
	uInt32				m_OptShortCurQty;// 当前仓位
	uInt32				m_OptShortAvailQty;// 当前可平仓位
	double				m_OptShortMargin; // 空仓的占用保证金
	double				m_OptShortExchangeMargin;				//option_position_one_side_info::get_exchange_margin	(可以获取)   ///< 交易所占用保证金;
	double				m_OptShortAvgPx;
	double				m_OptShortBcost;
	double				m_OptShortMktVal;
	double				m_OptShortPremium;
	uInt32				m_OptShortOpeningQty;
	double				m_OptShortOpeningFrozenBp;			//option_position_one_side_info::get_opending_frozen_bp		(可以获取)		///< 开仓中冻结保证金金额
															//option_position_one_side_info::get_opening_pos 				///< 开仓中数量
	uInt32				m_OptShortCoveringQty;

	//期权属性, 备兑仓
	uInt32				m_OptCoveredInitOvnQty;//初始昨仓
	uInt32				m_OptCoveredCurQty;//当前仓位
	uInt32				m_OptCoveredAvailQty;//当前可平仓位
	double				m_OptCoveredAvgPx;
	double				m_OptCoveredBcost;
	double				m_OptCoveredMktVal;
	double				m_OptCoveredPremium;
	uInt32				m_OptCoveredOpeningQty;
	uInt32				m_OptCoveredCoveringQty;

	uInt8				m_Reserved2[24];//预留
};


///仓位列表查询响应(3009)
struct qmsc_position_query_normal_resp
{
	qmsc_position_query_normal_resp()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = qmsc_types::QMSC_NORMAL_POSITION_QUERY_RESP;
		m_Header.m_MsgLen = sizeof(*this);
		assert(m_Header.m_MsgLen == 156);
	}
	msg_standard_hdr			m_Header;
	T_LAST_RECORD_FLAG			m_LastRecordFlag;
	uInt32						m_UserID;
	uInt8						m_Reserved[3];
	T_CUST_ID					m_ClientID;
	T_FUND_ACCOUNT_TYPE			m_FundAccountType;
	T_FUND_ACCOUNT				m_FundAccount;
	T_EXCHANGE					m_ExchID;
	T_SECURITY_CODE				m_SecurityCode;
	T_SECU_FULL_TYPE			m_SecurityFullType;
	uInt8						m_Reserved1;
	normal_position_info		m_PositionInfo;
};

///期权仓位列表查询响应(2029)
struct qmsc_option_position_query_resp
{
	qmsc_option_position_query_resp()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = qmsc_types::QMSC_OPTION_POSITION_QUERY_RESP;
		m_Header.m_MsgLen = sizeof(*this);
		CHECK_SZ_ALIGN_TO_8;
	}
	msg_standard_hdr			m_Header;

	Int32						m_RequestID;
	T_LAST_RECORD_FLAG			m_LastRecordFlag;
	uInt8						m_Reserved1[3];

	uInt32						m_UserID;
	T_CUST_ID					m_ClientID;
	T_FUND_ACCOUNT				m_FundAccount;
	T_SECURITY_CODE				m_SecurityCode;
	uInt8						m_Reserved2;

	T_SECU_FULL_TYPE			m_SecurityFullType;
	T_FUND_ACCOUNT_TYPE			m_FundAccountType;
	T_EXCHANGE					m_ExchID;
	uInt8						m_Reserved3[4];

	option_position_info		m_PositionInfo;
	uInt8						m_Reserved4[NEED_SZ_ALIGN_TO_8(sizeof(option_position_info))];
};

///期权仓位列表查询响应(3009)
struct qmsc_normal_position_query_resp
{
	qmsc_normal_position_query_resp()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = qmsc_types::QMSC_NORMAL_POSITION_QUERY_RESP;
		m_Header.m_MsgLen = sizeof(*this);
		CHECK_SZ_ALIGN_TO_8;
	}
	msg_standard_hdr			m_Header;

	Int32						m_RequestID;
	T_LAST_RECORD_FLAG			m_LastRecordFlag;
	uInt8						m_Reserved1[3];

	uInt32						m_UserID;
	T_CUST_ID					m_ClientID;
	T_FUND_ACCOUNT				m_FundAccount;
	T_SECURITY_CODE				m_SecurityCode;
	uInt8						m_Reserved2;

	T_SECU_FULL_TYPE			m_SecurityFullType;
	T_FUND_ACCOUNT_TYPE			m_FundAccountType;
	T_EXCHANGE					m_ExchID;
	uInt8						m_Reserved3[4];

	normal_position_info		m_PositionInfo;
	uInt8						m_Reserved4[NEED_SZ_ALIGN_TO_8(sizeof(normal_position_info))];
};

///订单rewind响应(3010)
struct qmsc_order_rewind_resp
{
	qmsc_order_rewind_resp()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = qmsc_types::QMSC_ORDER_REWIND_RESP;
		m_Header.m_MsgLen = sizeof(*this);
		assert(m_Header.m_MsgLen == sizeof(msg_standard_hdr) + sizeof(client_accept_order_body));
	}
	msg_standard_hdr			m_Header;
	client_accept_order_body	m_ClientAcceptBody;
};

///成交rewind响应(3011)
struct qmsc_exec_rewind_resp
{
	qmsc_exec_rewind_resp()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = qmsc_types::QMSC_EXEC_REWIND_RESP;
		m_Header.m_MsgLen = sizeof(*this);
		assert(m_Header.m_MsgLen == sizeof(msg_standard_hdr) + sizeof(client_exec_body));
	}
	msg_standard_hdr			m_Header;
	client_exec_body			m_ExecBody;
};

///撤单请求rewind响应(3012)
struct qmsc_cxl_req_rewind_resp
{
	qmsc_cxl_req_rewind_resp()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = qmsc_types::QMSC_CXL_REQ_REWIND_RESP;
		m_Header.m_MsgLen = sizeof(*this);
		assert(m_Header.m_MsgLen == sizeof(msg_standard_hdr) + sizeof(client_cxled_body));
	}
	msg_standard_hdr			m_Header;
	client_cxled_body			m_ClientCxledBody;
};

///客户号订单rewind完成消息(3013-32)
struct qmsc_order_rewind_finish
{
	qmsc_order_rewind_finish()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = qmsc_types::QMSC_ORDER_REWIND_FINISH;
		m_Header.m_MsgLen = sizeof(*this);
		assert(m_Header.m_MsgLen == 32);
	}
	msg_standard_hdr			m_Header;
	uInt32						m_UserID;
	T_CUST_ID			m_ClientID;
	uInt8						m_Reserved[3];
};

///客户号成交rewind完成消息(3014-32)
struct qmsc_exec_rewind_finish
{
	qmsc_exec_rewind_finish()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = qmsc_types::QMSC_EXEC_REWIND_FINISH;
		m_Header.m_MsgLen = sizeof(*this);
		assert(m_Header.m_MsgLen == 32);
	}
	msg_standard_hdr			m_Header;
	uInt32						m_UserID;
	T_CUST_ID			m_ClientID;
	uInt8						m_Reserved[3];
};

///客户号撤单请求rewind完成消息(3015-32)
struct qmsc_cxl_req_rewind_finish
{
	qmsc_cxl_req_rewind_finish()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = qmsc_types::QMSC_CXL_REQ_REWIND_FINISH;
		m_Header.m_MsgLen = sizeof(*this);
		assert(m_Header.m_MsgLen == 32);
	}
	msg_standard_hdr			m_Header;
	uInt32						m_UserID;
	T_CUST_ID			m_ClientID;
	uInt8						m_Reserved[3];
};

///客户号资金状态查询响应(3016-)
struct qmsc_bp_query_resp
{
	qmsc_bp_query_resp()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = qmsc_types::QMSC_BP_QUERY_RESP;
		m_Header.m_MsgLen = sizeof(*this);
		assert(m_Header.m_MsgLen == 136);
	}
	msg_standard_hdr			m_Header;
	uInt32						m_UserID;
	T_CUST_ID					m_ClientID;
	T_FUND_ACCOUNT				m_FundAccount;
	T_PRICE_4					m_InitialBp;
	T_PRICE_4					m_AvailableBp;
	T_LAST_RECORD_FLAG			m_LastRecordFlag;


	double m_FrozenMargin;  ///< 开仓冻结保证金 //i_buying_power_mgr::get_frozen_margin();
	double m_FrozePremium;///< 开仓冻结权限金 //i_buying_power_mgr::get_froze_premium();
	double m_FrozeFee; ///< 开仓冻结费用 //i_buying_power_mgr::get_frozen_fee();
	double m_IncomePreminm; ///< 收权利金                   //i_buying_power_mgr::get_income_premium();       
	double m_OutcomePreminm; ///< 支出权利金//i_buying_power_mgr::get_outcome_premium();   
	double m_MarginInclRlt; ///< 持仓占用保证金 //i_buying_power_mgr::get_margin_incl_rlt();
	double m_ExchangeAvailBp; ///< 交易所可用资金  //i_buying_power_mgr::get_exchange_avail_bp()
	double m_TotalFee; ///< 总费用   //i_buying_power_mgr:: get_commission_fee() +  get_frozen_fee() 已经扣除的手续费加上锁定的手续费
	double m_TotalFundBln;///< 总权益	//i_buying_power_mgr::get_fund_bln() 据说是权益 代码上的注释是当前余额
	uInt8						m_Reserved;
};

///交易所连接查询响应(3017-272)
struct qmsc_exch_sess_resp
{
	qmsc_exch_sess_resp()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = qmsc_types::QMSC_EXCH_SESS_RESP;
		m_Header.m_MsgLen = sizeof(*this);
		assert(m_Header.m_MsgLen == 272);
	}
	msg_standard_hdr			m_Header;
	T_LAST_RECORD_FLAG			m_LastRecordFlag;
	uInt32						m_UserID;
	T_EXCHANGE					m_ExchID;
	uInt8						m_SessionCount;
	uInt8						m_SessionIDList[255];
	uInt8						m_Reserved[2];
};

///交易所状态变化报告(3018-16)
struct qmsc_exch_sess_status_report
{
	qmsc_exch_sess_status_report()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = qmsc_types::QMSC_EXCH_SESS_STATUS_REPORT;
		m_Header.m_MsgLen = sizeof(*this);
		assert(m_Header.m_MsgLen == 16);
	}
	msg_standard_hdr			m_Header;
	T_EXCHANGE					m_ExchID;
	uInt8						m_SessionID;//1-255
	T_SESSION_STATUS			m_SessionStatus;
	uInt8						m_Reserved[5];
};


///ETF成交rewind响应(3019)
struct qmsc_etf_exec_rewind_resp
{
	qmsc_etf_exec_rewind_resp()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = qmsc_types::QMSC_ETF_EXEC_REWIND_RESP;
		m_Header.m_MsgLen = sizeof(*this);
		assert(m_Header.m_MsgLen == sizeof(msg_standard_hdr) + sizeof(client_etf_exec_body));
	}
	msg_standard_hdr			m_Header;
	client_etf_exec_body		m_ClientEtfExecBody;
};

//非symbol级风控累加值查询响应(3020-128)
struct qmsc_non_symbol_risk_accum_val_resp
{
	qmsc_non_symbol_risk_accum_val_resp()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = qmsc_types::QMSC_NON_SYMBOL_RISK_ACCUM_VAL_RESP;
		m_Header.m_MsgLen = sizeof(*this);
		assert(m_Header.m_MsgLen == 128);
	}
	msg_standard_hdr			m_Header;
	uInt32						m_UserID;
	T_CUST_ID			m_ClientID;
	T_FUND_ACCOUNT_TYPE			m_FundAccountType;
	T_FUND_ACCOUNT				m_FundAccount;
	uInt32						m_RequestID;
	uInt16						m_ReasonCode;
	uInt8						m_Reserved[3];
	T_PRICE_4					m_Rule1Value;
	uInt64						m_Rule8Value;
	uInt64						m_Rule9Value;
	uInt64						m_Rule10Value;
	uInt64						m_Rule11Value;
	uInt64						m_Rule12Value;
	uInt64						m_Rule13Value;
	T_PRICE_4					m_Rule34Value;
	T_PRICE_4					m_Rule35Value;
};



//symbol级风控累加值查询响应(3021-152)
struct qmsc_symbol_risk_accum_val_resp
{
	qmsc_symbol_risk_accum_val_resp()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = qmsc_types::QMSC_SYMBOL_RISK_ACCUM_VAL_RESP;
		m_Header.m_MsgLen = sizeof(*this);
		assert(m_Header.m_MsgLen == 152);
	}
	msg_standard_hdr			m_Header;
	uInt32						m_UserID;
	T_CUST_ID			m_ClientID;
	T_FUND_ACCOUNT_TYPE			m_FundAccountType;
	T_FUND_ACCOUNT				m_FundAccount;
	T_SECURITY_CODE				m_SecurityCode;
	uInt32						m_RequestID;
	uInt16						m_ReasonCode;
	uInt8						m_Reserved[2];
	uInt64						m_Rule36Value;
	uInt64						m_Rule37Value;
	uInt64						m_Rule38Value;
	uInt64						m_Rule39Value;
	uInt64						m_Rule40Value;
	uInt64						m_Rule41Value;
	uInt64						m_Rule42Value;
	uInt64						m_Rule43Value;
	uInt64						m_Rule44Value;
	uInt64						m_Rule45Value;
	uInt64						m_Rule46Value;
};

/// 查询可锁券数量返回(3024-)
struct qmsc_qry_underlying_symbol_qty_resp
{
	qmsc_qry_underlying_symbol_qty_resp()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = qmsc_types::QMSC_QRY_UNDERLYING_SYMBOL_QTY_RESP;
		m_Header.m_MsgLen = sizeof(*this);
		//CHECK_SZ_ALIGN_TO_8;
	}
	msg_standard_hdr			m_Header;

	Int32						m_RequestID;
	uInt32						m_UserID;

	T_CUST_ID					m_ClientID;
	T_FUND_ACCOUNT				m_FundAccount;
	T_SECURITY_CODE				m_SecurityCode;
	T_EXCHANGE					m_ExchangeID;
	uInt8						m_Reserved1[4];

	uInt32						m_Quantity;
	uInt32						m_Result;
	T_MSG_TEXT					m_MsgText;
};

/// 向主席请求锁定、解锁标的券 (3025-)
struct qmsc_frz_underlying_symbol_qty_resp
{
	qmsc_frz_underlying_symbol_qty_resp()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = qmsc_types::QMSC_FRZ_UNDERLYING_SYMBOL_QTY_RESP;
		m_Header.m_MsgLen = sizeof(*this);
		//CHECK_SZ_ALIGN_TO_8;
	}
	msg_standard_hdr			m_Header;

	Int32						m_RequestID;
	uInt32						m_UserID;

	T_CUST_ID					m_ClientID;
	T_FUND_ACCOUNT				m_FundAccount;
	T_SECURITY_CODE				m_SecurityCode;
	T_EXCHANGE					m_ExchangeID;
	T_FROZEN_FLAG				m_FrzFlag;
	uInt8						m_Reserved1[3];

	uInt32						m_Quantity;
	uInt32						m_Result;
	T_MSG_TEXT					m_MsgText;
};

/// 同主席资金划拔返回(3026-)
struct qmsc_inout_fund_account_amount_resp
{
	qmsc_inout_fund_account_amount_resp()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = qmsc_types::QMSC_INOUT_FUND_ACCOUNT_AMOUNT_RESP;
		m_Header.m_MsgLen = sizeof(*this);
		//CHECK_SZ_ALIGN_TO_8;
	}
	msg_standard_hdr			m_Header;

	Int32						m_RequestID;
	uInt32						m_UserID;

	uInt32						m_Result;
	T_CUST_ID					m_ClientID;
	T_FUND_ACCOUNT				m_FundAccount;
	T_FROZEN_FLAG				m_FrzFlag;
	uInt8						m_Reserved1;

	T_PRICE_4					m_Amount;
	T_MSG_TEXT					m_MsgText;
};
/// 向其他节点资金划拔返回(3030-)
struct qmsc_out_fund_account_amount_node_resp
{
	qmsc_out_fund_account_amount_node_resp()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = qmsc_types::QMSC_OUT_FUND_ACCOUNT_AMOUNT_NODE_RESP;
		m_Header.m_MsgLen = sizeof(*this);
		//CHECK_SZ_ALIGN_TO_8;	
	}
	msg_standard_hdr			m_Header;

	Int32						m_RequestID;
	uInt32						m_UserID;

	uInt32						m_Result;
	T_CUST_ID					m_ClientID;
	T_FUND_ACCOUNT				m_FundAccount;
	T_FUND_ACCOUNT_TYPE			m_FundAccountType;
	T_EXCHANGE					m_Exchange;
	uInt8						m_Reserved1[2];

	T_PRICE_4					m_Amount;
	T_MSG_TEXT					m_MsgText;
};


///资金账户列表查询响应(3031-)
struct qmsc_trade_account_list_resp
{
	qmsc_trade_account_list_resp()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = qmsc_types::QMSC_TRADE_ACCOUNT_LIST_RESP;
		m_Header.m_MsgLen = sizeof(*this);
	}
	msg_standard_hdr			m_Header;
	T_LAST_RECORD_FLAG			m_LastRecordFlag;
	uInt32						m_UserID;
	T_CUST_ID					m_ClientID;
	T_FUND_ACCOUNT				m_FundAccount;
	T_FUND_ACCOUNT_TYPE			m_FundAccountType;
	T_TRADE_ACCOUNT				m_TradeAccount;
	T_EXCHANGE					m_Exchanage;
};


/// 消息通知
struct hwcm_system_msg_report
{
	hwcm_system_msg_report()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = qmsc_types::QMSC_SYSTEM_MSG_REPORT;
		m_Header.m_MsgLen = sizeof(*this);
		assert(m_Header.m_MsgLen == 324);
	}
	msg_standard_hdr			m_Header;
	uInt32						m_UserID;
	T_CUST_ID					m_ClientID;
	fix_str<7>					m_Reserved1; //	保留
	T_FUND_ACCOUNT				m_FundAccount;
	fix_str<7>					m_Reserved2; //	保留
	Int32						m_MsgType;
	Int32						m_MsgCode;
	fix_str<256>				m_MsgText;
};

//#END，REM响应
//#END，Client查询类和响应类


#pragma pack(pop)




