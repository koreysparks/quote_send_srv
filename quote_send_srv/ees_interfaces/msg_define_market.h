#pragma once


#pragma pack(push, 1)
///#START，交易类，市场通道
///#START，交易类市场，硬件发给Market
///前缀tmhm: Trade Message, Hardware to Market

//订单请求(6000-384)
struct tmhm_new_order_req
{
	tmhm_new_order_req()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = tmhm_types::TMHM_NEW_ORDER_REQUEST;
		m_Header.m_MsgLen = sizeof(*this);		
		assert(m_Header.m_MsgLen == sizeof(msg_standard_hdr) + sizeof(order_snapshot_body));
	}
	msg_standard_hdr			m_Header;
	order_snapshot_body			m_OrderSnapshotBody;
};

//撤单请求(6001-640)
struct tmhm_cxl_req
{
	tmhm_cxl_req()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = tmhm_types::TMHM_CXL_REQ;
		m_Header.m_MsgLen = sizeof(*this);		
		assert(m_Header.m_MsgLen == sizeof(msg_standard_hdr) + sizeof(order_snapshot_body) + sizeof(cxl_req_snapshot_body));
	}
	msg_standard_hdr			m_Header;
	order_snapshot_body			m_OrderSnapshotBody;
	cxl_req_snapshot_body		m_CxlReqBody;
};

//#END，交易类市场，硬件发给Market

///#START，交易类市场，Market发给硬件
///前缀tmmh: Trade Message, Market to Hardware

//回报接受(7000-384)
struct tmmh_order_accept
{
	tmmh_order_accept()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = tmmh_types::TMMH_ORDER_ACCEPT;
		m_Header.m_MsgLen = sizeof(*this);		
		assert(m_Header.m_MsgLen == sizeof(msg_standard_hdr) + sizeof(order_snapshot_body));
	}
	msg_standard_hdr			m_Header;
	order_snapshot_body			m_OrderSnapshotBody;
};

//订单拒绝(7001-384)
struct tmmh_order_reject
{
	tmmh_order_reject()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = tmmh_types::TMMH_ORDER_REJECT;
		m_Header.m_MsgLen = sizeof(*this);		
		assert(m_Header.m_MsgLen == sizeof(msg_standard_hdr) + sizeof(order_snapshot_body));
	}
	msg_standard_hdr			m_Header;
	order_snapshot_body			m_OrderSnapshotBody;
};

//成交回报(7002-160)
struct tmmh_order_execution
{
	tmmh_order_execution()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = tmmh_types::TMMH_ORDER_EXECUTION;
		m_Header.m_MsgLen = sizeof(*this);		
		assert(m_Header.m_MsgLen == sizeof(msg_standard_hdr) + sizeof(exec_snapshot_body));
	}
	msg_standard_hdr			m_Header;
	exec_snapshot_body			m_ExecSnapshotBody;
};

//ETF申购赎回成交回报(7003-176+x)
struct tmmh_etf_execution
{
	tmmh_etf_execution()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = tmmh_types::TMMH_ETF_EXECUTION;
		m_Header.m_MsgLen = sizeof(*this);		
		assert(m_Header.m_MsgLen == sizeof(msg_standard_hdr) + sizeof(etf_exec_snapshot_body));
	}
	msg_standard_hdr			m_Header;
	etf_exec_snapshot_body		m_ExecSnapshotBody;
};

//撤单成功(7004-248)
struct tmmh_order_cxled
{
	tmmh_order_cxled()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = tmmh_types::TMMH_ORDER_CXLED;
		m_Header.m_MsgLen = sizeof(*this);		
		assert(m_Header.m_MsgLen == sizeof(msg_standard_hdr) + sizeof(cxl_req_snapshot_body));
	}
	msg_standard_hdr			m_Header;
	cxl_req_snapshot_body		m_CxlReqBody;
};

//撤单拒绝(7005-248)
struct tmmh_cxl_reject
{
	tmmh_cxl_reject()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = tmmh_types::TMMH_CXL_REJECT;
		m_Header.m_MsgLen = sizeof(*this);		
		m_CxlReqBody.m_CxlReqStatus = rem_cxl_req_status::CXL_REQ_PENDING;
		assert(m_Header.m_MsgLen == sizeof(msg_standard_hdr) + sizeof(cxl_req_snapshot_body));
	}	
	msg_standard_hdr			m_Header;
	cxl_req_snapshot_body		m_CxlReqBody;
};

//市场session连接情况反馈(7006-16)
struct tmmh_session_status_report
{
	tmmh_session_status_report()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = tmmh_types::TMMH_SESSION_STATUS_REPORT;
		m_Header.m_MsgLen = sizeof(*this);		
		assert(m_Header.m_MsgLen == 16);
	}
	msg_standard_hdr			m_Header;
	uInt8						m_MarketSessionID;
	T_EXCHANGE					m_ExchID;
	T_SESSION_STATUS			m_SessionStatus;
	uInt8						m_Reserved[5];
};

//#END，交易类市场，Market发给硬件

//#END，交易类，市场通道


#pragma pack(pop)
