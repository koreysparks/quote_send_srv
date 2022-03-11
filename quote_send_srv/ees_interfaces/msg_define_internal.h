#pragma once

#include "msg_define_client.h"

#pragma pack(push, 1)
///#START，交易类内部，硬件发给软件
///前缀tmhs: Trade Message, Hardware to Software

//订单snapshot(5000-384)
struct tmhs_order_snapshot
{
	tmhs_order_snapshot()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = tmhs_types::TMHS_ORDER_SNAPSHOT;
		m_Header.m_MsgLen = sizeof(*this);		
		assert(m_Header.m_MsgLen == sizeof(msg_standard_hdr) + sizeof(order_snapshot_body));
	}
	msg_standard_hdr			m_Header;
	order_snapshot_body			m_OrderSnapshotBody;
};



struct tmhs_order_sh_cs_rec_num_snapshot
{
	tmhs_order_sh_cs_rec_num_snapshot()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = tmhs_types::TMHS_ORDER_SH_CS_REC_NUM_SNAPSHOT;
		m_Header.m_MsgLen = sizeof(*this);

	}
	msg_standard_hdr m_Header;
	T_CUST_ID				m_cust_id;
	T_FUND_ACCOUNT			m_FundAccount;
	uInt64					m_OrderID; ///<	8	uInt64	REM系统单cluster唯一编号。 Id37
	uInt32					m_Reqnum; ///<	4	uInt32	送单子的数据库编号
};


/// 期权组合拆分扩展字段
struct extern_comb_order_snapshot : extern_comb_order
{

};

/// 期权组合行权扩展字段
struct extern_comb_execrise_snapshot : extern_comb_exercise
{


};


//交易所订单接受(5010-384)
struct tmhs_exch_order_accept
{
	tmhs_exch_order_accept()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = tmhs_types::TMHS_ORDER_EXCH_ACCEPT;
		m_Header.m_MsgLen = sizeof(*this);		
		assert(m_Header.m_MsgLen == sizeof(msg_standard_hdr) + sizeof(order_snapshot_body));
	}
	msg_standard_hdr			m_Header;
	order_snapshot_body			m_OrderSnapshotBody;
};

//交易所订单拒绝(5011-384)
struct tmhs_exch_order_reject
{
	tmhs_exch_order_reject()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = tmhs_types::TMHS_ORDER_EXCH_REJECT;
		m_Header.m_MsgLen = sizeof(*this);		
		assert(m_Header.m_MsgLen == sizeof(msg_standard_hdr) + sizeof(order_snapshot_body));
	}
	msg_standard_hdr			m_Header;
	order_snapshot_body			m_OrderSnapshotBody;
};

//被动单/外部单接受(5012-384)
struct tmhs_passive_external_order_accept
{
	tmhs_passive_external_order_accept()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = tmhs_types::TMHS_PASSIVE_EXT_ORDER;
		m_Header.m_MsgLen = sizeof(*this);		
		assert(m_Header.m_MsgLen == sizeof(msg_standard_hdr) + sizeof(order_snapshot_body));
	}
	msg_standard_hdr			m_Header;
	order_snapshot_body			m_OrderSnapshotBody;
};

//撤单请求snapshot(5001-248)
struct tmhs_cxl_req_snapshot
{
	tmhs_cxl_req_snapshot()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = tmhs_types::TMHS_CXL_REQ_SNAPSHOT;
		m_Header.m_MsgLen = sizeof(*this);		
		assert(m_Header.m_MsgLen == sizeof(msg_standard_hdr) + sizeof(cxl_req_snapshot_body));
		m_CxlReqBody.m_CxlReqStatus = rem_cxl_req_status::CXL_REQ_PENDING;
	}
	msg_standard_hdr			m_Header;
	cxl_req_snapshot_body		m_CxlReqBody;
};

//撤单成功(5021-248)
struct tmhs_order_cxled
{
	tmhs_order_cxled()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = tmhs_types::TMHS_ORDER_CXLED;
		m_Header.m_MsgLen = sizeof(*this);		
		assert(m_Header.m_MsgLen == sizeof(msg_standard_hdr) + sizeof(cxl_req_snapshot_body));
	}
	msg_standard_hdr			m_Header;
	cxl_req_snapshot_body		m_CxlReqBody;
};

//撤单交易所拒绝(5022-248)
struct tmhs_exch_cxl_reject
{
	tmhs_exch_cxl_reject()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = tmhs_types::TMHS_EXCH_CXL_REJECT;
		m_Header.m_MsgLen = sizeof(*this);		
		assert(m_Header.m_MsgLen == sizeof(msg_standard_hdr) + sizeof(cxl_req_snapshot_body));
	}
	msg_standard_hdr			m_Header;
	cxl_req_snapshot_body		m_CxlReqBody;
};

//成交回报snapshot(5002-160)
struct tmhs_exec_snapshot
{
	tmhs_exec_snapshot()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = tmhs_types::TMHS_EXEC_SNAPSHOT;
		m_Header.m_MsgLen = sizeof(*this);		
		assert(m_Header.m_MsgLen == sizeof(msg_standard_hdr) + sizeof(exec_snapshot_body));
	}
	msg_standard_hdr			m_Header;
	exec_snapshot_body			m_ExecSnapshotBody;
};

struct extern_comb_exec_snapshot : extern_comb_order
{

};


struct extern_comb_exercise_snapshot :extern_comb_exercise
{

};


//ETF成交回报snapshot(5003-176+x)
struct tmhs_etf_exec_snapshot
{
	tmhs_etf_exec_snapshot()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = tmhs_types::TMHS_ETF_EXEC_SNAPSHOT;
		m_Header.m_MsgLen = sizeof(*this);		
		assert(m_Header.m_MsgLen == sizeof(msg_standard_hdr) + sizeof(etf_exec_snapshot_body));
	}
	msg_standard_hdr			m_Header;
	etf_exec_snapshot_body		m_ExecSnapshotBody;
};

//订单被REM拒绝抄送消息(5004-240)
struct tmhs_order_rejected_drop_copy
{
	tmhs_order_rejected_drop_copy()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = tmhs_types::TMHS_ORDER_REJECT_DROPCOPY;
		m_Header.m_MsgLen = sizeof(*this);		
		assert(m_Header.m_MsgLen == sizeof(msg_standard_hdr) + sizeof(client_order_req_body) + sizeof(client_order_reject_body));
	}
	msg_standard_hdr			m_Header;
	client_order_req_body		m_ClientOrderRequestBody;
	client_order_reject_body	m_ClientOrderRejectBody;
};

/// 组合策略内部拒绝扩展消息
struct extern_comb_order_reject : extern_comb_order
{
};

/// 组合行情拒绝扩展消息
struct extern_comb_exercise_reject : extern_comb_exercise
{

};


//撤单请求被OT拒绝抄送消息(5005-208)
struct tmhs_cxl_reject_drop_copy
{
	tmhs_cxl_reject_drop_copy()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = tmhs_types::TMHS_CXL_REJECT_DROPCOPY;
		m_Header.m_MsgLen = sizeof(*this);		
		assert(m_Header.m_MsgLen == sizeof(msg_standard_hdr) + sizeof(client_cxl_req_body) + sizeof(client_cxl_reject_body));
	}
	msg_standard_hdr			m_Header;
	client_cxl_req_body			m_ClientCxlRequestBody;
	client_cxl_reject_body		m_ClientCxlRejectBody;
};


//撤单请求硬件专用(5601-640)
struct tmhs_cxl_req_snapshot_hwmkt
{
	tmhs_cxl_req_snapshot_hwmkt()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = tmhs_types::TMHS_CXL_REQ_SNAPSHOT_HWMKT;
		m_Header.m_MsgLen = sizeof(*this);		
		assert(m_Header.m_MsgLen == sizeof(msg_standard_hdr) + sizeof(order_snapshot_body) + sizeof(cxl_req_snapshot_body));
	}
	msg_standard_hdr			m_Header;
	order_snapshot_body			m_OrderSnapshotBody;
	cxl_req_snapshot_body		m_CxlReqBody;
};

//#END，交易类内部，硬件发给软件

//#END，交易类，内部通道



#pragma pack(pop)

