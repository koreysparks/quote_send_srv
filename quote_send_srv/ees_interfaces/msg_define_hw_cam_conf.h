#pragma once


#pragma pack(push, 1)
//#START，硬件配置协议

//大多数消息用到的公用头

struct hwcm_common_hdr
{	
	msg_standard_hdr m_StdHdr;
	T_BATCH_FLAG	 m_BatchFlag;
	uInt8			 m_CycleMode ;
	uInt8			 m_Reserved[6];
	uInt32			 m_TotalGroup;//整个批次的整体数据体个数
	uInt32			 m_NumGroup;//本次消息数据体的个数
};

//非期权证券代码配置信息，8000
struct hwcm_stock_security_code_config_hdr
{
	hwcm_stock_security_code_config_hdr()
	{
		memset(this, 0, sizeof(*this));
		m_CommonHdr.m_StdHdr.m_MsgType = hwcm_types::HWCM_NO_OPT_SECURITY_CODE_CONFIG;
		m_CommonHdr.m_StdHdr.m_MsgLen = sizeof(*this);		
	}
	hwcm_common_hdr	m_CommonHdr;
};
struct hwcm_stock_security_code_config_body
{
	hwcm_stock_security_code_config_body()
	{
		memset(this, 0, sizeof(*this));
		assert(sizeof(*this) == 32);
	}
	T_SECURITY_CODE			m_SecurityCode;
	T_EXCHANGE				m_ExchID;
	T_SECU_FULL_TYPE		m_SecurityFullType;	
	T_SECU_ADDITIONAL_FLAG	m_AddiFlag;
	T_COVER_TODAY_FLAG		m_CoverTodayFlag;
	uInt8					m_IsOptUnderlying;
	uInt8					m_Reserved1;
	T_SECURITY_CODE			m_UnderlyingSecurityCode;
	uInt16 					m_SecurityStatus;
	uInt8					m_Reserved2[5];
};

//期权symbol配置，8001
struct hwcm_opt_security_code_config_hdr
{
	hwcm_opt_security_code_config_hdr()
	{
		memset(this, 0, sizeof(*this));
		m_CommonHdr.m_StdHdr.m_MsgType = hwcm_types::HWCM_OPT_SECURITY_CODE_CONFIG;
		m_CommonHdr.m_StdHdr.m_MsgLen = sizeof(*this);		
	}
	hwcm_common_hdr	m_CommonHdr;
};
struct hwcm_opt_security_code_config_body
{
	hwcm_opt_security_code_config_body()
	{
		memset(this, 0, sizeof(*this));
		assert(sizeof(*this) == 64);
	}
	T_SECURITY_CODE		m_SecurityCode;
	T_EXCHANGE			m_ExchID;
	uInt16				m_ExpireDateYear;
	uInt8				m_ExpireDateMonth;
	uInt8				m_ExpireDateDay;
	T_OPT_CONTRACT_ID	m_ContractID;
	T_OPT_CALL_PUT		m_CallOrPut;
	T_EXCHANGE			m_UnderlyingExchID;
	uInt8				m_Reserved1[3];
	T_PRICE_4			m_StrikePrice;
	T_SECURITY_CODE		m_UnderlyingSecurityCode;
	uInt32				m_VolumeMultipler;
	uInt8				m_Reserved2[3];
};

//客户号、资金帐户、交易所账户配置，8002，需要先配8014
struct hwcm_account_structure_config_hdr
{
	hwcm_account_structure_config_hdr()
	{
		memset(this, 0, sizeof(*this));
		m_CommonHdr.m_StdHdr.m_MsgType = hwcm_types::HWCM_ACCOUNT_STRUCTURE_CONFIG;
		m_CommonHdr.m_StdHdr.m_MsgLen = sizeof(*this);		
	}
	hwcm_common_hdr	m_CommonHdr;
};
struct hwcm_account_structure_config_body
{
	hwcm_account_structure_config_body()
	{
		memset(this, 0, sizeof(*this));
		assert(sizeof(*this) == 88);
	}
	T_CUST_ID	m_ClientID;
	T_FUND_ACCOUNT_TYPE	m_FundAccountType;
	T_ACCOUNT_PREVILEGE	m_Previlege;
	T_EXCHANGE			m_ExchID;
	uInt8				m_Reserved1[4];
	T_FUND_ACCOUNT		m_FundAccount;
	uInt8				m_Reserved2[7];
	T_EXCHANGE_ACCOUNT	m_ExchangeAccount;
	T_BRANCH_ID			m_BranchID;
	T_EX_BRANCH_ID		m_ExBranchID;
	uInt8				m_OwerType;
	uInt8				m_Reserved3[5];
};

//配置客户号和UserID的关系，8003
struct hwcm_client_user_id_link_config_hdr
{
	hwcm_client_user_id_link_config_hdr()
	{
		memset(this, 0, sizeof(*this));
		m_CommonHdr.m_StdHdr.m_MsgType = hwcm_types::HWCM_CLIENT_USER_ID_LINK_CONFIG;
		m_CommonHdr.m_StdHdr.m_MsgLen = sizeof(*this);		
	}
	hwcm_common_hdr	m_CommonHdr;
};
struct hwcm_client_user_id_link_config_body
{
	hwcm_client_user_id_link_config_body()
	{
		memset(this, 0, sizeof(*this));
		assert(sizeof(*this) == 24);
		userid_super_flag = 0 ;
	}
	T_CUST_ID	m_ClientID;	
	uInt8				userid_super_flag  ;
	uInt8				m_Reserved1[2];
	u32_sl				m_UserID;	
};

//配置ExchangeSessionID和ExchangeID的关系，8004
struct hwcm_exchange_session_link
{
	hwcm_exchange_session_link()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = hwcm_types::HWCM_EXCHANGE_SESSION_LINK;
		m_Header.m_MsgLen = sizeof(*this);		
	}

	msg_standard_hdr	m_Header;
	T_EXCHANGE			m_ExchID;
	uInt8				m_SessionCount;
	uInt8				m_Flag;
	uInt8				m_Reserved1[5];
	uInt8				m_SessionIDList[255];
	uInt8				m_Reserved2;

};

//硬核版本
//报告库订单区间，8004
struct hwcm_exchange_order_id_range_hdr
{
	hwcm_exchange_order_id_range_hdr()
	{
		memset(this, 0, sizeof(*this));
		m_CommonHdr.m_StdHdr.m_MsgType = hwcm_types::HWCM_EXCHANGE_ORDER_ID_RANGE_CONFIG;
		m_CommonHdr.m_StdHdr.m_MsgLen = sizeof(*this);		
	}
	hwcm_common_hdr	m_CommonHdr;
};
struct hwcm_exchange_order_id_range_body
{
	hwcm_exchange_order_id_range_body()
	{
		memset(this, 0, sizeof(*this));
		assert(sizeof(*this) == 64);
	}

	T_BRANCH_ID			BranchID ;			///< 9	C9	客户号所属营业部代码，8位有效，右边最后一位软件隔断符
	T_EX_BRANCH_ID		ExchangBranchID	;	///< 9	C9	对应交易所营业部编码，最多8位有效，左对齐，无效处 填数字0
	T_TRADE_PBU			PBU	;				///< 6	C6	交易单元。交易单元是与资金账号一一对应，5位有效，右边最后一位软件隔断符
	fix_str<7>			OrderID_Prev ;		///< 7	C7	订单前缀，最长6位，左对齐，不用的字段填数字0，最右边是软件隔断符。
	uInt8				ConfigID ;			///<  1	Int8	配置ID，仅仅为了硬件建立表
	fix_str<11>			StartOrderToken	 ;	///< 11	C11	起始订单单号分区
	fix_str<5>			Reserved1	;		///<  5	Bin5	保留
	fix_str<11>			EndOrderToken	;	///< 11	C11	结束订单单号分区
	uInt8				MsSqlID			;	///<  1	Int8	EzSTEP报盘数据库内部编码ID
	fix_str<4>			Reserved2		;	///<  4	Bin4	保留
};



//客户号PBU，交易平台配置 8005
struct hwcm_cust_pbu_platform_config_hdr
{
	hwcm_cust_pbu_platform_config_hdr()
	{
		memset(this, 0, sizeof(*this));
		m_CommonHdr.m_StdHdr.m_MsgType = hwcm_types::HWCM_CUST_PBU_PLATFORM_CONFIG;
		m_CommonHdr.m_StdHdr.m_MsgLen = sizeof(*this);		
	}
	hwcm_common_hdr	m_CommonHdr;
};
struct hwcm_cust_pbu_platform_config_body
{
	hwcm_cust_pbu_platform_config_body()
	{
		memset(this, 0, sizeof(*this));
		assert(sizeof(*this) == 32);
	}
	T_CUST_ID	m_ClientID;
	T_EXCHANGE	m_ExchID;
	T_plat_form				m_PlatFormId;
	uInt8				ConfigID;			///<  1	Int8	配置ID，仅仅为了硬件建立表
	T_TRADE_PBU			PBU;				///< 6	C6	交易单元。交易单元是与资金账号一一对应，5位有效，右边最后一位软件隔断符
	uInt8				m_Reserved2[6];
};




//SQL报盘库的属性配置 22000
struct hwmi_config_mssql_config_hdr
{
	hwmi_config_mssql_config_hdr()
	{
		memset(this, 0, sizeof(*this));
		m_CommonHdr.m_StdHdr.m_MsgType = hwmi_types::HWMI_CONFIG_TYPES_MSSQL_CONFIG;;
		m_CommonHdr.m_StdHdr.m_MsgLen = sizeof(*this);
	}
	hwcm_common_hdr	m_CommonHdr;
};
struct hwmi_config_mssql_config_body
{
	hwmi_config_mssql_config_body()
	{
		memset(this, 0, sizeof(*this));
		assert(sizeof(*this) == 104);
	}
	T_db_name m_DbName;
	T_db_name_len m_DbNameLen;
	T_db_name m_ReqTableName;
	T_db_name_len m_ReqTableNameLen;
	T_db_name m_ExeTableName;
	T_db_name_len m_ExeTableNameLen;
	T_db_user m_DbUser;
	T_db_user_len   m_DbUserLen;
	T_db_password m_DbPassword;
	T_db_password_len   m_DbPasswordLen;
	T_ip	m_DbIp;
	T_port	m_DbPort;
	T_EXCHANGE	m_ExchID;
	T_plat_form				m_PlatFormId;
	uInt8				m_ServerId;			///<  内部报盘库ID编码 目前支持8个
	uInt8				m_Reserved[5];
};


//上交所报盘软件的属性配置 22001
struct hwmi_config_sse_offer_config_hdr
{
	hwmi_config_sse_offer_config_hdr()
	{
		memset(this, 0, sizeof(*this));
		m_CommonHdr.m_StdHdr.m_MsgType = hwmi_types::HWMI_CONFIG_TYPES_SSE_OFFER_CONFIG;
		m_CommonHdr.m_StdHdr.m_MsgLen = sizeof(*this);
	}
	hwcm_common_hdr	m_CommonHdr;
};
struct hwmi_config_sse_offer_config_body
{
	hwmi_config_sse_offer_config_body()
	{
		memset(this, 0, sizeof(*this));
		assert(sizeof(*this) == 8);
	}
	uInt16  m_TgwId;
	uInt8  m_Envno;
	T_plat_form  m_PlatformId ;
	uInt8				m_Reserved[4];
};

//初始ReqNum配置报盘软件的属性配置 22002
struct hwmi_config_sse_reqnum_config_hdr
{
	hwmi_config_sse_reqnum_config_hdr()
	{
		memset(this, 0, sizeof(*this));
		m_CommonHdr.m_StdHdr.m_MsgType = hwmi_types::HWMI_CONFIG_TYPES_MSSQL_REQNUM_CONFIG;
		m_CommonHdr.m_StdHdr.m_MsgLen = sizeof(*this);
	}
	hwcm_common_hdr	m_CommonHdr;
};
struct hwmi_config_sse_reqnum_config_body
{
	hwmi_config_sse_reqnum_config_body()
	{
		memset(this, 0, sizeof(*this));
		assert(sizeof(*this) == 8);
	}
	uInt8				m_ServerId;			///<  内部报盘库ID编码 目前支持8个
	uInt32  m_StartReqnum; //MI发送的Reqnum
	uInt8				m_Reserved[3];
};


//深交所TGW件的属性配置 23000
struct hwmi_config_sze_tgw_config_hdr
{
	hwmi_config_sze_tgw_config_hdr()
	{
		memset(this, 0, sizeof(*this));
		m_CommonHdr.m_StdHdr.m_MsgType = hwmi_types::HWMI_CONFIG_TYPES_SZE_TGW_CONFIG;
		m_CommonHdr.m_StdHdr.m_MsgLen = sizeof(*this);
	}
	hwcm_common_hdr	m_CommonHdr;
};
struct hwmi_config_sze_tgw_config_body
{
	hwmi_config_sze_tgw_config_body()
	{
		memset(this, 0, sizeof(*this));
		assert(sizeof(*this) == 112);
	}
	T_EXCHANGE m_ExchId;
	uInt8    m_TgwId;
	uInt8				m_ServerId;			///<  内部报盘库ID编码 目前支持8个
	T_plat_form          m_PlatformId;
	uInt8				m_Reserved0[4];
	T_ip  m_TgwIp;
	T_port m_TgwPort;
	uInt8				m_Reserved1[2];
	fix_str<21>         m_SenderCompId;
	fix_str<21>         m_TargetCompId;
	fix_str<17>			m_Password;
	fix_str<33>         m_DefAppVerId;
	uInt8 m_BackupFlag;
	uInt8				m_Reserved2[3];
 };

//初始reportIndex配置 23002
struct hwmi_config_reportindex_config_hdr
{
	hwmi_config_reportindex_config_hdr()
	{
		memset(this, 0, sizeof(*this));
		m_CommonHdr.m_StdHdr.m_MsgType = hwmi_types::HWMI_CONFIG_TYPES_REPORTINDEX_CONFIG;
		m_CommonHdr.m_StdHdr.m_MsgLen = sizeof(*this);
	}
	hwcm_common_hdr	m_CommonHdr;
};
struct hwmi_config_reportindex_config_body
{
	hwmi_config_reportindex_config_body()
	{
		memset(this, 0, sizeof(*this));
		assert(sizeof(*this) == 24);
	}
	T_EXCHANGE		m_ExchId;
	uInt8			m_ServerId;			///<  内部报盘库ID编码 目前支持8个
	T_plat_form		m_PlatformId;
	uInt8			m_Reserved0[5];
	uInt32			m_NoPartitions;
	uInt32			m_PartitionNo;
	uInt64			m_ReportIndex;
 };

//心跳间隔配置 23003
struct hwmi_config_heartbeat_config
{
	hwmi_config_heartbeat_config()
	{
		memset(this, 0, sizeof(*this));
		m_StdHdr.m_MsgType = hwmi_types::HWMI_CONFIG_TYPES_HEARTBEAT_CONFIG;
		m_StdHdr.m_MsgLen = sizeof(*this);
	}
	msg_standard_hdr	m_StdHdr;
	uInt32 m_HeartBeat;
	uInt8				m_Reserved0[4];
};






// 实时调整证券的持仓。目前的调仓主要用于期权备兑
struct hwcm_adjust_underlying_pos_config_hdr
{
	hwcm_adjust_underlying_pos_config_hdr()
	{
		memset(this, 0, sizeof(*this));
		m_CommonHdr.m_StdHdr.m_MsgType = hwcm_types::HWCM_ADJUST_UNDERLYING_POS_SHARE;
		m_CommonHdr.m_StdHdr.m_MsgLen = sizeof(*this);		
	}
	hwcm_common_hdr	m_CommonHdr;
};


//结构体不再用于配置给硬件，但是软件多处还需要用到这个结构体，留下来
struct hwcm_adjust_underlying_pos_config_body
{
	hwcm_adjust_underlying_pos_config_body()
	{
		memset(this, 0, sizeof(*this));
		assert(sizeof(*this) == 72);
	}
	T_CUST_ID			m_ClientID;
	uInt8				m_Reserved[5];
	T_FUND_ACCOUNT_TYPE	m_FundAccountType;
	uInt8				m_ExchangeID ;
	T_FUND_ACCOUNT		m_FundAccountID ;
	uInt8				m_Reserved1[7];
	T_SECURITY_CODE		m_SecurityCode;
	uInt8				m_Reserved2[5];
	uInt8				m_SecuType;
	uInt8				m_SecuSubType;
	uInt8				m_InOrOut ;	
	uInt8				m_OvnOrToday ; 
	uInt32				m_PosDeltaQty ;
	uInt8				m_Reserved4[2];
};

//结构体不再用于配置给硬件，但是软件多处还需要用到这个结构体，留下来
struct hwcm_ovn_pos_config_body
{
	hwcm_ovn_pos_config_body()
	{
		memset(this, 0, sizeof(*this));
		assert(sizeof(*this) == 104);
	}
	T_CUST_ID	m_ClientID;
	T_FUND_ACCOUNT_TYPE	m_FundAccountType;
	uInt32				m_CoveredCallPledgedQty;//期权标的物，因备兑开仓而作为担保的数量
	uInt8				m_Reserved1[2];
	T_FUND_ACCOUNT		m_FundAccount;
	T_EXCHANGE			m_ExchID;
	T_POS_DIR			m_PosDir;
	uInt32				m_InitOvnPosQty;
	uInt8				m_Reserved2;
	T_EXCHANGE_ACCOUNT	m_ExchangeAccount;
	T_SECURITY_CODE		m_SecurityCode;
	T_SECU_FULL_TYPE	m_SecuFullType;
	uInt8				m_Reserved3;
	uInt32				m_RedeemdQty;
	T_PRICE_4			m_LastPrice;
	T_PRICE_4			m_Margin;
	uInt32				m_CoveredLockedQty;//期权标的物，该值指明了被备兑锁定指令锁定的量
	uInt8				m_Reserved4[4];
};

//收盘价、涨跌停配置， 8007
struct hwcm_price_config_hdr
{
	hwcm_price_config_hdr()
	{
		memset(this, 0, sizeof(*this));
		m_CommonHdr.m_StdHdr.m_MsgType = hwcm_types::HWCM_PRICE_CONFIG;
		m_CommonHdr.m_StdHdr.m_MsgLen = sizeof(*this);		
	}
	hwcm_common_hdr	m_CommonHdr;
};
struct hwcm_price_config_body
{
	hwcm_price_config_body()
	{
		memset(this, 0, sizeof(*this));
		assert(sizeof(*this) == 40);
	}
	T_SECURITY_CODE		m_SecurityCode;
	T_EXCHANGE			m_ExchID;
	T_SECU_FULL_TYPE	m_SecuFullType;
	uInt8				m_Reserved1[4];
	T_PRICE_4			m_LastClosePrice;
	T_PRICE_4			m_UpperLimitPrice;
	T_PRICE_4			m_LowerLimitPrice;
};

//费率配置信息，8008
struct hwcm_fee_config_hdr
{
	hwcm_fee_config_hdr()
	{
		memset(this, 0, sizeof(*this));
		m_CommonHdr.m_StdHdr.m_MsgType = hwcm_types::HWCM_FEE_CONFIG;
		m_CommonHdr.m_StdHdr.m_MsgLen = sizeof(*this);
	}
	hwcm_common_hdr	m_CommonHdr;
};
struct hwcm_fee_config_body
{
	hwcm_fee_config_body()
	{
		memset(this, 0, sizeof(*this));
		assert(sizeof(*this) == 88);
	}
	T_CUST_ID			m_ClientID;
	T_FUND_ACCOUNT_TYPE	m_FundAccountType;
	uInt8				m_ExchID;
	T_SECU_FULL_TYPE	m_SecuFullType;
	T_SIDE				m_Side;
	uInt8 				m_IsUseSubType;
	uInt8				m_Reserved0[1];
	T_FUND_ACCOUNT		m_FundAccount;
	uInt8				m_Reserved1[3];
	T_FEE_TYPE			m_FeeIdx;
	uInt8				m_FeeLevel;
	uInt8				m_Reserved2[2];
	T_RATE_8			m_FeeAmount;
	T_PRICE_4			m_FeeQty;
	T_PRICE_4			m_FeeMin;
	T_PRICE_4			m_FeeMax;
	uInt8				m_Reserved3[8];
};


//逆回购费率配置信息，8018
struct hwcm_repo_fee_config_hdr
{
	hwcm_repo_fee_config_hdr()
	{
		memset(this, 0, sizeof(*this));
		m_CommonHdr.m_StdHdr.m_MsgType = hwcm_types::HWCM_REPO_FEE_CONFIG;
		m_CommonHdr.m_StdHdr.m_MsgLen = sizeof(*this);
	}
	hwcm_common_hdr	m_CommonHdr;
};
struct hwcm_repo_fee_config_body
{
	hwcm_repo_fee_config_body()
	{
		memset(this, 0, sizeof(*this));
		assert(sizeof(*this) == 40);
	}	

	T_SECURITY_CODE		m_SecurityCode;
	T_EXCHANGE			m_ExchID;
	T_SECU_FULL_TYPE	m_SecuFullType;
	uInt8				m_Reserved1[4];
	T_RATE_8			m_FeeAmount;
	T_RATE64_4			m_FeeMin ;
	T_PRICE32_4			m_ParValue ;
	uInt8				m_Reserved2[4] ;
};


// 配置账户品种控制，8019
struct hwcm_account_variety_authority_config_hdr
{
	hwcm_account_variety_authority_config_hdr()
	{
		memset(this, 0, sizeof(*this));
		m_CommonHdr.m_StdHdr.m_MsgType = hwcm_types::HWCM_VARIETY_AUTHORITY_CONFIG;
		m_CommonHdr.m_StdHdr.m_MsgLen = sizeof(*this);
	}
	hwcm_common_hdr	m_CommonHdr;
};

struct hwcm_account_variety_authority_config_body
{
	hwcm_account_variety_authority_config_body()
	{
		memset(this, 0, sizeof(*this));
		assert(sizeof(*this) == 88);
	}
	
	T_CUST_ID			m_ClientID;
	T_FUND_ACCOUNT_TYPE	m_FundAccountType;
	uInt8				m_Reserved1[1];
	T_EXCHANGE			m_ExchID;
	T_SECU_FULL_TYPE	m_SecuFullType;
	uInt8				m_Reserved2[26];
	T_EXCHANGE_ACCOUNT	m_ExchangeAccount;
	uInt8 				m_SideBits;
	uInt8				m_Reserved3[23];
};

// 期权组合策略配置信息(8020)
struct hwcm_comb_strategy_config_hdr
{
	hwcm_comb_strategy_config_hdr()
	{
		memset(this, 0, sizeof(*this));
		m_CommonHdr.m_StdHdr.m_MsgType = hwcm_types::HWCM_COMB_STRATEGY_CONFIG;
		m_CommonHdr.m_StdHdr.m_MsgLen = sizeof(*this);
	}
	hwcm_common_hdr	m_CommonHdr;
};

struct comb_strategy_config
{
	T_SECURITY_CODE		m_UnderlyingSecurityID;	///<	标的证券代码
	T_EXCHANGE			m_UnderlyingExchID;		///< 	标的证券交易所ID
	T_SECU_FULL_TYPE	m_SecurityType;			///<	
	uInt8				m_Reserved[4];			///< 保留
};

struct hwcm_comb_strategy_config_body
{
	hwcm_comb_strategy_config_body()
	{}
	
	T_COMB_STRATEGY_ID	m_StrategyID;	///< 组合策略编码
	T_EXCHANGE				m_ExchID;		///< 交易所	
	uInt8					m_LegList;		///< 组合策略包含的成份合约信息，一个成份合约对应一条 Leg记录，以下为二级循环体。最多4腿
	uInt8					m_Reserved;		///< 保留
	comb_strategy_config	m_Leg[4];
};


// 期权组合策略标的清单(8021)
struct hwcm_comb_strategy_underlying_config_hdr
{
	hwcm_comb_strategy_underlying_config_hdr()
	{
		memset(this, 0, sizeof(*this));
		m_CommonHdr.m_StdHdr.m_MsgType = hwcm_types::HWCM_COMB_STRATEGY_UNDERLYING_CONF;
		m_CommonHdr.m_StdHdr.m_MsgLen = sizeof(*this);
	}
	hwcm_common_hdr	m_CommonHdr;
};

struct comb_strategy_underlying_config
{
	T_SECURITY_CODE		m_UnderlyingSecurityID;	///< 标的证券代码
	T_EXCHANGE			m_UnderlyingExchID;		///< 标的证券交易所ID
	T_SECU_FULL_TYPE	m_SecurityType;			///< 证券类型 
	uInt8				m_Reserved[4];			///< 保留
};

// 期权组合策略标的清单(8021)
struct hwcm_comb_strategy_underlying_config_body
{
	hwcm_comb_strategy_underlying_config_body()
	{}
	
	T_COMB_STRATEGY_ID					m_StrategyID;	///< 组合策略编码
	T_EXCHANGE							m_ExchID;		///< 所属交易所
	uInt8								m_LegList;		///< 组合策略包含的成份合约信息，一个成份合约对应一条 Leg记录，以下为二级循环体。最多4腿
	uInt8								m_Reserved;		///<  保留
	comb_strategy_underlying_config		m_Underlying[4];
};

//实时出入金,8009本消息不会多条一起发送，设计这个形式是为了8xxx一套协议的一致性，BatchFlag总是0，TotalGroup和NumGroup总是1
struct hwcm_tradingtime_cash_inout
{
	hwcm_tradingtime_cash_inout()
	{
		memset(this, 0, sizeof(*this));
		m_CommonHdr.m_StdHdr.m_MsgType = hwcm_types::HWCM_TRADINGTIME_CASH_INOUT;
		m_CommonHdr.m_StdHdr.m_MsgLen = sizeof(*this);		
		m_CommonHdr.m_BatchFlag = rem_batch_flag::BF_SINGLE_PACKAGE;
		m_CommonHdr.m_TotalGroup = 1;
		m_CommonHdr.m_NumGroup = 1;
	}
	hwcm_common_hdr		m_CommonHdr;
	T_CUST_ID	m_ClientID;
	T_FUND_ACCOUNT_TYPE	m_FundAccountType;
	uInt8				m_InOrOut;//0-入金,1-出金
	uInt8				m_Reserved1[5];
	T_PRICE_4			m_Amount;
	T_FUND_ACCOUNT		m_FundAccount;	
	uInt8				m_Reserved[7];
	
};


//期权保证金率配置信息,8010
struct hwcm_opt_margin_config_hdr
{
	hwcm_opt_margin_config_hdr()
	{
		memset(this, 0, sizeof(*this));
		m_CommonHdr.m_StdHdr.m_MsgType = hwcm_types::HWCM_OPT_MARGIN_CONFIG;
		m_CommonHdr.m_StdHdr.m_MsgLen = sizeof(*this);
	}
	hwcm_common_hdr	m_CommonHdr;
};
struct hwcm_opt_margin_config_body
{
	hwcm_opt_margin_config_body()
	{
		memset(this, 0, sizeof(*this));
		assert(sizeof(*this) == 112);
	}
	T_CUST_ID	m_ClientID;
	T_FUND_ACCOUNT_TYPE	m_FundAccountType;
	uInt8				m_Reserved1[6];
	T_FUND_ACCOUNT		m_FundAccount;	
	T_SECURITY_CODE		m_UnderlyingSecuCode;
	T_SECURITY_CODE		m_SecurityCode;
	T_EXCHANGE			m_UnderlyingExchID;
	T_EXCHANGE			m_ExchID;	
	T_OPT_CALL_PUT		m_CallOrPut;
	uInt8				m_MarginFlag;	// 0：第一次配置保证金率 	1：配置动态保证金
	uInt8				m_Reserved2;
	T_PRICE_4			m_DynamicMargin ;
	T_PRICE_4			m_ExchangeMargin ;
	T_PRICE_4			m_BreakMargin ;
	T_PRICE_4			m_Reserved5;
	T_PRICE_4			m_Reserved6;
	T_PRICE_4			m_Reserved7;
};

//风控门限值配置,8012
struct hwcm_risk_threshold_config_hdr
{
	hwcm_risk_threshold_config_hdr()
	{
		memset(this, 0, sizeof(*this));
		m_CommonHdr.m_StdHdr.m_MsgType = hwcm_types::HWCM_RISK_THRESHOLD_CONFIG;
		m_CommonHdr.m_StdHdr.m_MsgLen = sizeof(*this);
	}
	hwcm_common_hdr	m_CommonHdr;
};
struct hwcm_risk_threshold_config_body
{
	hwcm_risk_threshold_config_body()
	{
		memset(this, 0, sizeof(*this));
		assert(sizeof(*this) == 112);
	}
	T_CUST_ID	m_ClientID;
	uInt8				m_Reserved1[5];
	T_FUND_ACCOUNT_TYPE	m_FundAccountType;	
	T_EXCHANGE			m_ExchID;
	T_FUND_ACCOUNT		m_FundAccount;	
	uInt8				m_Reserved2[7];
	T_SECURITY_CODE		m_SecurityCode;
	uInt8				m_Reserved3[5];
	T_SECU_FULL_TYPE	m_SecuFullType;
	uInt16				m_RiskRuleID;
	T_RISK_RULE_TYPE	m_RiskRuleType;
	uInt8				m_RuleValueNum;
	uInt8				m_RuleTimeNum;
	uInt8				m_Reserved4[3];
	uInt64				m_RiskRuleValue1;
	uInt64				m_RiskRuleValue2;
	uInt64				m_RiskRuleTime1;
	uInt64				m_RiskRuleTime2;
	uInt8				m_Reserved5[8];

};

//配置结束消息8013, 目前不需要这个
struct hwcm_all_config_done
{
	hwcm_all_config_done()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = hwcm_types::HWCM_ALL_CONFIG_DONE;
		m_Header.m_MsgLen = sizeof(*this);		
	}
	msg_standard_hdr	m_Header;	
};

//单独给硬件刷一遍不重复的ClientID，8014，必须在8002之前配置
struct hwcm_client_id_list_config_hdr
{
	hwcm_client_id_list_config_hdr()
	{
		memset(this, 0, sizeof(*this));
		m_CommonHdr.m_StdHdr.m_MsgType = hwcm_types::HWCM_CLIENT_ID_LIST_CONFIG;
		m_CommonHdr.m_StdHdr.m_MsgLen = sizeof(*this);		
	}
	hwcm_common_hdr	m_CommonHdr;
};

struct hwcm_client_id_list_config_body
{
	hwcm_client_id_list_config_body()
	{
		memset(this, 0, sizeof(*this));
		assert(sizeof(*this) == 24);
	}
	T_CUST_ID	m_ClientID;
	uInt8				m_Reserved[7];
};


//自成交用，最优价更新，8015
struct hwcm_self_trade_price_config_hdr
{
	hwcm_self_trade_price_config_hdr()
	{
		memset(this, 0, sizeof(*this));
		m_CommonHdr.m_StdHdr.m_MsgType = hwcm_types::HWCM_SELF_TRADE_PRICE_CONFIG;
		m_CommonHdr.m_StdHdr.m_MsgLen = sizeof(*this);
	}
	hwcm_common_hdr	m_CommonHdr;
};
struct hwcm_self_trade_price_config_body
{
	hwcm_self_trade_price_config_body()
	{
		memset(this, 0, sizeof(*this));
		assert(sizeof(*this) == 88);
	}

	T_CUST_ID					m_ClientID;
	uInt8						m_Reserved1[5];
	T_FUND_ACCOUNT_TYPE			m_FundAccountType;
	T_EXCHANGE					m_ExchID;
	T_FUND_ACCOUNT				m_FundAccount;
	uInt8						m_Reserved2[7];
	T_SECURITY_CODE				m_SecurityCode;
	uInt8						m_Reserved3[5];
	T_SECU_FULL_TYPE			m_SecurityFullType;
	T_PRICE_4					m_HighBidPrice;
	T_PRICE_4					m_LowAskPrice;	
	T_SELF_TRADE_UPDATE_FLAG	m_Flag;
	uInt8						m_Reserved4[7];
};

struct hwcm_self_trade_price_config
{
	hwcm_self_trade_price_config_hdr m_hdr;
	hwcm_self_trade_price_config_body m_body;
};

//风控开关配置，8016
struct hwcm_risk_switch_config_hdr
{
	hwcm_risk_switch_config_hdr()
	{
		memset(this, 0, sizeof(*this));
		m_CommonHdr.m_StdHdr.m_MsgType = hwcm_types::HWCM_RISK_SWITCH_CONFIG;
		m_CommonHdr.m_StdHdr.m_MsgLen = sizeof(*this);
	}
	hwcm_common_hdr	m_CommonHdr;
};
struct one_switch
{
	uInt8		m_RuleId;
	uInt8		m_IsOn;
};
#define CNF_SWITCHES_COUNT 64 
struct hwcm_risk_switch_config_body
{
	hwcm_risk_switch_config_body()
	{
		memset(this, 0, sizeof(*this));
		assert(sizeof(*this) == 176);

		// 初始化数据
		for (uInt8 i = 0; i < CNF_SWITCHES_COUNT; i++)
		{
			m_Switches[i].m_RuleId = i + 1;
			if (i < 3)
				m_Switches[i].m_IsOn = 1;
			else
				m_Switches[i].m_IsOn = 0;
		}
	}

	T_CUST_ID			m_ClientID;
	uInt8				m_Reserved1[6];
	T_FUND_ACCOUNT_TYPE	m_FundAccountType;	
	T_FUND_ACCOUNT		m_FundAccount;
	uInt8				m_Reserved2[7];
	one_switch			m_Switches[CNF_SWITCHES_COUNT];
};

//6.18	硬件数据库导出请求(8017)本消息不会多条一起发送，设计这个形式是为了8xxx一套协议的一致性，BatchFlag总是0，TotalGroup和NumGroup总是1
struct hwcm_risk_db_export_request
{
	hwcm_risk_db_export_request()
	{
		memset(this, 0, sizeof(*this));
		m_CommonHdr.m_StdHdr.m_MsgType = hwcm_types::HWCM_RISK_DB_EXPORT_REQUEST;
		m_CommonHdr.m_StdHdr.m_MsgLen = sizeof(*this);		
		m_CommonHdr.m_BatchFlag = rem_batch_flag::BF_SINGLE_PACKAGE;
		m_CommonHdr.m_TotalGroup = 1;
		m_CommonHdr.m_NumGroup = 1;
	}
	hwcm_common_hdr		m_CommonHdr;
	T_CUST_ID	m_ClientID;
	uInt8				m_Reserved[5];
	T_FUND_ACCOUNT_TYPE	m_FundAccountType;
	T_EXCHANGE			m_ExchID;
	T_FUND_ACCOUNT		m_FundAccount;	
	uInt8				m_Reserved1[6];
	//T_TRADE_TYPE		m_TradeType;
	T_SIDE				m_side;
	T_SECURITY_CODE		m_SecurityCode;
	uInt8				m_Reserved2[5];
	T_SECU_FULL_TYPE	m_SecurityFullType;
	T_RISK_DB_FLAG		m_RiskDBFlag;	
	uInt8				m_Reserved3[7];
};


//新的回滚方式，回滚普通股票/ETF等的实时仓位信息，使用配置接口配置下去, 8100
struct hwcm_rewind_runtime_normal_position_hdr
{
	hwcm_rewind_runtime_normal_position_hdr()
	{
		memset(this, 0, sizeof(*this));
		m_CommonHdr.m_StdHdr.m_MsgType = hwcm_types::HWCM_REWIND_RUNTIME_NORMAL_POSITION;
		m_CommonHdr.m_StdHdr.m_MsgLen = sizeof(*this);
	}
	hwcm_common_hdr	m_CommonHdr;
};
struct hwcm_rewind_runtime_normal_position_body
{
	hwcm_rewind_runtime_normal_position_body()
	{
		memset(this, 0, sizeof(*this));
		assert(sizeof(*this) == 104);
	}

	T_CUST_ID	m_ClientID;
	uInt8				m_Reserved1[5];
	T_FUND_ACCOUNT_TYPE	m_FundAccountType;
	T_EXCHANGE			m_ExchID;
	T_FUND_ACCOUNT		m_FundAccount;
	uInt8				m_Reserved2[7];
	T_SECURITY_CODE		m_SecurityCode;
	uInt8				m_Reserved3[5];
	T_SECU_FULL_TYPE	m_SecurityFullType;
	uInt32				m_OvnPosQty;
	uInt32				m_TodayPositionQty;
	uInt32				m_OvnCoveredLockedQty;
	uInt32				m_TodayCoveredLockedQty;
	uInt32				m_OvnCoveredLockPendingQty;
	uInt32				m_TodayCoveredLockPendingQty;
	uInt32				m_CoveredPledgedQty;
	uInt32				m_CoveredUnlockPendingQty;
	uInt32				m_ClosePosPendingQty;
	uInt8				m_Reserved4[4];
};

//新的回滚方式，回滚期权的实时仓位信息，使用配置接口配置下去, 8101
struct hwcm_rewind_runtime_option_position_hdr
{
	hwcm_rewind_runtime_option_position_hdr()
	{
		memset(this, 0, sizeof(*this));
		m_CommonHdr.m_StdHdr.m_MsgType = hwcm_types::HWCM_REWIND_RUNTIME_OPTION_POSITION;
		m_CommonHdr.m_StdHdr.m_MsgLen = sizeof(*this);
	}
	hwcm_common_hdr	m_CommonHdr;
};
struct hwcm_rewind_runtime_option_position_body
{
	hwcm_rewind_runtime_option_position_body()
	{
		memset(this, 0, sizeof(*this));
		assert(sizeof(*this) == 88 );
	}

	T_CUST_ID	m_ClientID;
	uInt8				m_Reserved1[5];
	T_FUND_ACCOUNT_TYPE	m_FundAccountType;
	T_EXCHANGE			m_ExchID;
	T_FUND_ACCOUNT		m_FundAccount;
	uInt8				m_Reserved2[7];
	T_SECURITY_CODE		m_SecurityCode;
	uInt8				m_Reserved3[5];
	T_SECU_FULL_TYPE	m_SecurityFullType;
	uInt32				m_LongPosQty;
	uInt32				m_ShortPosQty;
	uInt32				m_CoveredPosQty;

	uInt32				m_AllShortMarginQty;
	uInt32				m_CoveredClosePedQty ;
	uInt32				m_ShortClosePedQty ;

	//uInt8				m_Reserved4[4];
};

//新的回滚方式，风控累加值，包括BP的运行时状态回滚，使用配置接口配置下去, 8102
struct hwcm_rewind_risk_statistics_hdr
{
	hwcm_rewind_risk_statistics_hdr()
	{
		memset(this, 0, sizeof(*this));
		m_CommonHdr.m_StdHdr.m_MsgType = hwcm_types::HWCM_REWIND_RISK_STATISTICS;
		m_CommonHdr.m_StdHdr.m_MsgLen = sizeof(*this);
	}
	hwcm_common_hdr	m_CommonHdr;
};
struct hwcm_rewind_risk_statistics_body
{
	hwcm_rewind_risk_statistics_body()
	{
		memset(this, 0, sizeof(*this));
	}

	T_CUST_ID	m_ClientID;
	uInt8				m_Reserved1[5];
	T_FUND_ACCOUNT_TYPE	m_FundAccountType;
	T_EXCHANGE			m_ExchID;
	T_FUND_ACCOUNT		m_FundAccount;
	uInt8				m_Reserved2[7];
	T_SECURITY_CODE		m_SecurityCode;
	uInt8				m_Reserved3[5];
	T_SECU_FULL_TYPE	m_SecurityFullType;
	uInt16				m_RiskRuleID;
	T_RISK_RULE_TYPE	m_RiskRuleType;
	uInt8				m_Reserved4[5];
	T_PRICE_4			m_RiskRuleValue1;
	T_PRICE_4			m_RiskRuleValue2;
	uInt8				m_Reserved5[8];
};

//用户TCP流控配置消息, 8200
struct hwcm_user_flow_control_hdr
{
	hwcm_user_flow_control_hdr()
	{
		memset(this, 0, sizeof(*this));
		m_CommonHdr.m_StdHdr.m_MsgType = hwcm_types::HWCM_USER_FLOW_CONTROL;
		m_CommonHdr.m_StdHdr.m_MsgLen = sizeof(*this);
	}
	hwcm_common_hdr	m_CommonHdr;
};
struct hwcm_user_flow_control_body
{
	hwcm_user_flow_control_body()
	{
		memset(this, 0, sizeof(*this));
	}

	T_user_id		m_UserID;
	uInt32			m_time;
	uInt32			m_control_value;
	uInt8			m_switch;
	uInt8			m_Reserved[3];
};

//#报错处理的模块



///<出错反馈对应模块
enum msg_error_module_id
{
	ERR_MODULE_ID_RESERVED = 0,
	ERR_MODULE_ID_CONFIG = 1,
	ERR_MODULE_ID_GRAMMAR_CHECK = 2,
	ERR_MODULE_ID_REWIND = 3,
	ERR_MODULE_ID_ORDER_MGR = 4,
	ERR_MODULE_ID_MKT_RSP_MODULE = 5,
	ERR_MODULE_ID_RISK_MGR_MODULE = 6,
	ERR_MODULE_ID_CAM_CONFIG = 7,
	ERR_MODULE_ID_MI_CONFIG = 8,
	ERR_MODULE_ID_HW_MI = 9,
	ERR_MODULE_ID_Binary_Ctrl_Err = 10,
};

///<ERR_MODULE_ID_CONFIG = 1, ErrorID的取值范围
namespace hwerr_config_error_id
{
	enum _
	{
		CFG_ERROR_ID_MSG_TYPE = 1,//不在协议范围内
		CFG_ERROR_ID_PACKAGE_LENGTH = 2,//beats数与协议不符合
		CFG_ERROR_ID_ACCOUNT_ID_NOT_FOUND = 4,//account cam表没有配置或者查找出错
		CFG_ERROR_ID_SYMBOL_ID_NOT_FOUND = 8,//Symbol cam表没有配置或者查找出错
		CFG_ERROR_ID_CLIENT_CAM_FAILED = 16,//配置client cam 失败
		CFG_ERROR_ID_SYMBOL_CAM_FAILED = 32, //配置symbol cam 失败
		CFG_ERROR_ID_ACCOUNT_STRUCT_FIELD_ERROR = 64,//8002消息中某个字段出错
		CFG_ERROR_ID_PACKAGE_NOT_COMPLETE = 128,
	};
}

///<ERR_MODULE_ID_GRAMMAR_CHECK = 2, ErrorID的取值范围
namespace hwerr_grammar_error_id
{
	enum _
	{
		GRAMMAR_ERROR_ID_MSG_TYPE = 1,//不在协议范围内
		GRAMMAR_ERROR_ID_PACKAGE_LENGTH = 2,//beats数与协议不符合
		GRAMMAR_ERROR_ID_MSG_TYPE_AND_LENGTH = 3, //Msg_type错误 且长度错
		GRAMMAR_ERROR_ID_ORDER_BEFORE_REWIND = 4,//回滚未完成就收到下单消息
		GRAMMAR_ERROR_ID_ORDER_BEFORE_REWIND_AND_MSG_TYPE = 5,//回滚未完成就收到下单消息，且消息类型错（在当前版本中不会出现）
		GRAMMAR_ERROR_ID_ORDER_BEFORE_REWIND_AND_MSG_LENGTH = 6,//回滚未完成就收到下单消息，且消息长度错
		GRAMMAR_ERROR_ID_ORDER_BEFORE_REWIND_AND_MSG_TYPE_AND_LENGTH = 7,//回滚未完成就收到下单消息，且消息类型和长度都错
	};
}

///<ERR_MODULE_ID_REWIND = 3, ErrorID的取值范围
namespace hwerr_rewind_error_id
{
	enum _
	{
		REWIND_ERROR_ID_MSG_TYPE = 1,//不在协议范围内
		REWIND_ERROR_ID_PACKAGE_LENGTH = 2,//beats数与协议不符合
		REWIND_ERROR_ID_REWIND_NOT_IN_EXPECTED_ORDER = 3, //在一轮完整回滚完成前，回滚步骤顺序出错
		REWIND_ERROR_ID_DUPLICATED_REWIND = 4,//已经完成一轮回滚之后，又收到多余的回滚消息		
	};
}

///<ERR_MODULE_ID_ORDER_MGR = 4, ErrorID的取值范围
namespace hwerr_om_error_id
{
	enum _
	{
		OM_ERROR_ID_ORDER_CAPACITY_WARN = 2,//下单总量到达预警值（语法检查有报错）
		OM_ERROR_ID_ORDER_CAPACITY_EXCEEDED = 3,//下单总量超过预设内存值
		OM_ERROR_ID_RISK_RESP_TIMEOUT = 4, //risk响应超出看门狗时限
	};
}

///<ERR_MODULE_ID_MKT_RSP_MODULE = 5, ErrorID的取值范围
namespace hwerr_mkt_rsp_error_id
{
	enum _
	{
		MKT_RSP_ERROR_ID_MSG_TYPE = 1,//不在协议范围内
		MKT_RSP_ERROR_ID_PACKAGE_LENGTH = 2,//beats数与协议不符合
		MKT_RSP_ERROR_ID_NOT_FOUND_ORDER_ID = 3, //8037找不到37
		MKT_RSP_ERROR_ID_RSP_NOT_IN_EXPECTED_ORDER = 4,//市场回单顺序错误
		MKT_RSP_ERROR_ID_INVALID_RSP = 5,//市场回单不合法
		MKT_RSP_ERROR_ID_EXECUTION_PRICE_0 = 6,//成交回报时price域为0
		MKT_RSP_ERROR_ID_EXECUTION_QTY_0 = 7,//成交回报数量为0
		MKT_RSP_ERROR_ID_EXECUTION_ID_DUPLICATED = 8, //成交8017号重复
		MKT_RSP_ERROR_ID_SYMBOL_INVALID = 9,//Symbol 错误
		MKT_RSP_ERROR_ID_CLIENT_ID_INVALID = 10,//Client id 错误


	};
}

///<ERR_MODULE_ID_RISK_MGR_MODULE = 6,, ErrorID的取值范围
namespace hwerr_risk_error_id
{
	enum _
	{
		RISK_ERROR_ID_CALCULATION_OVERRUN = 1,//计算公式溢出
		RISK_ERROR_ID_STOCK_POS_QUEUE_TOO_LONG = 2,//股票持仓队列容量到达预警值
		RISK_ERROR_ID_OPTION_POS_QUEUE_TOO_LONG = 3,//期权持仓队列容量到达预警值
		RISK_ERROR_ID_MARGIN_POS_QUEUE_TOO_LONG = 4,//融资融券仓位容量到达预警值
	};
}

///<ERR_MODULE_ID_CAM_CONFIG = 7, ErrorID的取值范围
namespace hwerr_cam_error_id
{
	enum _
	{
		CAM_ERROR_ID_SYMBOL_TOO_MANY = 1,//Symbol 量超过动态分配预警
		CAM_ERROR_ID_CLIENT_ID_TOO_MANY = 2,//Client id 超过硬件容量
	};
}

//硬件报错信息，1210
struct cmhs_comm_error_msg_common_header
{
	cmhs_comm_error_msg_common_header()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = cmhs_types::CMHS_HTOS_HW_ERROR_REPORT;
		//长度为动态值。
	}
	msg_standard_hdr	m_Header;
	uInt8				m_ErrorID;
	uInt8				m_Reserved1;//StateID
	uInt16				m_ModuleID;
	uInt8				m_Reserved2[4];
	uInt8				m_ErrorDetailOrOrderState;//ModuleID=1(ERR_MODULE_ID_CONFIG)时，这是ErrorDetail， ModuleID=5时，这是OrderState，其它不用
	uInt8				m_ServerId;
	uInt8				m_PlatformState;
	uInt8				m_Reserved3[13];
};

struct cmhs_tds_ctrl_error_msg
{
	cmhs_tds_ctrl_error_msg()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = cmhs_types::CMHS_HTOS_HW_ERROR_REPORT;
		//长度为动态值。
	}
	msg_standard_hdr	m_Header;
	uInt8				m_ErrorID;
	uInt8				stateID;//StateID
	uInt16				m_ModuleID;
	uInt8				m_Reserved2[4];
	uInt8				m_KiwiSessionId;
	uInt8				m_ServerId;
	uInt32				m_TdsReqnum;
	uInt8				m_Reserved3[10];

	uInt8				m_TdsOriMsg[0];
};

//硬件数据库导出，1211，注意此处一个消息类型，可能对应3种结构体，不过3种结构体的长度都一样，所以可以用强制指针类型转换处理
// 首先，前104个字节都是统一的，然后根据RiskDBFlag，判断是rule累加值导出(=1)还是仓位导出(=2)
// 如果是仓位导出，则还需要根据SecurityCode,或者AccountType, 或者SecurityFullType，来判断是否股票/ETF仓位，还是期权仓位
// 下面几个结构体不会由软件创建，构造函数无所谓了。
struct cmhs_htos_hw_data_report_common_header
{
	cmhs_htos_hw_data_report_common_header()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = cmhs_types::CMHS_HTOS_HW_ERROR_REPORT;
		m_Header.m_MsgLen = 104+224;//104是通用头长度
	}

	msg_standard_hdr	m_Header;
	uInt8				m_Reserved[2];
	uInt16				m_ModuleID;
	uInt8				m_Reserved1[20];
	T_CUST_ID	m_ClientID;
	uInt8				m_Reserved2[5];
	T_FUND_ACCOUNT_TYPE	m_FundAccountType;
	T_EXCHANGE			m_ExchID;
	T_FUND_ACCOUNT		m_FundAccount;	
	uInt8				m_Reserved3[6];
	T_TRADE_TYPE		m_TradeType;
	T_SECURITY_CODE		m_SecurityCode;
	uInt8				m_Reserved4[5];
	T_SECU_FULL_TYPE	m_SecurityFullType;
	T_RISK_DB_FLAG		m_RiskDBFlag;
	uInt8				m_Reserved5[7];
};
//risk_db = 1, 除期权品种类之外的累加值
struct data_report_risk_accumate_value_report_body
{
	data_report_risk_accumate_value_report_body()
	{
		assert(sizeof(*this) == 328);
	}
	cmhs_htos_hw_data_report_common_header m_CommonHdr;
	T_PRICE_4			m_AvailBp;

	uInt32				m_RiskRule8AccumVal;
	uInt32				m_RiskRule9AccumVal;
	uInt32				m_RiskRule10AccumVal;
	uInt32				m_RiskRule11AccumVal;
	uInt32				m_RiskRule12AccumVal;
	uInt32				m_RiskRule13AccumVal;

	uInt32				m_RiskRule14AccumVal;
	uInt32				m_RiskRule14TimeVal;
	uInt32				m_RiskRule15AccumVal;
	uInt32				m_RiskRule15TimeVal;
	uInt32				m_RiskRule16AccumVal;
	uInt32				m_RiskRule16TimeVal;
	uInt32				m_RiskRule17AccumVal;
	uInt32				m_RiskRule17TimeVal;
	uInt32				m_RiskRule18AccumVal;
	uInt32				m_RiskRule18TimeVal;
	uInt32				m_RiskRule19AccumVal;
	uInt32				m_RiskRule19TimeVal;
	uInt32				m_RiskRule20AccumVal;
	uInt32				m_RiskRule20TimeVal;
	uInt32				m_RiskRule21AccumVal;
	uInt32				m_RiskRule21TimeVal;
	uInt32				m_RiskRule22AccumVal;
	uInt32				m_RiskRule22TimeVal;
	uInt32				m_RiskRule23AccumVal;
	uInt32				m_RiskRule23TimeVal;
	uInt32				m_RiskRule24AccumVal;
	uInt32				m_RiskRule24TimeVal;
	uInt32				m_RiskRule25AccumVal;
	uInt32				m_RiskRule25TimeVal;
	uInt32				m_RiskRule26AccumVal;
	uInt32				m_RiskRule26TimeVal;
	uInt32				m_RiskRule27AccumVal;
	uInt32				m_RiskRule27TimeVal;
	uInt32				m_RiskRule28AccumVal;
	uInt32				m_RiskRule28TimeVal;
	uInt32				m_RiskRule29AccumVal;
	uInt32				m_RiskRule29TimeVal;
	uInt32				m_RiskRule30AccumVal;
	uInt32				m_RiskRule30TimeVal;
	uInt32				m_RiskRule31AccumVal;
	uInt32				m_RiskRule31TimeVal;

	T_PRICE_4			m_RiskRule34AccumVal;
	T_PRICE_4			m_RiskRule35AccumVal;

	T_PRICE_4			m_RiskRule54AccumVal;
	T_PRICE_4			m_RiskRule48AccumVal;
	T_PRICE_4			m_RiskRule49AccumVal;
	T_PRICE_4			m_Equities;
};
//risk_db = 2, 普通股票及ETF仓位
struct data_report_normal_position_report_body
{
	data_report_normal_position_report_body()
	{
		assert(sizeof(*this) == 328);
	}
	cmhs_htos_hw_data_report_common_header m_CommonHdr;
	uInt32				m_OvnPosQty;
	uInt32				m_TodayPositionQty;
	uInt32				m_OvnCoveredLockedQty;
	uInt32				m_TodayCoveredLockedQty;
	uInt32				m_OvnCoveredLockPendingQty;
	uInt32				m_TodayCoveredLockPendingQty;
	uInt32				m_CoveredPledgedQty;
	uInt32				m_CoveredUnlockPendingQty;
	uInt32				m_ClosePosPendingQty;
	uInt32				m_CumQtyDay;
	uInt8				m_Reserved[184];

};
//risk_db = 2, 期权仓位，包括36-46的累加值
struct data_report_option_position_report_body
{
	data_report_option_position_report_body()
	{
		assert(sizeof(*this) == 328);
	}
	cmhs_htos_hw_data_report_common_header m_CommonHdr;
	uInt32				m_AvailLongPosQty;
	uInt32				m_AvailShortPosQty;
	uInt32				m_AvailCoveredPosQty;
	uInt32				m_ShortMarginPosQty;		// 	期权空仓保证金仓位数量	（计算实时保证金变化量时需要用到的仓位数量）
	uInt32				m_CoveredClosePedQty ;		// 备兑平仓挂单数量
	uInt32				m_ShortClosePedQty;			// 期权空仓挂单数量
	uInt32				m_RiskRule37AccumVal;
	uInt32				m_RiskRule38AccumVal;
	uInt32				m_RiskRule40AccumVal;
	uInt32				m_RiskRule41AccumVal;
	uInt32				m_RiskRule45AccumVal;
	uInt32				m_RiskRule46AccumVal;
	uInt32				m_RiskRule51AccumVal;
	uInt8				m_Reserved[172];
	uInt32				RiskRule36AccumVal()
	{
		return m_RiskRule37AccumVal + m_RiskRule38AccumVal;
	}
	uInt32				RiskRule39AccumVal()
	{
		return m_RiskRule40AccumVal + m_RiskRule41AccumVal;
	}
	uInt32				RiskRule42AccumVal()
	{
		return RiskRule36AccumVal() + RiskRule39AccumVal();
	}
	uInt32				RiskRule43AccumVal()
	{
		return m_RiskRule37AccumVal + m_RiskRule41AccumVal;
	}
	uInt32				RiskRule44AccumVal()
	{
		return m_RiskRule38AccumVal + m_RiskRule40AccumVal;
	}
};

//risk_db = 3, 费率、涨跌停等
struct data_report_symbol_other_info_body
{
	data_report_symbol_other_info_body()
	{
		assert(sizeof(*this) == 328);
	}
	cmhs_htos_hw_data_report_common_header m_CommonHdr;
	T_PRICE_4		m_LastClosePrice;
	T_PRICE_4		m_UpperLimitPrice;
	T_PRICE_4		m_LowerLimitPrice;
	T_PRICE_4		m_MarginRate;
	uInt32			m_VolumeMultipler;
	uInt8			m_Reserved1[4];
	T_RATE_8		m_FeeAmount0;
	T_PRICE_4		m_FeeQty0;
	T_PRICE_4		m_FeeMin0;
	T_PRICE_4		m_FeeMax0;

	T_RATE_8		m_FeeAmount1;
	T_PRICE_4		m_FeeQty1;
	T_PRICE_4		m_FeeMin1;
	T_PRICE_4		m_FeeMax1;

	T_RATE_8		m_FeeAmount2;
	T_PRICE_4		m_FeeQty2;
	T_PRICE_4		m_FeeMin2;
	T_PRICE_4		m_FeeMax2;

	T_RATE_8		m_FeeAmount3;
	T_PRICE_4		m_FeeQty3;
	T_PRICE_4		m_FeeMin3;
	T_PRICE_4		m_FeeMax3;

	uInt8			m_Reserved2[56];

};


/// 配置报盘库的时间
struct hwcm_mi_mssql_date_config
{
	hwcm_mi_mssql_date_config()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = hwmi_types::HWMI_CONFIG_TYPES_DATE_CONFIG;
		m_Header.m_MsgLen = sizeof(*this);
	}
	msg_standard_hdr m_Header;
	fix_str<9>		TradingDate; //	C9	年，月，日， YYYYMMDD，8位有效
	uInt32 BaseSecond;
	fix_str<7>		Reserved1; //	7	Bin7	保留
};



//#END，硬件配置协议

//#END，硬件相关协议



#pragma pack(pop)
