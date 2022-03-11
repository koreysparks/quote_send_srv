#pragma once


#pragma pack(push, 1)
///#START，交易类，内部通道
///#START，交易类内部，软件发给硬件
///前缀tmsh: Trade Message, Software to Hardware
 
///回滚订单状态(4000-32)
struct tmsh_rewind_status
{
	tmsh_rewind_status()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = tmsh_types::TMSH_REWIND_STATUS;
		m_Header.m_MsgLen = sizeof(*this);
		assert(m_Header.m_MsgLen == sizeof(msg_standard_hdr) + 24);
	}
	msg_standard_hdr			m_Header;
	T_REWIND_STATUS				m_RewindStatus;
	uInt8						m_Reserved[7];
	T_EXCHANGE_ORDER_TOKEN		m_MaxExchangeOrderToken;
};

//回滚订单(4001-384)
struct tmsh_rewind_order
{
	tmsh_rewind_order()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = tmsh_types::TMSH_REWIND_ORDER;
		m_Header.m_MsgLen = sizeof(*this);
		assert(m_Header.m_MsgLen == sizeof(msg_standard_hdr) + sizeof(order_snapshot_body) + sizeof(T_PRICE_4));
	}
	msg_standard_hdr			m_Header;
	order_snapshot_body			m_OrderSnapshotBody;
	T_PRICE_4					m_TotalFilledAmount;
};

//回滚成交数据(4002-160)
struct tmsh_rewind_execution
{
	tmsh_rewind_execution()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = tmsh_types::TMSH_REWIND_EXECUTION;
		m_Header.m_MsgLen = sizeof(*this);
		assert(m_Header.m_MsgLen == sizeof(msg_standard_hdr) + sizeof(exec_snapshot_body));
	}
	msg_standard_hdr			m_Header;
	exec_snapshot_body			m_ExecSnapshotBody;
};

//回滚撤单请求(4003-248)
struct tmsh_rewind_cxl_req
{
	tmsh_rewind_cxl_req()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = tmsh_types::TMSH_REWIND_CXL_REQ;
		m_Header.m_MsgLen = sizeof(*this);
		assert(m_Header.m_MsgLen == sizeof(msg_standard_hdr) + sizeof(cxl_req_snapshot_body));
	}
	msg_standard_hdr			m_Header;
	cxl_req_snapshot_body		m_CxlReqBody;
};

//回滚ETF成交(4004-176)
struct tmsh_rewind_etf_exec
{
	tmsh_rewind_etf_exec()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = tmsh_types::TMSH_REWIND_ETF_EXEC;
		m_Header.m_MsgLen = sizeof(*this);
		assert(m_Header.m_MsgLen == sizeof(msg_standard_hdr) + sizeof(etf_exec_snapshot_body));
	}
	msg_standard_hdr			m_Header;
	etf_exec_snapshot_body		m_ETFExecSnapshotBody;
};

//4被动成交请求(4005-160)
struct tmsh_passive_exec
{
	tmsh_passive_exec()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = tmsh_types::TMSH_PASSIVE_EXEC;
		m_Header.m_MsgLen = sizeof(*this);
		assert(m_Header.m_MsgLen == sizeof(msg_standard_hdr) + sizeof(exec_snapshot_body));
	}
	msg_standard_hdr			m_Header;
	exec_snapshot_body			m_ExecSnapshotBody;
};

//被动撤单成功(4006-248)
struct tmsh_passive_cxled
{
	tmsh_passive_cxled()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = tmsh_types::TMSH_PASSIVE_CXLED;
		m_Header.m_MsgLen = sizeof(*this);
		assert(m_Header.m_MsgLen == sizeof(msg_standard_hdr) + sizeof(cxl_req_snapshot_body));
	}
	msg_standard_hdr			m_Header;
	cxl_req_snapshot_body		m_CxlReqBody;
};

//被动订单(4007-384)
struct tmsh_passive_order
{
	tmsh_passive_order()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = tmsh_types::TMSH_PASSIVE_ORDER;
		m_Header.m_MsgLen = sizeof(*this);
		assert(m_Header.m_MsgLen == sizeof(msg_standard_hdr) + sizeof(order_snapshot_body)  + 8);
	}
	msg_standard_hdr			m_Header;
	order_snapshot_body			m_OrderSnapshotBody;
	uInt8						m_Reserved[8];
};


//被动交易所接受(4008-32)
struct tmsh_passive_exch_accpet
{
	tmsh_passive_exch_accpet()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = tmsh_types::TMSH_PASSIVE_EXCH_ACCEPT;
		m_Header.m_MsgLen = sizeof(*this);
		m_PassiveFlag = rem_passive_order_flag::POF_PASSIVE;
		assert(m_Header.m_MsgLen == sizeof(msg_standard_hdr) + 24);
	}
	msg_standard_hdr			m_Header;
	uInt64						m_OrderID;
	T_TIMESTAMP					m_Timestamp;
	uInt32						m_PassiveOptr;
	T_PASSIVE_ORDER_FLAG		m_PassiveFlag;
	uInt8						m_Reserved[3];
};

//被动撤单拒绝(4009)
struct tmsh_passive_cxl_reject
{
	tmsh_passive_cxl_reject()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = tmsh_types::TMSH_PASSIVE_CXL_REJECT;
		m_Header.m_MsgLen = sizeof(*this);
		m_CxlReqBody.m_ClientCxledBody.m_PassiveFlag = rem_passive_order_flag::POF_PASSIVE;
		m_CxlReqBody.m_CxlReqStatus = rem_cxl_req_status::CXL_REQ_REJECTED;
		assert(m_Header.m_MsgLen == sizeof(msg_standard_hdr) + sizeof(cxl_req_snapshot_body));
	}
	msg_standard_hdr			m_Header;
	cxl_req_snapshot_body		m_CxlReqBody;
};

struct tmsh_set_order_link_market_reff_id
{
	tmsh_set_order_link_market_reff_id()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = tmsh_types::TMSH_PASSIVE_MARKET_REFF_ID;
		m_Header.m_MsgLen = sizeof(*this);
	}
	msg_standard_hdr			m_Header; 
	char						m_orderFlag ; // 1: new order  2: cxl order
	uInt64						m_OrderID;
	i32_sl						m_ReqNum ;
	T_EXCHANGE_ORDER_REFF		m_OrderReff ;

};
//#END，交易类内部，软件发给硬件


#pragma pack(pop)
