
#pragma once


#pragma pack(push, 1)
//#START，HDS消息结构体
struct hds_common_header
{
	msg_standard_hdr m_Header;
	T_OT_CLUSTER_ID  m_cluster_id;
};

/// HDS消息通用消息
struct hds_common_msg
{
	hds_common_header m_header;
	i8_sl             m_p_orin_msg_buf[0];
};

/// EMC 登陆请求
struct hdsm_emc_logon_req
{
	hds_common_header m_header;   ///< HDS公共协议头 MsgType = 3
	T_OP_LOGON_ID     m_login_id; ///< 操作员的登录ID，不区分大小写，最大有效长度15个字节
	T_PASSWORD_MD5    m_pwd; ///< 经MD5加密后的密码串，必须是32个字节的有效长度
	i8_sl			  m_operator_type;					///A: 系统管理员，B: 业务操作员
	uInt32            m_version;  ///< 协议版本号，为不影响软硬件协议，HDS系统我们使用独立的版本号
	T_MAC_ADDR		  m_mac_addr;//版本5添加，因跨网段时无法获取客户端mac地址，因此要求客户端自行送上来
	char			  m_reserved[160];//版本5添加，多留些空间用于后续功能
	hdsm_emc_logon_req()
	{
		memset(this, 0, sizeof(*this));
		m_header.m_Header.m_MsgType = hdsm_types::HDSM_EMC_LOGON_REQ;
		m_header.m_Header.m_MsgLen = sizeof(*this);
	}
};

/// EMC 登陆响应
struct hdsm_emc_logon_resp
{
	hds_common_header m_header;   ///< HDS公共协议头 MsgType = 4 消息用于HDS响应EMC的登录请求
	uInt8              m_result;   ///< 0：登录成功，其余值表示失败原因, 具体失败原因详看《Log Server & Helpdesk Server及客户端整体设计.docx》
	uInt32              m_oper_id;  ///<　操作员id，类似用户登录名-用户ID的用法。

									/*考虑到对多网卡服务的支持，EMC访问数据库时，可能会从不同于我们系统配置数据库连接串的IP地址访问，因此将这个IP地址放在这个字段中下发，客户端处理方法：
									如果该值为空白字符串，则直接使用DB_ENTRY。
									如果不为空，那么需要用这个值替换掉DB_ENTRY中，server=xxxx的部分。
									配置该值的位置在t_global_settings中，
									键值为EES_CONFIG_IP_FOR_EMC
									其余库的处理类似，只是由客户端自行读取替换而已。*/
	i8_sl			  m_db_entry_addr[EES_HDS_DB_ENTRY_ADDR_LEN + 1];
	i8_sl             m_db_entry[EES_HDS_DB_ENTRY_LEN + 1]; ///< 数据库入口字符串，前面有“MYSQL:”打头，因此emc客户端使用时需要去掉这个头。登录失败时填全0
	uInt32              m_version;  ///< 协议版本号，为不影响软硬件协议，HDS系统我们使用独立的版本号
	uInt32			  m_db_version;	///HDS返回当前系统数据库配置版本号，EMC读取t_db_version库的最大db_version值，如果不匹配，则报告该错误并退出，要求系统更新数据库版本后才能继续
	hdsm_emc_logon_resp()
	{
		memset(this, 0, sizeof(*this));
		m_header.m_Header.m_MsgType = hdsm_types::HDSM_EMC_LOGON_RESP;
		m_header.m_Header.m_MsgLen = sizeof(*this);
	}
};

/// EMC 登陆初始化完成
struct hdsm_emc_logon_finished_resp
{
	hds_common_header m_header;   ///< MsgType = 16 消息由HDS发起
	uInt32              m_oper_id;  ///<　操作员id，类似用户登录名-用户ID的用法。操作员id：99999999将被保留为系统默认全权限操作员。
	hdsm_emc_logon_finished_resp()
	{
		memset(this, 0, sizeof(*this));
		m_header.m_Header.m_MsgType = hdsm_types::HDSM_EMC_LOGON_FINISHED_RESP;
		m_header.m_Header.m_MsgLen = sizeof(*this);
	}
};

/// HDC 登陆请求
struct hdsm_hdc_logon_req
{
	hds_common_header m_header;   ///< HDS公共协议头 MsgType = 1
	uInt8              m_mod_type; ///< 模块类型: 1：LGS(log server) 2：BK  3：OT  4：HDS（这条消息不会用到）
	i8_sl             m_mod_id[EES_MODULE_ID_LEN + 1];
	uInt32              m_version;  ///< 协议版本号，为不影响软硬件协议，HDS系统我们使用独立的版本号
	char			  m_mac_addr[18];//版本5添加，因跨网段时无法获取客户端mac地址，因此要求客户端自行送上来
	char			  m_reserved[179];//版本5添加，多留些空间用于后续功能
	hdsm_hdc_logon_req()
	{
		memset(this, 0, sizeof(*this));
		m_header.m_Header.m_MsgType = hdsm_types::HDSM_HDC_LOGON_REQ;
		m_header.m_Header.m_MsgLen = sizeof(*this);
	}
};

/// HDC 登陆响应
struct hdsm_hdc_logon_resp
{
	hds_common_header m_header;   ///< HDS公共协议头 MsgType = 2
	uInt8              m_result;   ///< 0：登录成功，其余值表示失败原因, 具体失败原因详看《Log Server & Helpdesk Server及客户端整体设计.docx》
	uInt32              m_version;  ///< 协议版本号，为不影响软硬件协议，HDS系统我们使用独立的版本号
	hdsm_hdc_logon_resp()
	{
		memset(this, 0, sizeof(*this));
		m_header.m_Header.m_MsgType = hdsm_types::HDSM_HDC_LOGON_RESP;
		m_header.m_Header.m_MsgLen = sizeof(*this);
	}
};

/// EMC 心跳消息
struct hdsm_emc_heartbeat
{
	hds_common_header m_header;   ///< MsgType = 17 消息由EMC发起
	uInt32              m_oper_id;  ///<　操作员id，类似用户登录名-用户ID的用法。操作员id：99999999将被保留为系统默认全权限操作员。
	hdsm_emc_heartbeat()
	{
		memset(this, 0, sizeof(*this));
		m_header.m_Header.m_MsgType = hdsm_types::HDSM_EMC_HEARTBEAT;
		m_header.m_Header.m_MsgLen = sizeof(*this);
	}
};

/// EMC-HDS-OT通知风控规则门限值改变
struct hdsm_emc_risk_threshold_change
{
	hds_common_header m_header;   ///< MsgType = 18 消息由EMC发起,HDS_RISK_THRESHOLD_CHANGE
	uInt8             m_risk_rule_id;  ///<
	T_FUND_ACCOUNT	  m_account_id;
	T_EXCHANGE		  m_exchange_id;
	T_SECURITY_CODE	  m_symbol;
	double			  m_threshold_value1;
	double			  m_threshold_value2;
	double			  m_threshold_value3;
	hdsm_emc_risk_threshold_change()
	{
		memset(this, 0, sizeof(*this));
		m_header.m_Header.m_MsgType = hdsm_types::HDSM_RISK_THRESHOLD_CHANGE;
		m_header.m_Header.m_MsgLen = sizeof(*this);
	}
};

/// EMC-HDS-OT通知风控规则开关改变
struct hdsm_emc_risk_switch_change
{
	hds_common_header m_header;   ///< MsgType = 19 消息由EMC发起,HDS_RISK_SWITCH_CHANGE	
	T_FUND_ACCOUNT	m_account_id;
	uInt64			m_switches;
	hdsm_emc_risk_switch_change()
	{
		memset(this, 0, sizeof(*this));
		m_header.m_Header.m_MsgType = hdsm_types::HDSM_RISK_SWITCH_CHANGE;
		m_header.m_Header.m_MsgLen = sizeof(*this);
	}
};

/// EMC-HDS-OT通知用户的启用/禁用 HDS_USER_FORBIDDEN_CONTROL_MSG_ID
struct hdsm_emc_user_status_control
{
	hds_common_header m_header;   ///< MsgType = 8 消息由EMC发起,HDS_USER_FORBIDDEN_CONTROL_MSG_ID	
	uInt32			  m_user_id;
	char			  m_enabled;	///‘Y’表示启用，’N’表示禁用，对于本消息，一般都是填’N’，否则不需要发送。
	hdsm_emc_user_status_control()
	{
		memset(this, 0, sizeof(*this));
		m_header.m_Header.m_MsgType = hdsm_types::HDSM_USER_FORBIDDEN_CONTROL;
		m_header.m_Header.m_MsgLen = sizeof(*this);
	}
};


///  
struct hdsm_emc_user_logon_prodinfo
{
	hds_common_header m_header;
	uInt32			  m_user_id;
	T_CLIENT_PROD_INFO	m_prod_info;
	fix_str<16>			m_ip;
	fix_str<32>			m_mac;
	hdsm_emc_user_logon_prodinfo()
	{
		memset(this, 0, sizeof(*this));
		m_header.m_Header.m_MsgType = hdsm_types::HDSM_USER_LOGON_INFO;
		m_header.m_Header.m_MsgLen = sizeof(*this);
	}
};

/// 进程运行状态
struct process_running_status
{
	uInt32			m_tpid;					///< 进程ID

	char			m_start_time[24];		///< 启动时间 YYYYMMdd hh:mm:ss

	uInt64			m_use_memory;			///< 内存总用量
	uInt32			m_use_cpu_rate;			///< CPU 占用百分比*10000

	uInt64			m_hd_last_sec_in_bytes;		///< 磁盘两次之间的平均一秒写入量
	uInt64			m_hd_last_sec_out_bytes;	///< 磁盘两次之间的平均一秒读取量

	uInt32			m_fd_count;					///< 打开文件个数
	uInt32			m_thread_count;				///< 当前进程线程个数

};



//OT定时报告状态消息
struct hdsm_ot_monitor_report
{
	hds_common_header m_header;
	T_server_id	m_ot_id;
	uInt32	m_ot_status;					///< OT当前的状态 
	char	m_running_mode;					///< ot运行的模式
	char	m_primary_core;					///< 
	uInt32 m_onbehalf_mkt_session_id;
	uInt8	m_tpi_status;

	uInt8	m_conn_bk_status;
	uInt8	m_conn_lgs_status;
	uInt8	m_conn_eqs_status;
	uInt8	m_conn_hds_status;

	uInt32	m_background_core_queue_depth;

	process_running_status m_running_status;

	hdsm_ot_monitor_report()
	{
		memset(this, 0, sizeof(*this));
		m_header.m_Header.m_MsgType = hdsm_types::HDSM_OT_MONITOR_REPORT;
		m_header.m_Header.m_MsgLen = sizeof(*this);
	}
};

// ot 连接用户状态报告
struct hdsm_query_ot_link_client
{
	hds_common_header m_header;

	hdsm_query_ot_link_client()
	{

		memset(this, 0, sizeof(*this));
		m_header.m_Header.m_MsgType = hdsm_types::HDSM_QUERY_OT_TRADER_LINK;
		m_header.m_Header.m_MsgLen = sizeof(*this);
	}
};

struct hdsm_ot_link_client_monitor_report
{
	hds_common_header m_header;

	T_server_id	m_ot_id;
	T_server_id	m_node_id;
	uInt8   m_link_mode;		//< 0:软   1：硬
	uInt32	m_link_id;			///< 连接号
	uInt8	m_port_type;		///< 连接端口类型 1:交易 2:查询
	uInt32	m_user_id;			///< 用户号
	char	m_user_name[32];	///< 用户名
	uInt32	m_max_cl_token;		///< 当前用户最大的 token
	char	m_remote_ip[16];	///< 客户端ip 
	uInt16  m_remote_port;		///< 客户端端口
	uInt8	m_last_status;		///< 最后状态  0:正常 1：断开 2：登录失败  3：。。。。。
	char	m_last_update_time[32];	///< 最后更新时间

	hdsm_ot_link_client_monitor_report()
	{
		memset(this, 0, sizeof(*this));
		m_header.m_Header.m_MsgType = hdsm_types::HDSM_OT_TRADER_LINK_REPORT;
		m_header.m_Header.m_MsgLen = sizeof(*this);
	}
};


//BK定时报告状态消息
struct hdsm_bk_monitor_report
{
	hds_common_header m_header;
	uInt32 m_bk_status;

	uInt32 m_bk_data_queue_length;
	uInt32 m_bg_data_length;

	uInt8  m_conn_lgs_status;
	uInt8  m_conn_hds_status;

	process_running_status m_running_status;

	hdsm_bk_monitor_report()
	{
		memset(this, 0, sizeof(*this));
		m_header.m_Header.m_MsgType = hdsm_types::HDSM_BK_MONITOR_REPORT;
		m_header.m_Header.m_MsgLen = sizeof(*this);
	}
};

//LGS定时报告消息
struct hdsm_lgs_monitor_report
{
	hds_common_header m_header;
	uInt32 m_lgs_status;

	uInt32 m_queue_length;
	uInt32 m_logs_count;

	uInt8  m_conn_hds_status;
	process_running_status m_running_status;

	hdsm_lgs_monitor_report()
	{
		memset(this, 0, sizeof(*this));
		m_header.m_Header.m_MsgType = hdsm_types::HDSM_LGS_MONITOR_REPORT;
		m_header.m_Header.m_MsgLen = sizeof(*this);
	}
};

//RS定时报告消息
struct hdsm_rs_monitor_report
{
	hds_common_header m_header;
	uInt32 m_rs_status;

	uInt32 m_queue_length;

	uInt8  m_conn_lgs_status;
	uInt8  m_conn_hds_status;

	process_running_status m_running_status;

	hdsm_rs_monitor_report()
	{
		memset(this, 0, sizeof(*this));
		m_header.m_Header.m_MsgType = hdsm_types::HDSM_RS_MONITOR_REPORT;
		m_header.m_Header.m_MsgLen = sizeof(*this);
	}
};

// EQS 定时报告消息
struct hdsm_eqs_monitor_report
{
	hds_common_header m_header;
	uInt32 m_eqs_status;
	uInt32 m_eqs_client_count;

	uInt8  m_sse_cs_quote;
	uInt8  m_sse_opt_quote;
	uInt8  m_sze_cs_quote;
	uInt8  m_sze_opt_quote;

	uInt8  m_conn_lgs_status;
	uInt8  m_conn_hds_status;

	process_running_status m_running_status;

	hdsm_eqs_monitor_report()
	{
		memset(this, 0, sizeof(*this));
		m_header.m_Header.m_MsgType = hdsm_types::HDSM_EQS_MONITOR_REPORT;
		m_header.m_Header.m_MsgLen = sizeof(*this);
	}
};

// HDS 定时报告消息
struct hdsm_hds_monitor_report
{
	hds_common_header m_header;

	uInt32	m_hds_status;
	uInt8	m_conn_lgs_status;
	process_running_status m_running_status;
	hdsm_hds_monitor_report()
	{
		memset(this, 0, sizeof(*this));
		m_header.m_Header.m_MsgType = hdsm_types::HDSM_HDS_MONITOR_REPORT;
		m_header.m_Header.m_MsgLen = sizeof(*this);
	}
};

//SYNC_TRADE定时报告消息
struct hdsm_sync_trade_monitor_report
{
	hds_common_header m_header;
	uInt32 m_sync_status;
	uInt8  m_conn_sync_status;
	uInt8  m_conn_hds_status;
	uInt8  m_conn_lgs_status;
	process_running_status m_running_status;

	hdsm_sync_trade_monitor_report()
	{
		memset(this, 0, sizeof(*this));
		m_header.m_Header.m_MsgType = hdsm_types::HDSM_SYNC_TRADE_MONITOR_REPORT;
		m_header.m_Header.m_MsgLen = sizeof(*this);
	}
};
//报盘库定时报告消息
struct hdsm_sql_monitor_report
{
	hds_common_header m_header;
	uInt32 m_sql_id;
	uInt8  m_conn_sql_status;
	uInt8  m_logon_status;
	hdsm_sql_monitor_report()
	{
		memset(this, 0, sizeof(*this));
		m_header.m_Header.m_MsgType = hdsm_types::HDSM_SQL_MONITOR_REPORT;
		m_header.m_Header.m_MsgLen = sizeof(*this);
	}
};
//emc实时出入金消息
struct hdsm_emc_trading_time_cash_inout
{
	hds_common_header m_header;			//HDS_EMC_TRADING_TIME_CASH_INOUT
	T_FUND_ACCOUNT		  m_account_id;
	double			  m_changed_value;
	hdsm_emc_trading_time_cash_inout()
	{
		memset(this, 0, sizeof(*this));
		m_header.m_Header.m_MsgType = hdsm_types::HDSM_EMC_TRADING_TIME_CASH_INOUT;
		m_header.m_Header.m_MsgLen = sizeof(*this);
	}
};

//emc实时出入金消息
struct hdsm_ot_trading_time_cash_inout
{
	hds_common_header m_header;			//HDS_OT_TRADING_TIME_CASH_INOUT
	T_CUST_ID	m_ClientID;
	T_FUND_ACCOUNT_TYPE	m_FundAccountType;
	T_FUND_ACCOUNT	  m_FundAccount;
	double			  m_changed_value;
	hdsm_ot_trading_time_cash_inout()
	{
		memset(this, 0, sizeof(*this));
		m_header.m_Header.m_MsgType = hdsm_types::HDSM_OT_TRADING_TIME_CASH_INOUT;
		m_header.m_Header.m_MsgLen = sizeof(*this);
	}
};

// 实时修改用户交易状态
struct hdsm_emc_trading_time_disable_account_instrument
{
	hds_common_header m_header;

	T_CUST_ID	m_ClientID;
	T_FUND_ACCOUNT_TYPE	m_FundAccountType;
	T_FUND_ACCOUNT		m_FundAccount;
	T_EXCHANGE			m_ExchangeId;
	T_SECU_FULL_TYPE	m_SecurityType;
	T_SECURITY_CODE		m_SecurityCode;

	T_EXCHANGE			m_UnderlyingExchangeId;
	T_SECU_FULL_TYPE	m_UnderlyingSecurityType;
	T_SECURITY_CODE		m_UnderlyingSecurityCode;


	T_SIDE				m_Side;
	uInt8				m_Disable; // 	1表示禁止交易，0表示可以交易，

	hdsm_emc_trading_time_disable_account_instrument()
	{
		memset(this, 0, sizeof(*this));
		m_header.m_Header.m_MsgType = hdsm_types::HDSM_HELPDESK_DISABLE_INSTRUMENT_TRADE;
		m_header.m_Header.m_MsgLen = sizeof(*this);
	}
};
/// HDC 查询寄存器状态请求
struct hdsm_register_status_req
{
	hds_common_header m_header;   ///< HDS公共协议头 MsgType = 25
	char   m_registrt_name[255];
	hdsm_register_status_req()
	{
		memset(this, 0, sizeof(*this));
		m_header.m_Header.m_MsgType = hdsm_types::HDSM_REGISTER_STATUS_REQ;
		m_header.m_Header.m_MsgLen = sizeof(*this);
	}
};

/// HDC 查询寄存器状态响应
struct hdsm_register_status_resp
{
	hds_common_header m_header;   ///< HDS公共协议头 MsgType = 26
	T_server_id	m_ot_id;
	char   m_registrt_name[255];
	unsigned int reg_value;
	hdsm_register_status_resp()
	{
		memset(this, 0, sizeof(*this));
		m_header.m_Header.m_MsgType = hdsm_types::HDSM_REGISTER_STATUS_RESP;
		m_header.m_Header.m_MsgLen = sizeof(*this);
	}
};

/// HDC 断开指定链接
struct hdsm_kick_trader_session_req
{
	hds_common_header m_header;
	fix_str<33>   m_otStr;
	uInt32  m_sessionType;    // 1：查询会话  2：交易会话
	uInt32  m_sessionID;
	hdsm_kick_trader_session_req()
	{
		memset(this, 0, sizeof(*this));
		m_header.m_Header.m_MsgType = hdsm_types::HDSM_EMC_KILL_TRADE_SESSION_REQ;
		m_header.m_Header.m_MsgLen = sizeof(*this);
	}
};

/// HDC 查询黑名单IP列表
struct hdsm_emc_qry_blackip_list_req
{
	hds_common_header m_header;
	fix_str<33>   m_otStr;
	hdsm_emc_qry_blackip_list_req()
	{
		memset(this, 0, sizeof(*this));
		m_header.m_Header.m_MsgType = hdsm_types::HDSM_EMC_QRY_BLACKIP_LIST_REQ;
		m_header.m_Header.m_MsgLen = sizeof(*this);
	}
};

/// HDC 查询黑名单IP列表返回消息
struct hdsm_emc_qry_blackip_list_resp
{
	hds_common_header m_header;
	char    m_otStr[33];
	uInt32	m_ip_count;
	uInt32  m_black_ip[32];
	hdsm_emc_qry_blackip_list_resp()
	{
		memset(this, 0, sizeof(*this));
		m_header.m_Header.m_MsgType = hdsm_types::HDSM_EMC_QRY_BLACKIP_LIST_RESP;
		m_header.m_Header.m_MsgLen = sizeof(*this);
	}
};

/// HDC 设置黑名单IP列表
struct hdsm_emc_set_blackip_list_req
{
	hds_common_header m_header;
	char    m_otStr[33];
	uInt32	m_ip_count;
	uInt32  m_black_ip[32];
	hdsm_emc_set_blackip_list_req()
	{
		memset(this, 0, sizeof(*this));
		m_header.m_Header.m_MsgType = hdsm_types::HDSM_EMC_SET_BLACKIP_LIST_REQ;
		m_header.m_Header.m_MsgLen = sizeof(*this);
	}
};

/// HDC 调整仓位
struct hdsm_new_emc_manual_pos
{
	hds_common_header m_header;
	T_OT_CLUSTER_ID		ot_cluster_id;
	T_SECURITY_CODE		m_underlying_symbol;
	T_FUND_ACCOUNT		m_fund_account;
	T_CUST_ID	m_client_id;
	int					m_pos_change;
	hdsm_new_emc_manual_pos()
	{
		memset(this, 0, sizeof(*this));
		m_header.m_Header.m_MsgType = hdsm_types::HDSM_NEW_EMC_MANUAL_POS;
		m_header.m_Header.m_MsgLen = sizeof(*this);
	}
};

/// TODO zjw 20180517 问了下老白, ot->hds hds->synctrade 消息以后可能不同, 先不套用消息体了

/// 向HDS请求查询账户的可用标的券数量[10035]
struct hdsm_hds_qry_underlying_symbol_qty_req
{
	hds_common_header		m_header;
	MODULE_TYPE_INT_DEF		m_module_type;
	T_MODULE_ID				m_module_id;
	uInt32					m_user_id;
	T_CUST_ID		m_client_id;
	T_FUND_ACCOUNT			m_fund_account;
	T_EXCHANGE_ACCOUNT		m_exchange_account;
	T_EXCHANGE				m_exchange_id;
	T_SECURITY_CODE			m_security_code;
	uInt32					m_req_id;

	hdsm_hds_qry_underlying_symbol_qty_req()
	{
		memset(this, 0, sizeof(*this));
		m_header.m_Header.m_MsgType = hdsm_types::HDSM_HDS_QRY_UNDERLYING_SYMBOL_QTY_REQ;
		m_header.m_Header.m_MsgLen = sizeof(*this);
	}
};

/// 向HDS请求查询账户的可用标的券数量 回复[10036]
struct hdsm_hds_qry_underlying_symbol_qty_resp
{
	hds_common_header		m_header;
	MODULE_TYPE_INT_DEF		m_module_type;
	T_MODULE_ID				m_module_id;
	uInt32					m_user_id;
	T_CUST_ID		m_client_id;
	T_FUND_ACCOUNT			m_fund_account;
	T_EXCHANGE_ACCOUNT		m_exchange_account;
	uInt32					m_req_id;
	T_EXCHANGE				m_exchange_id;
	T_SECURITY_CODE			m_security_code;
	uInt32					m_quantity;
	uInt32					m_result;
	T_MSG_TEXT				m_msg_text;

	hdsm_hds_qry_underlying_symbol_qty_resp()
	{
		memset(this, 0, sizeof(*this));
		m_header.m_Header.m_MsgType = hdsm_types::HDSM_HDS_QRY_UNDERLYING_SYMBOL_QTY_RESP;
		m_header.m_Header.m_MsgLen = sizeof(*this);
	}
};

/// 向HDS请求锁定、解锁可用标的券[10037]
struct hdsm_hds_frz_underlying_symbol_qry_req
{
	hds_common_header		m_header;
	MODULE_TYPE_INT_DEF		m_module_type;
	T_MODULE_ID				m_module_id;
	uInt32					m_user_id;
	T_CUST_ID		m_client_id;
	T_FUND_ACCOUNT			m_fund_account;
	T_EXCHANGE_ACCOUNT		m_exchange_account;
	uInt32					m_req_id;
	T_EXCHANGE				m_exchange_id;
	T_SECURITY_CODE			m_security_code;
	T_FROZEN_FLAG			m_frz_flag;
	uInt32					m_quantity;
	T_MSG_TEXT				m_remark;

	hdsm_hds_frz_underlying_symbol_qry_req()
	{
		memset(this, 0, sizeof(*this));
		m_header.m_Header.m_MsgType = hdsm_types::HDSM_HDS_FRZ_UNDERLYING_SYMBOL_QRY_REQ;
		m_header.m_Header.m_MsgLen = sizeof(*this);
	}
};

/// 向HDS请求锁定、解锁可用标的券的回复[10038]
struct hdsm_hds_frz_underlying_symbol_qry_resp
{
	hds_common_header		m_header;
	MODULE_TYPE_INT_DEF		m_module_type;
	T_MODULE_ID				m_module_id;
	uInt32					m_user_id;
	T_CUST_ID				m_client_id;
	T_FUND_ACCOUNT			m_fund_account;
	T_EXCHANGE_ACCOUNT		m_exchange_account;
	uInt32					m_req_id;
	T_EXCHANGE				m_exchange_id;
	T_SECURITY_CODE			m_security_code;
	T_FROZEN_FLAG			m_frz_flag;
	uInt32					m_quantity;
	uInt32					m_result;
	T_MSG_TEXT				m_msg_text;

	hdsm_hds_frz_underlying_symbol_qry_resp()
	{
		memset(this, 0, sizeof(*this));
		m_header.m_Header.m_MsgType = hdsm_types::HDSM_HDS_FRZ_UNDERLYING_SYMBOL_QRY_RESP;
		m_header.m_Header.m_MsgLen = sizeof(*this);
	}
};

/// 向HDS请求主席资金划拔的请求[10039]
struct hdsm_hds_inout_fund_account_amount_rep
{
	hds_common_header		m_header;
	MODULE_TYPE_INT_DEF		m_module_type;
	T_MODULE_ID				m_module_id;
	uInt32					m_user_id;
	T_CUST_ID		m_client_id;
	T_FUND_ACCOUNT			m_fund_account;
	uInt32					m_req_id;
	T_FROZEN_FLAG			m_frz_flag;
	T_PRICE_4				m_amount;
	T_MSG_TEXT				m_remark;

	hdsm_hds_inout_fund_account_amount_rep()
	{
		memset(this, 0, sizeof(*this));
		m_header.m_Header.m_MsgType = hdsm_types::HDSM_HDS_INOUT_FUND_ACCOUNT_AMOUNT_REP;
		m_header.m_Header.m_MsgLen = sizeof(*this);
	}
};

/// 向hds请求主席资金划拔拓回复[10040]
struct hdsm_hds_inout_fund_account_amount_resp
{
	hds_common_header		m_header;
	MODULE_TYPE_INT_DEF		m_module_type;
	T_MODULE_ID				m_module_id;
	uInt32					m_user_id;
	T_CUST_ID				m_client_id;
	T_FUND_ACCOUNT			m_fund_account;
	uInt32					m_req_id;
	T_FROZEN_FLAG			m_frz_flag;
	T_PRICE_4				m_amount;
	uInt32					m_result;
	T_MSG_TEXT				m_msg_text;

	hdsm_hds_inout_fund_account_amount_resp()
	{
		memset(this, 0, sizeof(*this));
		m_header.m_Header.m_MsgType = hdsm_types::HDSM_HDS_INOUT_FUND_ACCOUNT_AMOUNT_RESP;
		m_header.m_Header.m_MsgLen = sizeof(*this);
	}
};

/// 向SyncTrade请求查询账户的可用标的券数量[10041]
struct hdsm_sync_qry_underlying_symbol_qty_req
{
	hds_common_header		m_header;
	MODULE_TYPE_INT_DEF		m_module_type;
	T_MODULE_ID				m_module_id;
	uInt32					m_user_id;
	T_CUST_ID		m_client_id;
	T_FUND_ACCOUNT			m_fund_account;
	T_EXCHANGE_ACCOUNT		m_exchange_account;
	T_EXCHANGE				m_exchange_id;
	T_SECURITY_CODE			m_security_code;
	uInt32					m_req_id;

	hdsm_sync_qry_underlying_symbol_qty_req()
	{
		memset(this, 0, sizeof(*this));
		m_header.m_Header.m_MsgType = hdsm_types::HDSM_SYNC_QRY_UNDERLYING_SYMBOL_QTY_REQ;
		m_header.m_Header.m_MsgLen = sizeof(*this);
	}
};

/// 向SyncTrade请求查询账户的可用标的券数量 回复[10042]
struct hdsm_sync_qry_underlying_symbol_qty_resp
{
	hds_common_header		m_header;
	MODULE_TYPE_INT_DEF		m_module_type;
	T_MODULE_ID				m_module_id;
	uInt32					m_user_id;
	T_CUST_ID		m_client_id;
	T_FUND_ACCOUNT			m_fund_account;
	T_EXCHANGE_ACCOUNT		m_exchange_account;
	uInt32					m_req_id;
	T_EXCHANGE				m_exchange_id;
	T_SECURITY_CODE			m_security_code;
	uInt32					m_quantity;
	uInt32					m_result;
	T_MSG_TEXT				m_msg_text;

	hdsm_sync_qry_underlying_symbol_qty_resp()
	{
		memset(this, 0, sizeof(*this));
		m_header.m_Header.m_MsgType = hdsm_types::HDSM_SYNC_QRY_UNDERLYING_SYMBOL_QTY_RESP;
		m_header.m_Header.m_MsgLen = sizeof(*this);
	}
};

/// 向SyncTrade请求锁定、解锁可用标的券 [10043]
struct hdsm_sync_frz_underlying_symbol_qry_req
{
	hds_common_header		m_header;
	MODULE_TYPE_INT_DEF		m_module_type;
	T_MODULE_ID				m_module_id;
	uInt32					m_user_id;
	T_CUST_ID		m_client_id;
	T_FUND_ACCOUNT			m_fund_account;
	T_EXCHANGE_ACCOUNT		m_exchange_account;
	uInt32					m_req_id;
	T_EXCHANGE				m_exchange_id;
	T_SECURITY_CODE			m_security_code;
	T_FROZEN_FLAG			m_frz_flag;
	uInt32					m_quantity;
	T_MSG_TEXT				m_remark;

	hdsm_sync_frz_underlying_symbol_qry_req()
	{
		memset(this, 0, sizeof(*this));
		m_header.m_Header.m_MsgType = hdsm_types::HDSM_SYNC_FRZ_UNDERLYING_SYMBOL_QRY_REQ;
		m_header.m_Header.m_MsgLen = sizeof(*this);
	}
};

/// 向SyncTrade 请求锁定、解锁可用标的券的回复 [10044]
struct hdsm_sync_frz_underlying_symbol_qry_resp
{
	hds_common_header		m_header;
	MODULE_TYPE_INT_DEF		m_module_type;
	T_MODULE_ID				m_module_id;
	uInt32					m_user_id;
	T_CUST_ID		m_client_id;
	T_FUND_ACCOUNT			m_fund_account;
	T_EXCHANGE_ACCOUNT		m_exchange_account;
	uInt32					m_req_id;
	T_EXCHANGE				m_exchange_id;
	T_SECURITY_CODE			m_security_code;
	T_FROZEN_FLAG			m_frz_flag;
	uInt32					m_quantity;
	uInt32					m_result;
	T_MSG_TEXT				m_msg_text;

	hdsm_sync_frz_underlying_symbol_qry_resp()
	{
		memset(this, 0, sizeof(*this));
		m_header.m_Header.m_MsgType = hdsm_types::HDSM_SYNC_FRZ_UNDERLYING_SYMBOL_QRY_RESP;
		m_header.m_Header.m_MsgLen = sizeof(*this);
	}
};

/// 向SyncTrade请求主席资金划拔的请求[10045]
struct hdsm_sync_inout_fund_account_amount_rep
{
	hds_common_header		m_header;
	MODULE_TYPE_INT_DEF		m_module_type;
	T_MODULE_ID				m_module_id;
	uInt32					m_user_id;
	T_CUST_ID		m_client_id;
	T_FUND_ACCOUNT			m_fund_account;
	uInt32					m_req_id;
	T_FROZEN_FLAG			m_frz_flag;
	T_PRICE_4				m_amount;
	T_MSG_TEXT				m_remark;

	hdsm_sync_inout_fund_account_amount_rep()
	{
		memset(this, 0, sizeof(*this));
		m_header.m_Header.m_MsgType = hdsm_types::HDSM_SYNC_INOUT_FUND_ACCOUNT_AMOUNT_REP;
		m_header.m_Header.m_MsgLen = sizeof(*this);
	}
};

/// 向SyncTrade请求主席资金划拔拓回复[10046]
struct hdsm_sync_inout_fund_account_amount_resp
{
	hds_common_header		m_header;
	MODULE_TYPE_INT_DEF		m_module_type;
	T_MODULE_ID				m_module_id;
	uInt32					m_user_id;
	T_CUST_ID		m_client_id;
	T_FUND_ACCOUNT			m_fund_account;
	uInt32					m_req_id;
	T_FROZEN_FLAG			m_frz_flag;
	T_PRICE_4				m_amount;
	uInt32					m_result;
	T_MSG_TEXT				m_msg_text;

	hdsm_sync_inout_fund_account_amount_resp()
	{
		memset(this, 0, sizeof(*this));
		m_header.m_Header.m_MsgType = hdsm_types::HDSM_SYNC_INOUT_FUND_ACCOUNT_AMOUNT_RESP;
		m_header.m_Header.m_MsgLen = sizeof(*this);
	}
};

struct hw_mi_new_order_req
{
	hw_mi_new_order_req()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = hwmi_types::HWMI_CONFIG_TYPES_NEW_ORDER_REQ;
		m_Header.m_MsgLen = sizeof(*this);
	}

	msg_standard_hdr		m_Header;
	uInt32					Reqnum; ///<	4	uInt32	送单子的数据库编号
	uInt64					OrderID; ///<	8	uInt64	REM系统单cluster唯一编号。 Id37
	T_EXCHANGE_ORDER_TOKEN	ExchangeOrderToken; ///<	16	C16	tag8011，面向交易所的OrderToken，和撤单请求一起编号
	uInt8					session_id; ///<	1	Uint1	EzSTEP报盘数据库内部编码ID，硬件内部映射成ServerName；目前支持8个报盘库
	fix_str<3>				Reserved; ///<	Bin3	保留 
};

struct hw_mi_cxl_order_req
{
	hw_mi_cxl_order_req()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = hwmi_types::HWMI_CONFIG_TYPES_CXL_ORDER_REQ;
		m_Header.m_MsgLen = sizeof(*this);
	}

	msg_standard_hdr		m_Header; ///<		8		MsgType=22006
	uInt32					Reqnum; ///<	4	uInt32	送单子的数据库编号
	uInt64					OrigOrderID; ///<	8	uInt64	盛立系统产生的单子号，和盛立交流时可用该号。Id37
	T_EXCHANGE_ORDER_ID		ExchangeOrderID; ///<	20	C20	Tag8037，要撤单的原始订单交易所ID
	T_EXCHANGE_ORDER_TOKEN	ExchangeOrderToken; ///<	16	C16	tag8011，面向交易所的OrderToken，撤单请求的编号。
	uInt8					session_id; ///<	1	Uint1	EzSTEP报盘数据库内部编码ID，硬件内部映射成ServerName；目前支持8个报盘库
	uInt8					Reserved; ///<	1	Bin1	保留 
};

struct hw_mi_partitions_info
{
	hw_mi_partitions_info()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = hwmi_types::HWMI_CONFIG_TYPES_PARTITIONS_INFO;
		m_Header.m_MsgLen = 16 + m_NoPartitions * 4;
	}

	msg_standard_hdr		m_Header;
	T_EXCHANGE              m_ExchId;
	uInt8              m_ServerId;

	uInt8              m_PlatformId;
	uInt8              m_Reserved1;
	uInt32			m_NoPartitions;
	uInt32          m_PartitionNo[256];

};

// 8.2.2	抄送全市场回单消息（21001）
struct hw_mi_raw_exchange_data
{
	hw_mi_raw_exchange_data()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = hwmi_types::HWMI_CONFIG_TYPES_RAW_EXCHANGE_DATA;
		m_Header.m_MsgLen = sizeof(*this); // 该长度是变化的长度， 硬件上传的时候，要包括这个长度
	}

	msg_standard_hdr		m_Header;
	T_EXCHANGE				m_ExchID;
	uInt8					m_sessionID;
	uInt8					m_Reserved[6]; ///<	1	Bin1	保留 
	uInt8					m_Data[0];	// 硬件上传给软件的数据
};

// 8.2.3	反馈市场平台reportindex（21002）
struct hw_mi_partitions_report_index
{
	hw_mi_partitions_report_index()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = hwmi_types::HWMI_CONFIG_TYPES_REPORT_INDEX_INFO;
		m_Header.m_MsgLen = sizeof(*this);
	}

	msg_standard_hdr		m_Header;
	T_EXCHANGE              m_ExchId;
	uInt8              m_ServerId;

	uInt8              m_PlatformId;
	uInt8              m_Reserved1;
	uInt32			m_PartitionNo;
	uInt64          m_ReportIndex;

};

struct hdsm_hds_change_position_share
{
	hdsm_hds_change_position_share()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = hdsm_types::HDSM_CHANGE_POSITION_SHARE;
		m_Header.m_MsgLen = sizeof(*this);
	}
	msg_standard_hdr		m_Header; ///<		8		MsgType=22006
	T_PRICE_4				m_price;
	hwcm_adjust_underlying_pos_config_body	body;
};


//#END，HDS消息结构体
//#END，股票版结构体定义
#pragma pack(pop)
