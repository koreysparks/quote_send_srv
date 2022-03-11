#pragma once

#pragma pack(push, 1)

///#START，股票版消息结构体定义

//#START，多个消息需要使用的公用结构

//客户端请求消息体(104)
struct client_order_req_body
{
	client_order_req_body()
	{
		assert(sizeof(*this) == 104);
	}
	uInt32					m_UserID;
	uInt32					m_ClOrdToken;
	T_CUST_ID				m_cust_id;
	T_SECU_FULL_TYPE		m_SecurityFullType;
	Int8					m_Reserved1[5];
	T_FUND_ACCOUNT			m_FundAccount;
	uInt8					m_ForceCoverFlag ; // 只要不为0，就是强平的原因。
	T_EXCHANGE				m_ExchID;
	T_SIDE					m_Side;
	uInt32					m_OrderQty;
	uInt32					m_MinQty;
	T_PRICE_TYPE			m_PriceType;
	uInt16					m_MaxPriceLevels;
	T_TIF					m_TIF;
	T_PRICE_4				m_Price;
	T_PRICE_4				m_StopPrice;
	T_SECURITY_CODE			m_SecurityCode;
	T_CASHMARGIN_FLAG		m_CashMarginFlag;
	uInt8					m_SessionID;
	T_SESSION_SEL_MODE		m_SessionSelMode;
	uInt32					m_PassiveOrderClientID;
	Int8					m_UserInfo[8];
};

struct comb_leg
{
	T_SECURITY_CODE	m_LegSecurityID;		///<	成份合约代码（期权code）
	uInt8			m_LegPosDir;			///<	持仓方向
	uInt32			m_LegOrderQty;			////<	成份合约数量
	uInt8			m_Reserver2;			///<	保留
	uInt8			m_Exchange;				///<	交易所
};

/// 期权组合，折分持仓订单扩展请求
struct extern_comb_order
{
	T_ExchCombSeqID		m_SecondaryOrderID; ///<	组合策略流水号， 16位有效	构建组合申报时填全 0 ，解除组合申报时填写拟解除组合对应的组合流水号（构建组合申报时返回的执行报告中的OrderID）
	T_SECURITY_CODE		m_StrategyID;		///<	组合策略编码
	uInt8				m_Nolegs;				///<	成分合约个数（最多支持4，目前市场最多是2）
	uInt8				m_Reserve1[5];			///< 	保留
	comb_leg			m_legs[2];				///<	多腿 
};

/// 期权组合行权扩展字段
struct extern_comb_exercise
{
	uInt8		m_Nolegs;				///< 	成分合约个数（最多支持4，目前市场最多是2）
	uInt8		m_Reserve[7];				///<	保留
	comb_leg	m_legs[2];
};

//#TODO: 融资融券相关的两个请求

//客户端撤单请求消息体(72)
struct client_cxl_req_body
{
	client_cxl_req_body()
	{
		assert(sizeof(*this) == 72);
	}
	uInt32					m_UserID;
	uInt32					m_ClOrdToken;
	T_CUST_ID				m_ClientID;
	Int8					m_Reserved1[7];
	T_FUND_ACCOUNT			m_FundAccount;
	Int8					m_Reserved2[7];
	uInt64					m_OrigOrderID;
	uInt32					m_OrigClOrdToken;
	uInt32					m_LeavesQty;
};

//客户端接受消息结构体(长度232)
struct client_accept_order_body
{
	client_accept_order_body()
	{
		assert(sizeof(*this) == 232);
	}
	client_order_req_body		m_ClReqBody;	
	uInt64						m_OrderID;
	T_EXCHANGE_ORDER_ID			m_ExchangeOrderID;
	T_EXCHANGE_ACCPET_FALG		m_ExchangeAcceptFlag;
	uInt8						m_OrderState;
	T_PASSIVE_ORDER_FLAG		m_PassiveOrderFlag;
	uInt8						m_Reserved1;
	T_TIMESTAMP					m_RecvTimestamp;
	T_TIMESTAMP					m_AcceptTimestamp;
	T_TIMESTAMP					m_ExchangeAcceptTimestamp;
	T_TIMESTAMP					m_ExchangeTransTimestamp;
	T_TIMESTAMP					m_ClosedTimestamp;
	uInt32						m_FilledQty;
	uInt16						m_ExpireDateYear;
	uInt8						m_ExpireDateMonth;
	uInt8						m_ExpireDateDay;
	T_SECURITY_CODE				m_UnderlyingSecurityCode;
	T_CONTRACT_ACCOUNT_CODE		m_ContractAccountCode;
	T_OPT_CONTRACT_ID			m_ContractID;
	T_EXCHANGE					m_UnderlyingExchID;
	T_OPT_CALL_PUT				m_CallOrPut;
	uInt8						m_Reserved2;
	T_PRICE_4					m_StrikePrice;
	
};

/// 普通订单 扩展字段 
struct extern_order_accept
{
	T_PRICE_4		m_AvailBp;		///<	可用资金
	uInt32			m_OvnPosQty;	///< 	仓位数量
	uInt8			m_Reserve3[4];	///<	保留
};

/// 组合持仓1010 扩展字段 
struct extern_comb_order_accept : extern_comb_order
{
};

struct extern_comb_exchange_accept : extern_comb_order
{
};

struct extern_comb_exchange_reject : extern_comb_order
{
};

struct extern_comb_exec : extern_comb_order
{
};

/// 组合行权扩展字段 
struct extern_comb_order_exercise : extern_comb_exercise
{
};

//客户端订单拒绝(128)
struct client_order_reject_body
{
	client_order_reject_body()
	{
		assert(sizeof(*this) == 136);
	}
	uInt32						m_UserID;
	uInt32						m_ClOrdToken;
	uInt64						m_OrderID;
	T_TIMESTAMP					m_RejectTimestamp;
	T_REJECTED_BY				m_RejectedBy;
	uInt16						m_RejectReason;
	uInt32						m_GrammarResult;
	T_PASSIVE_ORDER_FLAG		m_PassiveFlag;
	uInt8						m_RiskResult[16];///考虑封装一个type
	T_REASON_TEXT				m_ReasonText;	
};

struct extern_order_reject
{
	T_PRICE_4		m_AvailBp;		///<	可用资金
	uInt32			m_OvnPosQty;	///< 	仓位数量
	uInt8			m_Reserve3[4];	///<	保留
};

struct extern_comb_order_rej
{
	char		m_SecondaryOrderID[17];		///< 组合策略流水号， 16位有效	构建组合申报时填全0，解除组合申报时填写拟解除组合对应的组合流水号（构建组合申报时返回的执行报告中的OrderID）
	char		m_StrategyID[9];			///< 组合策略编码
	char		m_Reserve[6];				///< 保留
};

//客户端成交(144)
struct client_exec_body
{
	client_exec_body()
	{
		assert(sizeof(*this) == 144);
	}
	uInt32						m_UserID;
	uInt32						m_ClOrdToken;
	T_CUST_ID					m_ClientID;
	uInt8						m_Reserved1[7];
	T_FUND_ACCOUNT				m_FundAccount;
	uInt8						m_Reserved2[7];
	uInt64						m_OrderID;
	uInt64						m_ExecID;
	T_PRICE_4					m_LastPrice;
	uInt32						m_LastQty;
	T_PASSIVE_ORDER_FLAG		m_PassiveFlag;
	T_EXCHANGE					m_ExchID;
	uInt8						m_Reserved3[2];
	T_EXCHANGE_ORDER_ID			m_ExchangeOrderID;
	T_EXCHANGE_EXEC_ID			m_ExchangeExecID;
	T_TIMESTAMP					m_ExchangeTimestamp;
	T_TIMESTAMP					m_ExecTimestamp;
};

// 普通成交的扩展字段
struct extern_exec_body
{
	T_PRICE_4		m_AvailBp;		///<	可用资金
	uInt32			m_OvnPosQty;	///< 	仓位数量
	uInt8			m_Reserve3[4];	///<	保留
};

/// 组合 持仓成交扩展字段 
struct extern_comb_exec_body : extern_comb_order
{

};

/// 组合行权成交扩展字段
struct extern_exercise_exec :extern_comb_exercise
{

}; 

//客户端撤单拒绝(144)
struct client_cxl_reject_body
{
	client_cxl_reject_body()
	{
		assert(sizeof(*this) == 144);
	}
	uInt32						m_UserID;
	uInt32						m_ClOrdToken;
	uInt64						m_OrderID;
	T_TIMESTAMP					m_RejectTimestamp;
	T_TIMESTAMP					m_ExchangeTrasnTimestamp;
	T_REJECTED_BY				m_RejectedBy;
	uInt16						m_RejectReason;
	T_PASSIVE_ORDER_FLAG		m_PassiveFlag;
	uInt32						m_GrammarResult;
	uInt8						m_RiskResult[16];///考虑封装一个type	
	T_REASON_TEXT				m_ReasonText;
	
};


///etf成交
struct client_etf_exec_body
{
	client_etf_exec_body()
	{
		assert(sizeof(*this) == 176);
	}
	client_exec_body			m_ExecBody;
	T_LAST_RECORD_FLAG			m_LastRecordFlag;
	uInt8						m_Reserved[3];
	uInt32						m_TotalGroup;
	T_SECURITY_CODE				m_MemberSecurityCode;
	T_EXCHANGE					m_MemberExchID;
	uInt32						m_DeliveryQty;
	uInt8						m_Reserved2[2];
	T_PRICE_4					m_SubstCash;
};

///客户端撤单成功消息体(128)
struct client_cxled_body
{
	client_cxled_body()
	{
		assert(sizeof(*this) == sizeof(client_cxl_req_body) + 56);
	}
	client_cxl_req_body			m_ClientReqBody;
	T_TIMESTAMP					m_AcceptTimestamp;
	T_TIMESTAMP					m_CxledTimestamp;
	T_TIMESTAMP					m_ExchangeTransTimestamp;
	T_EXCHANGE_ORDER_ID			m_ExchangeOrderID;
	uInt32						m_OrigUserID;
	uInt32						m_LeavesQty;
	T_EXCHANGE					m_ExchID;
	T_PASSIVE_ORDER_FLAG		m_PassiveFlag;
	T_CXL_REQ_STATUS			m_CxlReqStatus;
	uInt8						m_Reserved;
};

///订单完整信息(长度376)
struct order_snapshot_body
{
	order_snapshot_body()
	{
		assert(sizeof(*this) == sizeof(client_accept_order_body)+ 160);
	}
	
	extern_comb_order_exercise* get_extern_comb_exercise_ptr()
	{
		return (extern_comb_order_exercise*)(((unsigned char*)(this)) + sizeof(*this)) ;
	}

	extern_comb_order_accept* get_extern_order_accept_ptr()
	{
		return (extern_comb_order_accept*)(((unsigned char*)(this)) + sizeof(*this)) ;
	}

	extern_comb_exchange_accept* get_extern_exchange_accept_ptr()
	{
		return (extern_comb_exchange_accept*)(((unsigned char*)(this)) + sizeof(*this));
	}

	extern_comb_exchange_reject* get_extern_exchange_reject_ptr()
	{
		return (extern_comb_exchange_reject*)(((unsigned char*)(this)) + sizeof(*this));
	}

	extern_comb_exec* get_extern_exec_ptr()
	{
		return (extern_comb_exec*)(((unsigned char*)(this)) + sizeof(*this));
	}

	extern_comb_order*		get_comb_pos_ptr()
	{
		return (extern_comb_order*)(((unsigned char*)(this)) + sizeof(*this));
	}

	bool is_mutli_leg()  
	{		
		if (m_ClientAccpetBody.m_ClReqBody.m_Side == rem_side::SIDE_OPT_COMB_EXERCISE) //= 43, ///<期权合并申报行权
			return true;
		if (m_ClientAccpetBody.m_ClReqBody.m_Side == rem_side::SIDE_OPT_COMB_POS_CREATE) //= 44, ///<期权构建组合策略
			return true;
		if (m_ClientAccpetBody.m_ClReqBody.m_Side == rem_side::SIDE_OPT_COMB_POS_RELIEVE) //= 45, ///<期权解除组合策略
			return true;
		if (m_ClientAccpetBody.m_ClReqBody.m_Side == rem_side::SIDE_OPT_COVERED_TO_NORMAL) //= 46, ///<期权备兑转普通		
			return true;
		return false;
	}


	client_accept_order_body	m_ClientAccpetBody;
	T_EXCHANGE_ORDER_TOKEN		m_ExchangeOrderToken;
	T_TIMESTAMP					m_ExchTrasactionTimestamp;
	T_TIMESTAMP					m_MarketTransTimestamp;
	T_EXCHANGE_ACCOUNT			m_ExchangeAccount;
	uInt16						m_RejectReason;
	uInt32						m_PassiveOptr;
	uInt8						m_Reserved[2];
	T_REASON_TEXT				m_ReasonText;
	T_BRANCH_ID					m_ExchangeBranchID;
	uInt8						m_OwerType;
	uInt32						m_RewindRecNum ;
	uInt8						m_Reserved2[2];
};

///撤单请求完整消息(256)
struct cxl_req_snapshot_body
{
	cxl_req_snapshot_body()
	{
		assert(sizeof(*this) == sizeof(client_cxled_body) + 120);
		m_CxlReqStatus = rem_cxl_req_status::CXL_REQ_PENDING;
	}	
	client_cxled_body			m_ClientCxledBody;
	T_EXCHANGE_ORDER_TOKEN		m_ExchangeOrderToken;
	uInt32						m_PassiveOptr;
	uInt16						m_RejectReason;
	T_CXL_REQ_STATUS			m_CxlReqStatus;
	uInt8						m_RwdCxlIdx;
	T_REASON_TEXT				m_ReasonText;
	uInt8						m_RejectedBy;
	uInt8						m_OwerType;
	uInt8						m_Reserved2[6];
};

///成交完整信息(152)
struct exec_snapshot_body
{
	exec_snapshot_body()
	{
		assert(sizeof(*this) == sizeof(client_exec_body) + 8);
	}
	client_exec_body	m_ClientExecReportBody;
	uInt32				m_PassiveOptr;
	uInt8				m_Reserved[4];
};

///ETF成交完整消息，不包含可重复部分(168)
struct etf_exec_snapshot_body
{
	etf_exec_snapshot_body()
	{
		assert(sizeof(*this) == sizeof(client_etf_exec_body) + 8);
	}
	uInt32						m_PassiveOptr;
	uInt8						m_Reserved[4];
	client_etf_exec_body		m_ClientEtfExecHdrBody;
};



///单个证券代码仓位信息，完整结构体，可用于表示股票/ETF/仓位
struct full_position_info
{
	full_position_info()
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
	double				m_OptExchangeMargin;				//option_position_one_side_info::get_exchange_margin	(可以获取)   ///< 交易所占用保证金;
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


#pragma pack(pop)
