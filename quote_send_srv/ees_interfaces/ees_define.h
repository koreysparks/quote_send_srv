#pragma once
//#include "../kiwi_comm_api/cherry_comm_struct.h"
//#include "../kiwi_trading_api/cherry_trading_data_struct.h"
#ifdef _WIN32
#include "../../common_libs_pub/include/windows/shengli_tool/shengli_define.h"
#include "../../common_libs_pub/include/windows/shengli_tool/cross_platform_api.h"
#include "../../common_libs_pub/include/windows/shengli_tool/tool_function.h"
#include "../../common_libs_pub/include/windows/shengli_tool/date_time.h"
#else

#include "../../common_libs_pub/include/linux/shengli_tool/shengli_define.h"
#include "../../common_libs_pub/include/linux/shengli_tool/cross_platform_api.h"
#include "../../common_libs_pub/include/linux/shengli_tool/tool_function.h"
#include <time.h>
#endif


#include "fix_str.h"

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <memory>
using std::vector;

using namespace SHENGLI::TOOLS;

#define EES_DB_ENTRY_XML			("ees_db_entry.xml")
#define SHENGLI_REM_VERSION_STR_FOR_EXCHANGE  ("ShengLi_REM_v1.2")

#define	EES_OT_CLUSTER_LEN						15
#define EES_IP_LEN								15
#define EES_TPL_ID_LEN							45
#define EES_EQS_ID_LEN							15
#define EES_OT_ID_LEN							32
#define EES_EXCHANGE_NAME_LEN					255
#define MAX_ALLOWED_SESSION						255
#define CHERRY_TRADING_RISK_RESULT_LEN			16


#define	EES_CS_ParValue							100 

/// for HDS
#define EES_MODULE_ID_LEN           32

#define EES_HDS_LOGIN_PWD_LEN       32
#define EES_HDS_DB_ENTRY_ADDR_LEN	19
#define EES_HDS_DB_ENTRY_LEN        255

#define EES_PROD_ID_LEN				30
//费率配置，最多8种
#define REM_SEC_FEE_MAX_COUNT		8

//下列define映射将cherry中的定义转到EES中
#define REM_FUND_ACCOUNT_ID_LEN			16
#define REM_SECURITY_CODE_LEN			8

#define EES_CHAR_EXCHANGE_SHH ("SHH")
#define EES_CHAR_EXCHANGE_SHZ ("SHZ")

#define EES_CHAR_EXCHANGE_SHH_VERSION_ONE "5"
#define EES_CHAR_EXCHANGE_SHZ_VERSION_ONE "6"


enum ees_capacity
{
	//CAPACITY_AGENCY = CHERRY_ORDER_CAPACITY_AGENCY,
	//CAPACITY_PRINCIPAL = CHERRY_ORDER_CAPACITY_PRINCIPAL,
	//CAPACITY_HEDGING = CHERRY_ORDER_CAPACITY_HEDGING
	//2015-03-09, 该字段改为投机套利标志
	CAPACITY_HEDGE_FLAG_NONE = 0,//发送0，将视为投机
	CAPACITY_HEDGE_FLAG_ARBITRAGE = 1,//套利
	CAPACITY_HEDGE_FLAG_SPECULATION = 2,//投机，老版本EES api恒送2，所以映射为默认值投机
	CAPACITY_HEDGE_FLAG_HEDGE = 3, //套保
	CAPACITY_HEDGE_FLAG_END		//投机套利标志结束，用于投机套利标志数量，建立静态数组用
};

enum risk_rule_apply_to
{
	APPLY_TO_ACCOUNT = 'A',//账户级别
	APPLY_TO_SYMBOL	= 'S',//symbol级别
	APPLY_TO_TIME = 'T',//账户级别
	APPLY_TO_BIG = 'B',//账户级别
};

enum MODULE_TYPE_INT_DEF
{

	MTNID_INVALID = 0,
	MTNID_LGS = 1,			//Log Server
	MTNID_BK = 2,			//BK Server
	MTNID_OT = 3 ,			//OT 
	MTNID_HDS = 4,			//help desk server
	MTNID_RS = 5,           // EES risk static
	MTNID_EQS = 6 ,			// eqs risk_ static 
	MTNID_SYNC_TRADE = 7,	// 与主席同步
	MTNID_MS_SQL = 8,	// 报盘库状态
	MTNID_TRADING_NODE = 9 ,	// 报盘库状态
	MTNID_MYSQL = 10 , // 数据库结点
	MTNID_COMPUTER= 11, // 计算机状态

	//add new module type above this value
	MTNID_TOTAL_NUMBER

};

enum ees_diag_mode
{
	EES_DIAG_MODE_NONE,			///正常运行模式
	EES_DIAG_MODE_CRAZY_ORDERS,	///从OT内部大量下单，返回到客户端的消息不转发只计数，其他market端，抄送端正常工作，二进制日志不记录
	EES_DIAG_MODE_MAX_ORDERS,	///从OT内部大量下单，所有从硬件返回的消息不抄送不转发，日志不记录，目的是测试硬件PCIE传输的问题
	EES_DIAG_MODE_CRAZY_CANCEL, ///需将市场端设置为撤单永远拒绝，每下一个单，对其撤单N次，用以将action id涨到4G
	EES_DIAG_MODE_TITAN_ORDER,			///需将市场端设为每次一手成交所有量，测试成交数量上限
	EES_DIAG_MODE_COUNT			///枚举数量，新增诊断模式放在这行之前
};

enum ees_operator_type
{
	EES_OP_TYPE_ADMIN = 'A',
	EES_OP_TYPE_BUSI_OP = 'B',
};

enum ees_hw_error_module_id
{
	EES_HWERR_MOD_ID_RESERVED = 0,
	EES_HWERR_MOD_ID_CONFIG,
	EES_HWERR_MOD_ID_GRAMMAR_CHECK,
	EES_HWERR_MOD_ID_REWIND,
	EES_HWERR_MOD_ID_OM,
	EES_HWERR_MOD_ID_MARKET_FEEDBACK,
	EES_HWERR_MOD_ID_RISK,
};

enum ees_hw_market_feedback_error_type//EES_HWERR_MOD_ID_MARKET_FEEDBACK时, error type
{
	EES_HWERR_MFB_ERR_TYPE_MSG_TYPE_ERROR = 1,
	EES_HWERR_MFB_ERR_TYPE_BEATS = 2,//BEATS出错
	EES_HWERR_MFB_ERR_TYPE_INTERNAL_ORDER_ID_NOT_FOUND = 3,//找不到37
	EES_HWERR_MFB_ERR_TYPE_NOT_IN_ORDER = 4,//回单顺序错误，类似先成交再accept
	EES_HWERR_MFB_ERR_TYPE_INVALID = 5, //市场回单不合法, 判断挂单量够不够成交或撤销
	EES_HWERR_MFB_ERR_TYPE_PRICE_ZERO = 6, //成交回报时price域为0
	EES_HWERR_MFB_ERR_TYPE_EXEC_ID_DUP = 7, //成交8017号重复
	EES_HWERR_MFB_ERR_TYPE_EXEC_ID_OVERFLOW = 8, //成交8017区域溢出
};

enum margin_rate_source//账户的合约保证金率配置是来自那种配置
{
	MARGIN_RATE_SOURCE_PROD_DEF = 0,//品种默认值
	MARGIN_RATE_SOURCE_ACCOUNT_PROD,//账户的品种配置
	MARGIN_RATE_NEAR_EXERCISE_CNF, // 临近行权合约配置
};

enum fee_rate_source//账户的合约手续费率配置是来自那种配置
{
	FEE_RATE_SOURCE_GLOBAL_DEF = 0,//品种默认值	
	FEE_RATE_SOURCE_ACCOUNT_CONFIG
};

//#define  (double)(x)	( (double)((( long long int )(x)) * 1.0 / 10000) )


// #START，typedef股票版类型定义
typedef char					Int8;
typedef unsigned char			uInt8;
typedef	short					Int16;
typedef unsigned short			uInt16;
typedef int						Int32;
typedef unsigned int			uInt32;
typedef long long int			Int64;
typedef unsigned long long		uInt64;

typedef fix_str<EES_OT_CLUSTER_LEN + 1>			T_OT_CLUSTER_ID;			///ot集群号,客户号一定要绑定一个ot cluster id
typedef fix_str<EES_OT_CLUSTER_LEN + 1>			T_OT_CLUSTER_ID;			///ot集群号,客户号一定要绑定一个ot cluster id
typedef fix_str<EES_OT_ID_LEN + 1>				T_ot_id;					///
typedef fix_str<17>								T_CUST_ID;					///证券客户号
typedef fix_str<64>								T_CUST_NAME;				///证券客户号
typedef fix_str<REM_FUND_ACCOUNT_ID_LEN + 1>	T_FUND_ACCOUNT;				///资金账号
typedef fix_str<24>								T_TRADE_ACCOUNT;			///股东账号
typedef fix_str<64>								T_FUND_ACCOUNT_NAME;		///资金账号名称
typedef fix_str<REM_SECURITY_CODE_LEN + 1>		T_SECURITY_CODE;			///证券代码，股票代码，期权编码
typedef fix_str<16>								T_SECURITY_NAME;			///证券代码，股票代码，期权编码
typedef fix_str<17>								T_ExchCombSeqID;		/// 组合持仓交易所流水号
typedef fix_str<20>								T_EXCHANGE_ORDER_ID;		///交易所单号
typedef fix_str<7>								T_CONTRACT_ACCOUNT_CODE;	///期权中的合约账户代码
typedef fix_str<21>								T_OPT_CONTRACT_ID;			///期权合约代码
typedef fix_str<32>								T_OPT_NAME;					///期权合约代码
typedef fix_str<88>								T_REASON_TEXT;				///原因文字，中文必须是UTF8编码
typedef fix_str<20>								T_EXCHANGE_EXEC_ID;			///交易所成交号
typedef fix_str<16>								T_EXCHANGE_ORDER_TOKEN;		///针对交易所的客户端单号
typedef fix_str<16>								T_EXCHANGE_ORDER_REFF;		///针对交易所的客户端单号
typedef fix_str<16>								T_EXCHANGE_ACCOUNT;			///交易所账号
typedef fix_str<16>								T_EXCHANGE_SUB_ACCOUNT;		///交易子账号
typedef fix_str<33>								T_LOGON_ID;					///客户端登录名
typedef fix_str<33>								T_PASSWORD_MD5;				///MD5加密密码
typedef fix_str<18>								T_MAC_ADDR;					///MAC地址，格式类似08:00:27:EC:D9:F4, 分隔符也可以用'-'
typedef fix_str<32>								T_CLIENT_PROD_INFO;			///客户端程序标识符
typedef fix_str<16>								T_OP_LOGON_ID;				///操作员登录号
typedef fix_str<9>								T_BRANCH_ID;				///客户号所属的营业部代码
typedef fix_str<9>								T_EX_BRANCH_ID;				///客户号所属的营业部代码
typedef fix_str<6>								T_TRADE_PBU;				///交易单元
typedef fix_str<48>								T_BRANCH_NAME;				///客户号所属的营业部代码
typedef fix_str<8>								T_SEAT_ID;					///席位号
typedef	fix_str<11>								T_DATE_STR;					///用YYYYMMDD代表的年月日
typedef fix_str<16>								T_IP_ADDR;					///IP地址
typedef fix_str<256>							T_STATION ;					///站点地址
typedef fix_str<33>								T_SESSION_ID ;				///会话ID
typedef fix_str<33>								T_MODULE_ID;				///模块实例ID
typedef fix_str<256>							T_MSG_TEXT;					///错误描述

typedef fix_str<256>							T_node_id;					/// 结点名称
typedef fix_str<256>							T_node_name;

typedef fix_str<256>							T_server_id;				/// 服务名称
typedef fix_str<256>							T_server_name;
typedef fix_str<256>							T_version;					/// 版本号 

typedef fix_str<33>								T_APP_ID;					//	看穿式里面， APP ID 
typedef fix_str<65>								T_APP_AUTH_CODE;			//  看空式里面，APP 的验证码
typedef fix_str<9>								T_COMB_STRATEGY_ID;			///< 组合策略




typedef long									T_exec_id ;
  
typedef fix_str<17>								T_db_name;
typedef uInt8							T_db_name_len;

typedef fix_str<17>								T_db_user;
typedef uInt8							T_db_user_len;

typedef fix_str<17>								T_db_password;
typedef uInt8							T_db_password_len;


typedef uInt32									T_ip;
typedef uInt16									T_port;


typedef fix_str<8>								T_pbu ;
typedef uInt32									T_user_id;
typedef uInt32									T_socket_id;


typedef fix_str<16>								T_date;
typedef fix_str<8>								T_time;
typedef fix_str<32>								T_datetime;

typedef int										T_trade_account_type;
typedef int										T_cust_type;
typedef int										T_cust_stat;

typedef int										T_cust_acct_cls;
typedef int										T_cust_acct_stat;
typedef uInt8									T_plat_form;


///#END，股票版类型定义

struct order_belonging_info
{
	T_CUST_ID m_cust_id;
	T_FUND_ACCOUNT	 m_fund_account_id;
};

#pragma pack(push, 1)

///#START，股票版枚举定义
enum rem_order_status_bit
{
	ROSB_CLOSE_BIT = 0x01,			//bit0 - 是否已经关闭
	ROSB_RESERVED_BIT1 = 0x02,		//bit1 - 保留
	ROSB_RESERVED_BIT2 = 0x04,		//bit2 - 保留
	ROSB_RESERVED_BIT3 = 0x08,		//bit3 - 保留
	ROSB_CXLED_BIT = 0x10,			//bit4 - 是否已撤单
	ROSB_FILLED_BIT = 0x20,			//bit5 - 是否有过任意数量的成交
	ROSB_EXCH_ACCEPT_BIT = 0x40,	//bit6 - 交易所是否已经接受
	ROSB_EXCH_REJECT_BIT = 0x80,	//bit7 – 交易所拒绝标志
	
};

enum rem_order_grammar_result
{
	ORDER_GRAMMAR_GOOD							= 0x00000000,
	ORDER_GRAMMAR_FAILED_ANY_RESULT				= 0x00000001,
	ORDER_GRAMMAR_FAILED_CL_ORD_TOKEN			= 0x00000002,
	ORDER_GRAMMAR_FAILED_EXCHANGE_ID			= 0x00000004,
	ORDER_GRAMMAR_FAILED_TIF					= 0x00000008,
	ORDER_GRAMMAR_FAILED_LIMIT_PRICE			= 0x00000010,
	ORDER_GRAMMAR_FAILED_SYMBOL					= 0x00000020,
	ORDER_GRAMMAR_FAILED_ORDER_QTY				= 0x00000040,
	ORDER_GRAMMAR_FAILED_INVALID_ACCOUNT		= 0x00000080,
	ORDER_GRAMMAR_FAILED_SIDE_COMBINE			= 0x00000100,
	ORDER_GRAMMAR_FAILED_PREVILEGE				= 0x00000200,			
	ORDER_GRAMMAR_FAILED_SERVER_CAPACITY		= 0x00000400,
	ORDER_GRAMMAR_FAILED_INVALID_USERID			= 0x00000800,
	ORDER_GRAMMAR_FAILED_MARKET_ORDER_COMBINE	= 0x00001000,
	ORDER_GRAMMAR_FAILED_EXCHANGE_SESSION		= 0x00002000,
	ORDER_GRAMMAR_FAILED_EXERICISE_DATE			= 0x00004000,
	ORDER_GRAMMAR_FAILED_ORDER_TOKEN_RANGE		= 0x00008000,
	ORDER_GRAMMAR_FAILED_ST_PERM				= 0x00010000, // 限制买入风险警示板股票
	ORDER_GRAMMAR_FAILED_BOND_PERM				= 0x00020000, // 债券交易权限检查失败
	ORDER_GRAMMAR_FAILED_BUSINESS_ACTION_PERM	= 0x00040000, // 业务行为权限检查失败
	ORDER_GRAMMAR_FAILED_VARIETY_PERM			= 0x00080000, // 交易品种权限检查失败

};

enum rem_cxl_grammar_reason
{
	CXL_GRAMMAR_GOOD								= 0x00000000,
	CXL_GRAMMAR_FAILED_ANY_RESULT					= 0x00000001,
	CXL_GRAMMAR_FAILED_USER_ID_INVALID				= 0x00000002,
	CXL_GRAMMAR_FAILED_CL_ORD_TOKEN					= 0x00000004,
	CXL_GRAMMAR_FAILED_ORIG_ORDER_NOT_FOUND			= 0x00000008,
	CXL_GRAMMAR_FAILED_SERVER_CAPACITY				= 0x00000010,
	CXL_GRAMMAR_FAILED_ORDER_FULL_FILLED			= 0x00000020,
	CXL_GRAMMAR_FAILED_ORDER_CXLED					= 0x00000040,
	CXL_GRAMMAR_FAILED_ORDER_REJECTED				= 0x00000080,
	CXL_GRAMMAR_FAILED_EXCHANGE_SESSION				= 0x00000100,
	CXL_GRAMMAR_FAILED_PASSIVE_ORDER				= 0x00000200,
	CXL_GRAMMAR_FAILED_ORDER_NOT_SUPPORT_CXL		= 0x00000400,
};

template < typename T>
struct T_ENUM
{
	uInt8 m_value ; 

	T_ENUM()
	{

	}

	T_ENUM(const int val )
	{
		m_value = (uInt8)val ;
	}

	T_ENUM(const T& val )
	{
		m_value = val ;
	}

	T_ENUM& operator = (const T& val)
	{
		m_value = val ;
		return *this;
	}

	bool operator == ( const T& val )
	{
		return m_value == val ;
	}

	bool operator != (const T& val )
	{
		return m_value != val;
	}

	bool operator > (const T& val )
	{
		return m_value > val;
	}

	bool operator >= (const T& val )
	{
		return m_value >= val;
	}

	bool operator < (const T& val )
	{
		return m_value < val;
	}

	bool operator <= (const T& val )
	{
		return m_value <= val;
	}

	T_ENUM& operator = (int nVal)
	{
		m_value = nVal ;
		return *this ;
	}

	operator int()
	{
		return (int)m_value;
	}

	
};

namespace rem_price_type
{
	enum _
	{
		PX_TYPE_MARKET = 1,	///市价
		PX_TYPE_LIMIT = 2,	///限价
		PX_TYPE_INSIDE = 3,	///本方最优
	};
}
typedef T_ENUM<rem_price_type::_> T_PRICE_TYPE;

namespace rem_tif
{
	enum _
	{
		TIF_DAY_ORDER = 0, ///日内单
		TIF_IOC_ORDER = 1, ///IOC
		TIF_COMPLEX_ORDER = 10, ///综合交易平台
	};
}
typedef T_ENUM<rem_tif::_> T_TIF;


namespace rem_frz_flag
{
	enum _
	{
		FROZEN		= '0', // 划入     冻结
		UNFROZEN	= '1'  // 划出     解封
	};
}
typedef T_ENUM<rem_frz_flag::_> T_FROZEN_FLAG;


namespace rem_pos_day_flag
{
	enum _
	{
		pos_day_flag_unknow = 0, // 未知
		pos_day_flag_today = 1, // 今仓
		pos_day_flag_ovn = 2, // 昨仓
	};
}
typedef T_ENUM<rem_pos_day_flag::_>	T_POS_DAY_FLAG; 

namespace rem_comb_strategy_type
{
	enum _
	{
		comb_strategy_type_cnsjc = 1,///< 	CNSJC	认购牛市价差策略
		comb_strategy_type_pxsjc = 2,///< 	PXSJC	认沽熊市价差策略
		comb_strategy_type_pnsjc = 3,///< 	PNSJC	认沽牛市价差策略
		comb_strategy_type_cxsjc = 4,///< 	CXSJC	认购熊市价差策略
		comb_strategy_type_ks		= 5,///< 	KS	跨式空头
		comb_strategy_type_kks		= 6,///< 	KKS	宽跨式空头
	};
}
typedef T_ENUM<rem_comb_strategy_type::_>	T_COMB_STRATEGY_TYPE ;

namespace rem_trading_board
{
	enum _
	{
		rem_trading_board_cs	= 1, // 股票
		rem_trading_board_opt	= 2, // 期权
		rem_trading_board_etf	= 3, // etf申购赎回
	};
}
typedef T_ENUM<rem_trading_board::_> T_TRADING_BOARD;


namespace rem_fee_idx
{
	enum _
	{
		rem_fee_idx_comm		= 0, // 佣金
		rem_fee_idx_stamp		= 1, // 印花费
		rem_fee_idx_transfer	= 2, // 过户费
		rem_fee_idx_transcation	= 3, // 交易规费
		rem_fee_idx_settlement	= 4, // 结算费
		rem_fee_idx_handling	= 5, // 经手费
	};
}
typedef T_ENUM<rem_fee_idx::_> T_FEE_IDX;

namespace rem_cover_today_flag
{
	enum _
	{
		CANNOT_COVER_TODAY = 0,
		CAN_COVER_TODAY = 1,
	};
}
typedef T_ENUM<rem_cover_today_flag::_> T_COVER_TODAY_FLAG;

namespace rem_security_type
{
	enum _
	{
		SECU_TYPE_INDICES = 0,	//指数
		SECU_TYPE_STOCK = 1,	//股票	
		SECU_TYPE_FUNDS = 2,	//基金
		SECU_TYPE_BONDS = 3,	//债券
		SECU_TYPE_REPO	= 4,	//回购
		SECU_TYPE_WAR	= 5,	//权证		
		SECU_TYPE_OPTION = 9,	//期权
	};
}
typedef T_ENUM<rem_security_type::_> T_SECURITY_TYPE;

//股票子类型
namespace rem_cs_secu_sub_type
{
	enum _
	{
		CS_SECU_SUB_TYPE_A_STOCK = 0, //A股
		CS_SECU_SUB_TYPE_ZXB = 1,//中小板
		CS_SECU_SUB_TYPE_CYB = 2,//创业板
		CS_SECU_SUB_TYPE_B_STOCK = 3, //B股
		CS_SECU_SUB_TYPE_H_STOCK = 4, //H股
		CS_SECU_SUB_TYPE_A_KE_CHUANG	=5,		//科创版
		CS_SECU_SUB_TYPE_US_ADR = 6,	//美股ADR
		CS_SECU_SUB_TYPE_EXT = 7,		///< 扩展版
		CS_SECU_SUB_TYPE_OPS	= 8,    ///<  优先股
	};
}
typedef T_ENUM<rem_cs_secu_sub_type::_> T_CS_SECU_SUB_TYPE;


//债券子类型
namespace rem_bond_secu_sub_type
{
	enum _
	{
		BOND_SECU_SUB_TYPE_GVN = 0, //政府债券
		BOND_SECU_SUB_TYPE_ENT = 1,//企业债券
		BOND_SECU_SUB_TYPE_DFZ = 2, //地方债
		BOND_SECU_SUB_TYPE_CVT = 3, //可转换债券
		BOND_SECU_SUB_TYPE_CPF = 4, // 公司债
		BOND_SECU_SUB_TYPE_FBF = 5, // 金融债
		BOND_SECU_SUB_TYPE_CBD = 6, // 可分离，可转债
		BOND_SECU_SUB_TYPE_CCF = 7, // 可交换公司债
		BOND_SECU_SUB_TYPE_CPD = 8, // 可交换私幕债
		BOND_SECU_SUB_TYPE_PD = 9, // 私募债
		BOND_SECU_SUB_TYPE_CSD = 10, // 次级债
		BOND_SECU_SUB_TYPE_AD = 11, // 资产支持证券
		BOND_SECU_SUB_TYPE_BSD = 12, // 证券公司短期债
		BOND_SECU_SUB_TYPE_OBD = 13, // 可交换私幕债
		BOND_SECU_SUB_TYPE_DST = 14, // 可交换私幕债
		BOND_SECU_SUB_TYPE_DVP = 15, // 地方分销
	};
}
typedef T_ENUM<rem_bond_secu_sub_type::_> T_BOND_SECU_SUB_TYPE;

//基金子类型
namespace rem_mf_secu_sub_type
{
	enum _
	{
		MF_SECU_SUB_TYPE_NORMAL = 0, //一般
		MF_SECU_SUB_TYPE_CEF = 1,//封闭式基金
		MF_SECU_SUB_TYPE_LOF = 2,//LOF基金
		MF_SECU_SUB_TYPE_ETF = 3, //ETF基金
		MF_SECU_SUB_TYPE_FJ = 4,	// 分级 基金
		MF_SECU_SUB_TYPE_KFS = 5,	// 开放式基金（仅申赎）
		MF_SECU_SUB_TYPE_SSSGHB = 6,	// 实时申赎货币基金
		MF_SECU_SUB_TYPE_DSC = 7,	// 单市股票ETF
		MF_SECU_SUB_TYPE_KSC = 8,	// 跨市股票ETF
		MF_SECU_SUB_TYPE_KJ = 9,	// 跨境ETF
		MF_SECU_SUB_TYPE_SWZQ = 10,	// 实物债券ETF
		MF_SECU_SUB_TYPE_XJZQ = 11,	// 现金债券ETF
		MF_SECU_SUB_TYPE_HB = 12,	// 货币ETF
		MF_SECU_SUB_TYPE_HJ = 13,	// 黄金ETF
		MF_SECU_SUB_TYPE_SPQH = 14,	// 商品期货ETF
		MF_SECU_SUB_TYPE_GG = 15,	// 杠杆ETF
		MF_SECU_SUB_TYPE_CROSS_LOF = 16, //跨境LOF
	};
}
typedef T_ENUM<rem_mf_secu_sub_type::_> T_MF_SECU_SUB_TYPE;



//回购子类型
namespace rem_repo_secu_sub_type
{
	enum _
	{
		REPO_SECU_SUB_TYPE_CRP = 0, //质押式国债回购
		REPO_SECU_SUB_TYPE_BRP = 1,//质押式企业回购	
		REPO_SECU_SUB_TYPE_ORP = 2,//买断式国债回购	
	};
}
typedef T_ENUM<rem_repo_secu_sub_type::_> T_REPO_SECU_SUB_TYPE;


// 权证子类型
namespace rem_war_secu_sub_type
{
	enum _
	{
		WAR_SECU_SUB_TYPE_WAR = 0 ,
	};
}
typedef T_ENUM<rem_war_secu_sub_type::_>	T_WAR_SECU_SUB_TYPE;


// 期权子类型 
namespace rem_option_secu_sub_type
{
	enum _
	{
		OPTION_SECU_SUB_TYPE_ETF	= 0, ///< ETF期权 
		OPTION_SECU_SUB_TYPE_ABS	= 1, ///< 股票期权
	};
}
typedef T_ENUM<rem_option_secu_sub_type::_> T_OPTION_SECU_SUB_TYPE;


//其他几种类型，在交易系统中暂时用不到子类型，不定义了

//证券类型，需要2个字节同时决定，因此定义个结构体
typedef struct _secu_full_type
{	
	T_SECURITY_TYPE m_SecurityType;
	uInt8			m_SubType;	//取值是上面几个SECU_SUB_TYPE
	//使用在消息结构体中，默认值都被置0了

	_secu_full_type()
	{
		m_SecurityType = -1;
		m_SubType = -1 ;	
	}
	_secu_full_type(T_SECURITY_TYPE secu_type, uInt8 sub_type)
	{
		m_SecurityType = secu_type ;
		m_SubType = sub_type ;
	}

	bool is_cyb_stock()
	{
		if (m_SecurityType == rem_security_type::SECU_TYPE_STOCK && m_SubType == rem_cs_secu_sub_type::CS_SECU_SUB_TYPE_CYB)
			return true;
		return false;
	}	
	
	bool is_kcb_stock()
	{
		if (m_SecurityType == rem_security_type::SECU_TYPE_STOCK && m_SubType == rem_cs_secu_sub_type::CS_SECU_SUB_TYPE_A_KE_CHUANG)
			return true;
		return false;
	}

	
	//判断是不是盘后定价交易
	bool is_pfp(T_TIF tif, T_PRICE_TYPE priceType, uInt16 maxPriceLevels, uInt32 minQty)
	{
		if (rem_security_type::SECU_TYPE_STOCK != m_SecurityType
			|| rem_cs_secu_sub_type::CS_SECU_SUB_TYPE_A_KE_CHUANG != m_SubType) 
		{
			return false;
		}

		if (rem_tif::TIF_COMPLEX_ORDER == tif &&
			rem_price_type::PX_TYPE_LIMIT == priceType &&
			0 == maxPriceLevels &&
			0 == minQty) 
		{
			return true;
		}
		return false;
	}

	bool is_option()
	{
		return rem_security_type::SECU_TYPE_OPTION == m_SecurityType;
	}

	bool is_good()
	{
		return 	!is_bad();
	}

	bool is_bad()
	{
		uInt8 n_err = -1;
		return m_SecurityType == n_err || m_SubType == n_err;
	}

	bool is_repo()
	{
		return rem_security_type::SECU_TYPE_REPO == m_SecurityType;
	}
	
}T_SECU_FULL_TYPE;


//额外标志，目前只用于是否ETF申赎代码
namespace rem_secu_addi_flag
{
	enum _
	{
		RSAF_NORMAL = 0,	//一般
		RSAF_ETF_PURCHASE_REDEEM = 1,		//ETF申赎代码		
	};
}
typedef T_ENUM<rem_secu_addi_flag::_> T_SECU_ADDITIONAL_FLAG;

namespace rem_exchange
{
	enum _
	{
		EXCH_UNDEFINED = 0,
		EXCH_SHH = 100,//上交所
		EXCH_SHZ = 101,//深交所		
	};
}
typedef T_ENUM<rem_exchange::_> T_EXCHANGE;


namespace rem_compare
{
	enum _
	{
		rem_compare_large = 0, // "大于");
		rem_compare_less = 1, // "小于");
		rem_compare_equal = 2, // "等于");
		rem_compare_big_equal = 3, // "大于等于")
		rem_compare_less_equal4,  //"小于等于")
		rem_compare_no_equal = 5,  //"不等于");
	};
}
typedef T_ENUM<rem_compare::_> T_REM_COMPARE;



namespace rem_recheck_flag
{
	enum _
	{
		RECHECK_FLAG_NONE		 = 0,	///< 	未复核	0
		RECHECK_FLAG_NOT_CHECK	=  1 ,  ///< 	无需复核	1
		RECHECK_FLAG_MYSELF_CHECK = 2,	///< 自己复核	2
		RECHECK_FLAG_ACCEPT = 3,		///< 复核通过	3
		RECHECK_FLAG_REJ = 4,			///< 复核拒绝	4
		RECHECK_FLAG_DELETE = 5,		///< 已经删除	5
	};
}
typedef T_ENUM<rem_recheck_flag::_> T_RECHECK_FLAG ;


namespace rem_sse_platform_type
{
	enum _
	{
		SpotCentralizedTrading = 1, //[Description("现货集中竞价交易平台")] 
		IntegratedBusiness = 2,		//[Description("综合业务平台")]
		Option = 3,					//[Description("期权平台")]		
		InternationalMarket = 4,	// [Description("国际市场互联")]
	};
}
typedef T_ENUM<rem_sse_platform_type::_> T_REM_SSE_PLATFORM_TYPE ;



namespace rem_sze_platform_type
{
	enum _
	{
		SpotCentralizedTrading = 1, //[Description("现货集中竞价交易平台")] 
		IntegratedBusiness = 2,		//[Description("综合业务平台")]
		NoTrading = 3,				//{ 3,"非交易处理平台" },
		Option = 4,					//[Description("期权平台")]		
		InternationalMarket = 5,	//[Description("国际市场互联")]
	};
}
typedef T_ENUM<rem_sze_platform_type::_> T_REM_SZE_PLATFORM_TYPE ;

namespace rem_side
{
	enum _
	{
		SIDE_CS_BUY_OPEN = 1,					///买开仓
		SIDE_CS_SELL_CLOSE = 2,					///卖平仓		
		SIDE_CS_SELL_REPO = 3 ,					/// 逆回购
		SIDE_ETF_PURCHASE = 10,					///ETF申购
		SIDE_ETF_REDEEM = 11,					///ETF赎回
		SIDE_MARGIN_BUY = 20,					///融资买入
		SIDE_MQHK = 21,							///卖券还款
		SIDE_XJHK = 22,							///现金还款
		SIDE_DBPMR = 23,						///担保品买入
		SIDE_DBPMC = 24,						///担保品卖出
		SIDE_MQHQ = 25,							///买券还券
		SIDE_XQHQ = 26,							///现券还券
		SIDE_SELL_SHORT = 27,					///融券卖出
		SIDE_OPEN_COVERED_CALL = 30,			///备兑开仓
		SIDE_CLOSE_COVERED_CALL = 31,			///备兑平仓
		SIDE_OPT_EXECISE = 32,					///期权行权
		SIDE_COVERED_CALL_LOCK = 33,			///备兑锁定
		SIDE_COVERED_CALL_UNLOCK = 34,			///备兑解锁
		SIDE_OPT_BUY_OPEN = 35,					///期权买开仓
		SIDE_OPT_SELL_CLOSE = 36,				///期权卖平仓
		SIDE_OPT_SELL_OPEN = 37,				///期权卖开仓
		SIDE_OPT_BUY_CLOSE = 38,				///期权买平仓
		SIDE_OPT_FORCE_SELL_CLOSE  = 39 ,		///< 期权卖平仓（强平）
		SIDE_OPT_FORCE_BUY_CLOSE  = 40 ,		///< 期权买平仓（强平）
		SIDE_OPT_FORCE_CLOSE_COVERED_CALL=41,	///< 备兑平仓（强平）
		SIDE_OPT_AGREEMENT_EXECISE=42,			///< 备兑平仓（强平）
		SIDE_OPT_COMB_EXERCISE			=	43 , ///<期权合并申报行权
		SIDE_OPT_COMB_POS_CREATE		=	44 , ///<期权构建组合策略
		SIDE_OPT_COMB_POS_RELIEVE		=	45 , ///<期权解除组合策略
		SIDE_OPT_COVERED_TO_NORMAL		=	46 , ///<期权备兑转普通
		SIDE_OPT_NORMAL_TO_COVERED		=	47 , ///<期权普通转备兑
		SIDE_OPT_FORCE_COMB_POS_RELIEVE	=	48 , ///<期权解除组合策略（券商强制解除）
	};
}
typedef T_ENUM<rem_side::_> T_SIDE;



namespace rem_risk_rule_type
{
	enum _
	{
		RRT_GLOBAL = 1,
		RRT_SECU_TYPE = 2,
		RRT_FUND_ACCOUNT = 3,
		RRT_FUND_ACCOUNT_AND_SYMBOL = 4,
		RRT_FUND_ACCOUNT_AND_INSTRUMENT = 5,
	};
}
typedef T_ENUM<rem_risk_rule_type::_> T_RISK_RULE_TYPE;


namespace account_instrumet_disable
{
	enum _ 
	{
		DISABLE_SIDE_OPT_OPEN_SHORT		= 0x00000001  ,  ///< 期权卖开仓	0:禁止开义务仓
		DISABLE_SIDE_OPT_OPEN_LONG 		= 0x00000002  ,  ///< 期权买开仓	1:禁止开权力仓
		DISABLE_SIDE_OPT_CLOSE_SHORT 	= 0x00000004  ,  ///< 期权卖平仓	2:禁止平义务仓
		DISABLE_SIDE_OPT_CLOSE_LONG 	= 0x00000008  ,  ///< 期权买平仓	3:禁止平权力仓
		DISABLE_SIDE_OPEN_COVERED_CALL 	= 0x00000010  ,  ///< 备兑开仓	4:禁止备兑开仓
		DISABLE_SIDE_CLOSE_COVERED_CALL = 0x00000020  ,  ///< 备兑平仓	5:禁止备兑平仓
		DISABLE_SIDE_OPT_EXECISE 		= 0x00000040  ,  ///< 期权行权	6:禁止行权	
	};
}
	

/*下面这段草稿给各种switch来用
case rem_side::SIDE_CS_BUY_OPEN:			///买开仓
{
}
break;
case rem_side::SIDE_CS_SELL_CLOSE:		///卖平仓	
{
}
break;
case rem_side::SIDE_ETF_PURCHASE:		///ETF申购
{
}
break;
case rem_side::SIDE_ETF_REDEEM:		///ETF赎回
{
}
break;
case rem_side::SIDE_MARGIN_BUY:		///融资买入
{
}
break;
case rem_side::SIDE_MQHK:				///卖券还款
{
}
break;
case rem_side::SIDE_XJHK:				///现金还款
{
}
break;
case rem_side::SIDE_DBPMR:			///担保品买入
{
}
break;
case rem_side::SIDE_DBPMC:			///担保品卖出
{
}
break;
case rem_side::SIDE_MQHQ:				///买券还券
{
}
break;
case rem_side::SIDE_XQHQ:				///现券还券
{
}
break;
case rem_side::SIDE_SELL_SHORT:		///融券卖出
{
}
break;
case rem_side::SIDE_OPEN_COVERED_CALL:///备兑开仓
{
}
break;
case rem_side::SIDE_CLOSE_COVERED_CALL:///备兑平仓
{
}
break;
case rem_side::SIDE_OPT_EXECISE:		///期权行权
{
}
break;
case rem_side::SIDE_COVERED_CALL_LOCK: ///备兑锁定
{
}
break;
case rem_side::SIDE_COVERED_CALL_UNLOCK: ///备兑解锁
{
}
break;
case rem_side::SIDE_OPT_BUY_OPEN:			///期权买开仓
{
}
break;
case rem_side::SIDE_OPT_SELL_CLOSE:		///期权卖平仓
{
}
break;
case rem_side::SIDE_OPT_SELL_OPEN:		///期权卖开仓
{
}
break;
case rem_side::SIDE_OPT_BUY_CLOSE:		///期权买平仓
{
}
break;
 */

//给手续费用，和SIDE有紧密的关系，参考 get_trade_type函数
namespace rem_trade_type
{
	enum _
	{
		TRADE_TYPE_OTHER = 0,
		TRADE_TYPE_CS_BUY = 1,			///股票买
		TRADE_TYPE_CS_SELL_CLOSE = 2,		///股票卖		
		TRADE_TYPE_ETF_BUYSELL	= 3,			///ETF买卖		
		TRADE_TYPE_ETF_PURCHASE_REDEEM = 4,		///ETF申购赎回

		TRADE_TYPE_OPT_AGREEMENT_EXECISE = 5,					///协议行权
		TRADE_TYPE_OPT_EXECISE = 6,					///期权行权

		TRADE_TYPE_OPEN_COVERED_CALL = 7,			///备兑开仓
		TRADE_TYPE_CLOSE_COVERED_CALL = 8,			///备兑平仓		
		TRADE_TYPE_OPT_BUY_OPEN = 9,				///期权买开仓
		TRADE_TYPE_OPT_SELL_CLOSE = 10,				///期权卖平仓
		TRADE_TYPE_OPT_SELL_OPEN = 11,				///期权卖开仓
		TRADE_TYPE_OPT_BUY_CLOSE = 12,				///期权买平仓
		TRADE_TYPE_CS_SELL_REPO	= 13 ,				/// 逆回购

		//TODO: 融资融券分类
	};
}
typedef T_ENUM<rem_trade_type::_> T_TRADE_TYPE;




namespace rem_cashmargin_flag
{
	enum _
	{
		CMF_CASH = 1,			///普通
		CMF_MARGIN_OPEN = 2,	///融资融券开仓
		CMF_MARGIN_CLOSE = 3,	///融资融券平仓
	};
}
typedef T_ENUM<rem_cashmargin_flag::_> T_CASHMARGIN_FLAG;

namespace rem_session_sel_mode
{
	enum _
	{
		SSM_CYCLE = 0,		///由服务器指定
		SSM_SPECIFY = 1,	///客户端指定
	};
}
typedef T_ENUM<rem_session_sel_mode::_> T_SESSION_SEL_MODE;

namespace rem_exchange_accept_flag
{
	enum _
	{
		EXCH_NOT_ACCEPTED = 0,
		EXCH_ACCEPTED = 1,
	};
}
typedef T_ENUM<rem_exchange_accept_flag::_> T_EXCHANGE_ACCPET_FALG;

namespace rem_passive_order_flag
{
	enum _
	{
		POF_NORMAL = 0, 
		POF_PASSIVE = 1,
		POF_EXTERNAL = 2,
	};
}
typedef T_ENUM<rem_passive_order_flag::_> T_PASSIVE_ORDER_FLAG;

namespace rem_cxl_req_status
{
	enum _
	{
		CXL_REQ_INVALID = 0,
		CXL_REQ_PENDING = 1,
		CXL_REQ_CXLED = 2,
		CXL_REQ_REJECTED = 3,
	};
}
typedef T_ENUM<rem_cxl_req_status::_> T_CXL_REQ_STATUS;

namespace rem_opt_call_put
{
	enum _
	{
		OPT_CALL = 'C',
		OPT_PUT = 'P',
	};
}
typedef T_ENUM<rem_opt_call_put::_> T_OPT_CALL_PUT;


namespace rem_rejected_by
{
	enum _
	{
		REJECTED_BY_REM = 0,
		REJECTED_BY_EXCH = 1,
		REJECTED_BY_MI = 2,
	};
}
typedef T_ENUM<rem_rejected_by::_> T_REJECTED_BY;

namespace rem_batch_flag
{
	enum _
	{
		BF_SINGLE_PACKAGE = 0,
		BF_START_PACKAGE = 1,
		BF_BODY_PACKAGE = 2,
		BF_END_PACKAGE = 3,
	};
}
typedef T_ENUM<rem_batch_flag::_> T_BATCH_FLAG;

namespace rem_owner_type
{
	enum _
	{
		OWNER_TYPE_NONE				= 0, ///<	保留
		OWNER_TYPE_INDIVIDUAL		= 1 , ///<	散户，个人
		OWNER_TYPE_MEMBER			= 2 , ///<	会员
		OWNER_TYPE_INSTITUTION		= 3 , ///<	机构
		OWNER_TYPE_DEALER			= 4, ///<	自营
		OWNER_TYPE_MARKET			= 5, ///<	做市商		
	};
}
typedef T_ENUM<rem_owner_type::_> T_REM_OWNER_TYPE;

namespace rem_rewind_status
{
	enum _
	{
		RWS_ORDER_BEGIN = 1,
		RWS_EXEC_BEGIN = 2,
		RWS_CXLREQ_BEGIN = 3,
		RWS_ORDER_END = 8,
		RWS_EXEC_END = 9,
		RWS_CXLREQ_END = 10,
	};
}
typedef T_ENUM<rem_rewind_status::_> T_REWIND_STATUS;

namespace rem_session_status
{
	enum _
	{
		RSS_NOT_CONNECTED = 0,
		RSS_CONNECTED = 1,
	};
}
typedef T_ENUM<rem_session_status::_> T_SESSION_STATUS;

namespace rem_logon_result
{
	enum _
	{
		LR_SUCCESS = 0,
		LR_USERPWD_INCORRECT = 1,
		LR_CONFIG_INCORRECT = 2,
		LR_ALREADY_LOGON = 3,
		LR_INVALID_RELOGON = 4, //在已登录的连接,又发送其他用户的登录请求
		LR_MISSING_CLIENT_INFO = 5,
		LR_INTERNAL_ERROR = 6,				//系统内部错误
		LR_NOT_USING_QUERY_PORT = 7,		//未使用查询通道，2017-05-22开始，强制要求使用
		LR_CONNECT_QUERY_PORT_FAILED = 8,	//连接查询通道失败，这个错误不会在服务器上报，只会在客户端API内部报出
		LR_AUTH_FAILED = 9,					//  ip mac 认证失败
		LR_USER_STATUS = 10,				// 用户状态错误
		LR_APP_ID_AUTH_FAILED = 11,			//  appid 认证失败


		LR_SYSTEM_CRITICAL = 99,	//系统资源不足,不允许新用户连接上来
	};
}
typedef T_ENUM<rem_logon_result::_> T_REM_LOGON_RESULT;

namespace rem_user_status
{
	enum _
	{

		UserStatus_Normal = 0, // "正常"
		UserStatus_Freeze = 1, //"冻结"
		UserStatus_Close = 2, //"注销"
	};
}
typedef T_ENUM<rem_user_status::_> T_REM_USER_STATUS ;



namespace rem_cust_acct_status
{
	enum _
	{
		CustAcctStatus_Normal = 0, // "正常"
		CustAcctStatus_Freeze = 1, //"冻结"
		CustAcctStatus_Close = 2, //"注销"
	};
}
typedef T_ENUM<rem_cust_acct_status::_> T_REM_CUST_ACCT_STATUS;

namespace rem_cust_status
{
	enum _
	{
		CustStatus_Normal = 0, // "正常"
		CustStatus_Close = 1, //"注销"
	};
}
typedef T_ENUM<rem_cust_status::_> T_REM_CUST_STATUS;

namespace rem_change_pwd_result
{
	enum _
	{
		CPR_SUCCESS = 0,
		CPR_OLD_PWD_INCORRECT = 1,
		CPR_NEW_PWD_INVALID = 2,
		CPR_NOT_LOGON = 3,
		CP4_SVR_PROBLEM = 99,
	};
}
typedef T_ENUM<rem_change_pwd_result::_> T_CHANGE_PWD_RESULT;

namespace rem_last_record_flag
{
	enum _
	{
		LRF_FALSE = 0,
		LRF_TRUE = 1,
	};
}
typedef T_ENUM<rem_last_record_flag::_> T_LAST_RECORD_FLAG;

namespace rem_fund_account_type
{
	enum _
	{
		FAT_NORMAL = 0,//普通账户
		FAT_MARGIN = 1,//信用账户
		FAT_DERIVATIVES = 2,//衍生品账户，目前用于期权
		FAT_END				//以后新添账户类型都加在这行前面
	};
}
typedef T_ENUM<rem_fund_account_type::_> T_FUND_ACCOUNT_TYPE;


namespace rem_hw_using_margn_flag
{
	enum _
	{
		MARGIN_CONF = 0	,	// 0：第一次配置保证金率
		MARGIN_USING_DYNAMIC_MARGIN = 1,	// 1：配置动态保证金
	};
}
typedef T_ENUM<rem_hw_using_margn_flag::_> T_HW_USING_MARGIN_FLAG ;

namespace rem_account_previlege
{
	enum _
	{
		AP_NORMAL = 0,		//没有创业板权限
		AP_CAN_CYB = 1,		//有创业板权限
		AP_OPT_LEVEL1 = 2,	//期权1级权限
		AP_OPT_LEVEL2 = 3,	//期权2级权限
		AP_OPT_LEVEL3 = 4,	//期权3级权限
	};
}
typedef T_ENUM<rem_account_previlege::_> T_ACCOUNT_PREVILEGE;


namespace rem_account_finanching_exercise
{
	enum _
	{
		AFE_NO = 0,		///< 不能融资行权
		AFE_YES = 1,	///< 允许融资行权
	};
}
typedef T_ENUM<rem_account_finanching_exercise::_> T_ACCOUNT_FINANCHING_EXERCISE;


namespace rem_subst_cash_flag
{
	enum _
	{
		SCF_NO_SUBST = 0,		//不能现金替代
		SCF_CAN_SUBST = 1,		//可以现金替代，替代比例有上限
		SCF_MUST_SUBST = 2,		//必须现金替代
		SCF_TUIBU = 3,			//退补
	};
}
typedef T_ENUM<rem_subst_cash_flag::_> T_SUBST_CASH_FLAG;

namespace rem_pos_dir
{
	enum _
	{
		POS_DIR_LONG = 1,
		POS_DIR_SHORT = 5,
		POS_DIR_COVERED = 9,//备兑仓，实际上类似空头，不过是用仓位保证而已
	};
}
typedef T_ENUM<rem_pos_dir::_> T_POS_DIR;

//备兑标志
namespace rem_covered_flag
{
	enum _
	{
		RCF_UNCOVERED = 0,
		RCF_COVERED = 1,
	};
}
typedef T_ENUM<rem_covered_flag::_> T_COVERED_FLAG;

//费用类型
namespace rem_fee_type
{
	enum _
	{
		FT_COMMISSION = 0,	//手续费，佣金
		FT_STAMP = 1,		//印花税
		FT_TRANSFER = 2,	//过户费
	};
}
typedef T_ENUM<rem_fee_type::_> T_FEE_TYPE;

//硬件数据库导出结构体标志
namespace rem_risk_db_flag
{
	enum _
	{
		RDF_RESERVED = 0, //保留不用
		RDF_RULE_ACCUMULATE_VALUE, //RULE累加值
		RDF_POSITION,		//仓位
		RDF_FEE_RATE,		//费率，必须有symbol
		RDF_RISK_LIMIT_VALUE,	//风控门限值，尚不支持
	};
}
typedef T_ENUM<rem_risk_db_flag::_> T_RISK_DB_FLAG;


namespace rem_self_trade_update_flag
{
	enum _
	{
		STU_NEW_ORDER = 0,				//0: New Order时的配置
		STU_FULLFILLED,					//1：完全成交造成的变化时配置
		STU_CXLED,						//2：撤单成功时造成的变化时配置
		STU_EXCH_RJT,					//3: 交易所拒绝时造成的变化时配置
	};
}
typedef T_ENUM<rem_self_trade_update_flag::_> T_SELF_TRADE_UPDATE_FLAG;

namespace rem_option_grammer_check_result
{
	enum _
	{
		NO_ERR = 0,						//0: 没有错误
		FUND_ACCOUNT_STRUCT_ERROR,		//1: 账户关系不完整
		FUND_ACCOUNT_TYPE_ERROR,		//2: 账户类型错误
		SYMBOL_TYPE_ERROR,				//3: 股票类型错误
		AVAIL_POS_QTY_ERROR,			//4: 可用券不够
		AVAIL_BP_ERROR,					//5: 可用资金不够
		EXIST_SEQ_ID_ERROR,				//6: qmcs消息的req id已存在
		NOT_EXIST_SEQ_ID_ERROR,			//7: qmsc消息的req id不存在
		NOT_FIND_EXCHANGE_ACCOUNT		//8: 获取交易所账户失败
		
		/// TODO zjw 20180518 其他synctrade, hds相关错误请往下定义
	};
}
typedef T_ENUM<rem_option_grammer_check_result::_> T_OPTION_GRAMMER_CHECK_RESULT;

// 现金替代标记
namespace rem_substitute_flag
{
	enum _
	{
		SubstituteFlag_No = 0, // 禁止现金替代
		SubstituteFlag_Need = 1 , // 可以进行现金替代
		SubsittuteFlag_Must = 2 , // 必须用现金替代		
	};
}
typedef T_ENUM<rem_substitute_flag::_>	REM_SUBSTITUTE_FLAG;



// 配置里面的客户类型
namespace cust_sw_type
{
	enum _
	{
		cust_sw_type_Individual = 1, // 个人		
		cust_sw_type_member = 2, //  会员
		cust_sw_type_Institution = 3, //  机构
		cust_sw_type_Dealers = 4,  // 自营
		cust_sw_type_MarketMarker = 5, // 做市商
	};
}
typedef T_ENUM<cust_sw_type::_> T_CUST_SW_TYPE;


//#END，股票版枚举定义

///#START，消息类型定义, 用namespace来分开

//#查询请求类_Client发往REM
namespace qmcs_types
{
	enum _
	{
		QMCS_PROTOCOL_VERSION_REPORT = 2000,
		QMCS_LOGON_REQ = 2001,
		QMCS_CHANGE_PASSWORD_REQ = 2002,
		QMCS_CLIENT_ID_LIST_REQ = 2003,
		QMCS_FUND_ACCOUNT_LIST_REQ = 2004,
		QMCS_SECURITY_CODE_LIST_REQ = 2005,
		QMCS_ETF_MEMBER_LIST_REQ = 2006,
		QMCS_OPT_DETAIL_LIST_REQ = 2007,
		QMCS_FEE_QUERY_REQ = 2008,
		QMCS_NORMAL_POSITION_QUERY_REQ = 2009,
		QMCS_TRADE_REWIND_REQ = 2010,
		QMCS_BP_QUERY_REQ = 2011,
		QMCS_EXCH_SESS_REQ = 2012,
		QMCS_NON_SYMBOL_RISK_ACCUM_VAL_REQ = 2013,
		QMCS_SYMBOL_RISK_ACCUM_VAL_REQ = 2014,
		QMCS_HEARTBEAT_REQ = 2015,		///< 用户的心跳请求。

		/// lgl 20180226 查询登录
		QMCS_QUERY_LOGON_REQ = 2016,

		QMCS_QRY_UNDERLYING_SYMBOL_QTY_REQ	=	2017,	 // 查询标的券数(2017-)
		QMCS_FRZ_UNDERLYING_SYMBOL_QTY_REQ	=	2018,	 // 向主席锁定/解锁标的券数量(2018-)
		QMCS_INOUT_FUND_ACCOUNT_AMOUNT_REQ	=	2019,	 // 同主席划入划出资金 (2019-)
		QMCS_OPTION_POSITION_QUERY_REQ = 2020,
		QMCS_REQ_REPORT_CAPTURE_CLIENT_INFO_REQ = 2021 ,
		QMCS_OUT_FUND_ACCOUNT_AMOUNT_NODE_REQ = 2022 , 	 // 向其他节点划入资金 (2022-)
		QMCS_TRADE_ACCOUNT_LIST_REQ = 2023 , 	 // 查询股东账户 (2023-)
	};
}

//#查询响应类，REM发往Client
namespace qmsc_types
{
	enum _
	{
		QMSC_PROTOCOL_VERSION_RESP = 3000,
		QMSC_LOGON_RESP = 3001,
		QMSC_CHANGE_PASSWORD_RESP = 3002,
		QMSC_CLIENT_ID_LIST_RESP = 3003,
		QMSC_FUND_ACCOUNT_LIST_RESP = 3004,
		QMSC_SECURITY_CODE_LIST_RESP = 3005,
		QMSC_ETF_MEMBER_LIST_RESP = 3006,
		QMSC_OPT_DETAIL_LIST_RESP = 3007,
		QMSC_FEE_QUERY_RESP = 3008,
		QMSC_NORMAL_POSITION_QUERY_RESP = 3009,
		QMSC_ORDER_REWIND_RESP = 3010,
		QMSC_EXEC_REWIND_RESP = 3011,
		QMSC_CXL_REQ_REWIND_RESP = 3012,
		QMSC_ORDER_REWIND_FINISH = 3013,
		QMSC_EXEC_REWIND_FINISH = 3014,
		QMSC_CXL_REQ_REWIND_FINISH = 3015,
		QMSC_BP_QUERY_RESP = 3016,
		QMSC_EXCH_SESS_RESP = 3017,
		QMSC_EXCH_SESS_STATUS_REPORT = 3018,
		QMSC_ETF_EXEC_REWIND_RESP = 3019,
		QMSC_NON_SYMBOL_RISK_ACCUM_VAL_RESP = 3020,
		QMSC_SYMBOL_RISK_ACCUM_VAL_RESP = 3021,

		/// lgl 20180226  交易端口的登录返回消息
		QMSC_QUERY_LOGON_RESP = 3022,
		QMSC_HEARTBEAT_RESP = 3023,			///< 心跳包的回复消息

		QMSC_QRY_UNDERLYING_SYMBOL_QTY_RESP = 3024,	//	查询可锁券数量返回(3024-)
		QMSC_FRZ_UNDERLYING_SYMBOL_QTY_RESP = 3025,	//	向主席请求锁定、解锁标的券 (3025-)
		QMSC_INOUT_FUND_ACCOUNT_AMOUNT_RESP = 3026,	//	同主席资金划拔返回(3026-)

		QMSC_SYSTEM_MSG_REPORT = 3027,	 // 系统消息报告。

		QMSC_OPTION_POSITION_QUERY_RESP = 3029,
		QMSC_OUT_FUND_ACCOUNT_AMOUNT_NODE_RESP = 3030,	//	向交易节点资金划转返回(3030-)
		QMSC_TRADE_ACCOUNT_LIST_RESP = 3031,	//	查询股东账户返回(3031-)

	};
}

//#交易类_Client发往REM硬件
namespace tmcs_types
{
	enum _
	{
		TMCS_NEW_ORDER_REQ = 10,
		TMCS_CXL_REQ = 13,
	};
}

//#交易类_REM硬件发往Client
namespace tmsc_types
{
	enum _
	{
		TMSC_ORDER_ACCEPT = 1010,
		TMSC_ORDER_REJECT = 1011,
		TMSC_ORDER_EXECUTION	= 1012,
		TMSC_ORDER_CXLED = 1013,
		TMSC_CXL_REJECTED = 1014,
		TMSC_ETF_EXEC = 1015,
	};
}

//#KIWIUM消息
namespace kwum_types
{
	enum _
	{
		KWUM_STOH_LOGIN_SUCCESS = 1088,
		KWUM_HTOS_SESSION_ERROR_REPORT = 1089,		
		KWUM_HTOS_STATUS_REPORT = 1212,
	};
}

namespace cmhs_types
{
	enum _
	{
		//注意下面2条，他们是从0号通道，也就是 kiwi comm api里获取到的。消息类型取值用12打头，其实最好改一下
		CMHS_HTOS_HW_ERROR_REPORT = 1210,
		CMHS_HTOS_HW_DATA_REPORT = 1211,
		
	};
}

//#交易类，内部软件发给硬件
namespace tmsh_types
{
	enum _
	{
		TMSH_REWIND_STATUS = 4000,
		TMSH_REWIND_ORDER = 4001,
		TMSH_REWIND_EXECUTION = 4002,
		TMSH_REWIND_CXL_REQ = 4003,
		TMSH_REWIND_ETF_EXEC = 4004,
		TMSH_PASSIVE_EXEC = 4005,
		TMSH_PASSIVE_CXLED = 4006,
		TMSH_PASSIVE_ORDER = 4007,
		TMSH_PASSIVE_EXCH_ACCEPT = 4008,
		TMSH_PASSIVE_CXL_REJECT = 4009,
		TMSH_PASSIVE_MARKET_REFF_ID = 4010,
	};
}

//#交易类，硬件发往软件内部
namespace tmhs_types
{
	enum _
	{
		TMHS_ORDER_SNAPSHOT = 5000,
		TMHS_CXL_REQ_SNAPSHOT = 5001,
		TMHS_EXEC_SNAPSHOT = 5002,
		TMHS_ETF_EXEC_SNAPSHOT = 5003,		
		TMHS_ORDER_REJECT_DROPCOPY = 5004,
		TMHS_CXL_REJECT_DROPCOPY = 5005,
		TMHS_ORDER_EXCH_ACCEPT = 5010,
		TMHS_ORDER_EXCH_REJECT = 5011,
		TMHS_PASSIVE_EXT_ORDER = 5012,
		TMHS_ORDER_CXLED = 5021,
		TMHS_EXCH_CXL_REJECT = 5022,
		TMHS_CXL_REQ_SNAPSHOT_HWMKT = 5601,
		TMHS_ORDER_SH_CS_REC_NUM_SNAPSHOT = 50005000 , // 这个是软件自己生成的，所以定义的比较大。
	};
}

///交易类，硬件发往MI，本消息段暂时不用，用5000和5001的消息即可
namespace tmhm_types
{
	enum _
	{
		TMHM_NEW_ORDER_REQUEST = 6000,
		TMHM_CXL_REQ	=	6001,
	};
}

///交易类，MI发往硬件
namespace tmmh_types
{
	enum _
	{
		TMMH_ORDER_ACCEPT = 7000,
		TMMH_ORDER_REJECT = 7001,
		TMMH_ORDER_EXECUTION = 7002,
		TMMH_ETF_EXECUTION = 7003,
		TMMH_ORDER_CXLED = 7004,
		TMMH_CXL_REJECT = 7005,
		TMMH_SESSION_STATUS_REPORT = 7006,
	};
}

//#硬件配置通道消息类型
namespace hwcm_types
{
	enum _
	{		
		HWCM_NO_OPT_SECURITY_CODE_CONFIG = 8000,
		HWCM_OPT_SECURITY_CODE_CONFIG = 8001 ,
		HWCM_ACCOUNT_STRUCTURE_CONFIG = 8002 ,
		HWCM_CLIENT_USER_ID_LINK_CONFIG = 8003 ,
		HWCM_EXCHANGE_SESSION_LINK = 8004 ,
		HWCM_EXCHANGE_ORDER_ID_RANGE_CONFIG = 8004,
		HWCM_CUST_PBU_PLATFORM_CONFIG = 8005 ,
		HWCM_ADJUST_UNDERLYING_POS_SHARE = 8006 ,
		HWCM_PRICE_CONFIG = 8007 ,
		HWCM_FEE_CONFIG = 8008 ,
		HWCM_TRADINGTIME_CASH_INOUT = 8009 ,
		HWCM_OPT_MARGIN_CONFIG = 8010,
		HWCM_ETF_MEMBER_CONFIG = 8011,
		HWCM_RISK_THRESHOLD_CONFIG = 8012,
		HWCM_ALL_CONFIG_DONE = 8013 ,		//目前用不到
		HWCM_CLIENT_ID_LIST_CONFIG = 8014 ,
		HWCM_SELF_TRADE_PRICE_CONFIG = 8015 ,//自成交价格配置
		HWCM_RISK_SWITCH_CONFIG= 8016 ,
		HWCM_RISK_DB_EXPORT_REQUEST = 8017 ,//硬件数据库导出请求
		HWCM_REPO_FEE_CONFIG	= 8018	,	// 配置逆回购费用
		HWCM_VARIETY_AUTHORITY_CONFIG		= 8019	,	// 配置账户品种控制
		HWCM_COMB_STRATEGY_CONFIG	= 8020,	// 期权组合策略配置信息(8020)
		HWCM_COMB_STRATEGY_UNDERLYING_CONF	= 8021,	// 期权组合策略标的清单(8021)
		HWCM_REWIND_RUNTIME_NORMAL_POSITION = 8100,//回滚非期权的实时仓位
		HWCM_REWIND_RUNTIME_OPTION_POSITION = 8101,//回滚期权的试试仓位
		HWCM_REWIND_RISK_STATISTICS = 8102 ,//回滚风控累加值，其中BP的回滚就是当risk rule = 1时	


		HWCM_USER_FLOW_CONTROL = 8200 ,
	};
}

//#hds相关协议类型定义
namespace hdsm_types
{
	enum _
	{
		HDSM_HDS_MONITOR_REPORT = 1024 ,
		HDSM_HDC_LOGON_REQ = 10001,
		HDSM_HDC_LOGON_RESP = 10002,
		HDSM_EMC_LOGON_REQ = 10003,
		HDSM_EMC_LOGON_RESP = 10004,
		HDSM_OT_MONITOR_REPORT = 10005,
		HDSM_BK_MONITOR_REPORT = 10006,
		HDSM_LGS_MONITOR_REPORT = 10007,
		HDSM_USER_FORBIDDEN_CONTROL = 10008,
		HDSM_HELPDESK_EXECUTION = 10009,
		HDSM_HELPDESK_CXLED = 10010,
		HDSM_HELPDESK_PASSIVE_ORDER = 10011,
		HDSM_HELPDESK_CXL_REJ = 10012,
		HDSM_HELPDESK_EXCH_ACCEPT = 10013,
		HDSM_EMC_LOGON_FINISHED_RESP = 10014,
		HDSM_EMC_HEARTBEAT = 10015,
		HDSM_RISK_THRESHOLD_CHANGE = 10016,
		HDSM_RISK_SWITCH_CHANGE = 10017,
		HDSM_RS_MONITOR_REPORT = 10018,
		HDSM_EMC_TRADING_TIME_CASH_INOUT = 10019,
		HDSM_OT_TRADING_TIME_CASH_INOUT = 10020,
		HDSM_HELPDESK_DISABLE_INSTRUMENT_TRADE = 10021,
		HDSM_HELPDESK_FORCE_COVER_ORDER = 10022 ,
		HDSM_EQS_MONITOR_REPORT = 10023 ,
		HDSM_OT_TRADER_LINK_REPORT = 10024 ,

		///  lgl 20180306 新加的查询寄存器数据
		HDSM_REGISTER_STATUS_REQ = 10025 ,
		HDSM_REGISTER_STATUS_RESP = 10026 ,

		HDSM_EMC_KILL_TRADE_SESSION_REQ = 10027 ,
		//HDSM_EMC_KILL_LINEK_SESSION_RESP = 10028 ,

		HDSM_EMC_SET_BLACKIP_LIST_REQ = 10029 ,
		//HDSM_EMC_SET_BLACKIP_LIST_RESP = 10030 ,
		
		HDSM_EMC_QRY_BLACKIP_LIST_REQ = 10031 ,
		HDSM_EMC_QRY_BLACKIP_LIST_RESP = 10032 ,

		HDSM_NEW_EMC_MANUAL_POS = 10033,

		HDSM_HDS_QRY_UNDERLYING_SYMBOL_QTY_REQ		=	10035	,	// 向HDS请求查询账户的可用标的券数量[10035]
		HDSM_HDS_QRY_UNDERLYING_SYMBOL_QTY_RESP		=	10036	,	// 向HDS请求查询账户的可用标的券数量 回复[10036]
		HDSM_HDS_FRZ_UNDERLYING_SYMBOL_QRY_REQ		=	10037	,	// 向HDS请求锁定、解锁可用标的券 [10037]
		HDSM_HDS_FRZ_UNDERLYING_SYMBOL_QRY_RESP		=	10038	,	// 向HDS 请求锁定、解锁可用标的券的回复 [10038]
		HDSM_HDS_INOUT_FUND_ACCOUNT_AMOUNT_REP		=	10039	,	// 向 HDS请求主席资金划拔的请求[10039]
		HDSM_HDS_INOUT_FUND_ACCOUNT_AMOUNT_RESP		=	10040	,	// 向hds请求主席资金划拔拓回复[10040]
		HDSM_SYNC_QRY_UNDERLYING_SYMBOL_QTY_REQ		=	10041	,	// 向SyncTrade请求查询账户的可用标的券数量[10041]
		HDSM_SYNC_QRY_UNDERLYING_SYMBOL_QTY_RESP	=	10042	,	// 向SyncTrade请求查询账户的可用标的券数量 回复[10042]
		HDSM_SYNC_FRZ_UNDERLYING_SYMBOL_QRY_REQ		=	10043	,	// 向SyncTrade请求锁定、解锁可用标的券 [10043]
		HDSM_SYNC_FRZ_UNDERLYING_SYMBOL_QRY_RESP	=	10044	,	// 向SyncTrade 请求锁定、解锁可用标的券的回复 [10044]
		HDSM_SYNC_INOUT_FUND_ACCOUNT_AMOUNT_REP		=	10045	,	// 向 SyncTrade请求主席资金划拔的请求[10045]
		HDSM_SYNC_INOUT_FUND_ACCOUNT_AMOUNT_RESP	=	10046	,	// 向SyncTrade请求主席资金划拔拓回复[10046]


		HDSM_SYNC_TRADE_MONITOR_REPORT = 10048,//监控消息
		HDSM_SQL_MONITOR_REPORT = 10049,//报盘库监控消息


		HDSM_QUERY_OT_TRADER_LINK = 10050,
		HDSM_USER_LOGON_INFO = 10051,	///< 用于记录登录流水

		HDSM_SQL_UPDATA_SIG = 10052,	//增加盘中配置

		HDSM_CHANGE_POSITION_SHARE = 10053 ,


	};
}

///#quote相关消息类型
namespace quote_types
{
	enum _
	{
		QUOTE_LOGON_REQ = 11001,		
		QUOTE_REG_SYMBOL_REQ = 11002,
		QUOTE_UNREG_SYMBOL_REQ = 11003,
	
		QUOTE_LOGON_RESP = 11005,
		QUOTE_REG_SYMBOL_RESP  = 11006,
		QUOTE_UNREG_SYMBOL_RESP = 11007,
		QUOTE_QUOTE_SNAPSHOT = 11008,
		
		QUOTE_QUOTE_HEARTBEAT	=	11009,

		QUOTE_QUOTE_QRY_QUOTE = 11010, // 查询合约行情
		QUOTE_QUOTE_QRY_QUOTE_RESP = 11011, // 查询合约行情

	};
}

/// 硬件MI相关通讯
namespace hwmi_types
{
	enum _
	{

		HWMI_CONFIG_TYPES_PARTITIONS_INFO= 21000 ,			///<	平台分区信息
		HWMI_CONFIG_TYPES_RAW_EXCHANGE_DATA = 21001 ,		///<	抄送全市场回单消息
		HWMI_CONFIG_TYPES_REPORT_INDEX_INFO= 21002 ,			///<	平台分区信息
		HWMI_CONFIG_TYPES_MSSQL_CONFIG = 22000 ,			///<	报盘配置
		HWMI_CONFIG_TYPES_SSE_OFFER_CONFIG = 22001 ,			///<	上交所报盘软件属性配置
		HWMI_CONFIG_TYPES_MSSQL_REQNUM_CONFIG = 22002 ,		///<	报盘reqnum配置
		HWMI_CONFIG_TYPES_DATE_CONFIG = 22003 ,				///<	系统日期配置
		HWMI_CONFIG_TYPES_NEW_ORDER_REQ = 22005 ,			///<	硬件下单以后，通知软件系统
		HWMI_CONFIG_TYPES_CXL_ORDER_REQ = 22006 ,			///<	硬件撤单以后，通知软件系统
		HWMI_CONFIG_TYPES_SZE_TGW_CONFIG = 23000 ,			///<	深交所TGW属性配置
		HWMI_CONFIG_TYPES_REPORTINDEX_CONFIG = 23002,			///<	初始ReportIndex配置
		HWMI_CONFIG_TYPES_HEARTBEAT_CONFIG = 23003,			///<	心跳间隔配置
	};
}


namespace hw_err_type
{
	enum hw_err_type
	{
		HW_ERR_Msg_Type_Err = 1 ,
		HW_ERR_Msg_Length_Err = 2 ,
		HW_ERR_Cnf_Client_Cam_Err = 3,
		HW_ERR_Client_ID_Err = 4 ,
		HW_ERR_Symbol_Cam_Err = 5 , 
		HW_ERR_Nof_Find_SymbolID = 6, 
		HW_ERR_8002_Msg_Err = 7,
		HW_ERR_8006_Msg_err = 8 ,
	};
}

///消息分发类型
namespace distribute_msg_type
{
	enum _
	{
		TRADE_DISTRIBUTE = 0,
		QUERY_DISTRIBUTE,
	};
}
///#END，消息类型定义

//#START，TypeStructures

///本结构体用于方便处理用Int64表示的，精确到最多8位小数的浮点类型，大多用于费率配置
struct T_RATE_8
{
protected:
	Int64 m_val;

public:
	T_RATE_8()
	{
		m_val = 0;
	}

	T_RATE_8& operator = (double val)
	{
		m_val = (val + 0.000000005) * 100000000.0 ;//+0.000000005表示4舍5入		
		return *this ;
	}

	double get_double() const 
	{		
		return (double)(m_val) * 1.0 / 100000000.0 ;
	}

	Int64 get_long() const 
	{
		return m_val;
	}
};

struct T_RATE64_4
{
protected:
	Int64 m_val;

public:
	T_RATE64_4()
	{
		m_val = 0;
	}

	T_RATE64_4& operator = (double val)
	{
		m_val = (val + 0.00005) * 10000.0;//+0.000000005表示4舍5入		
		return *this;
	}


	T_RATE64_4& operator = (long val)
	{
		m_val = val ;//	
		return *this;
	}

	double get_double() const
	{
		return (double)(m_val) * 1.0 / 10000.0;
	}

	Int64 get_long() const
	{
		return m_val;
	}
};

struct T_RATE64_5
{
protected:
	Int64 m_val;

public:
	T_RATE64_5()
	{
		m_val = 0;
	}

	T_RATE64_5& operator = (double val)
	{
		m_val = (val + 0.000005) * 100000.0;//+0.000005表示4舍5入
		return *this;
	}


	T_RATE64_5& operator = (long val)
	{
		m_val = val ;//	
		return *this;
	}

	double get_double() const
	{
		return (double)(m_val) * 1.0 / 100000.0;
	}

	Int64 get_long() const
	{
		return m_val;
	}
};

///本结构体用于方便处理用Int64表示的，精确到最多4位小数的浮点类型，大多用于价格字段
struct T_PRICE_4
{
protected:
	Int64 m_val;

public:
	T_PRICE_4()
	{
		m_val = 0;
	}

	T_PRICE_4(const double &val)
	{
		m_val = (val + 0.00005) * 10000 ;//+0.0005表示4舍5入		
	}

	T_PRICE_4& operator = (double val)
	{
		m_val = (val + 0.00005) * 10000 ;//+0.0005表示4舍5入		
		return *this ;
	}	

	double get_double()	 const 
	{		
		return (double)(m_val) * 1.0/ 10000.0 ;
	}

	Int64 get_long() const 
	{
		return m_val;
	}

	bool operator ==(const T_PRICE_4& obj)
	{
		if (this == &obj)
			return true;

		return equal_float(get_double(), obj.get_double(), 5);
	}
};


struct T_PRICE32_4
{
protected:
	Int32 m_val;

public:
	T_PRICE32_4()
	{
		m_val = 0;
	}

	T_PRICE32_4(const double &val)
	{
		m_val = (val + 0.00005) * 10000;//+0.0005表示4舍5入		
	}

	T_PRICE32_4& operator = (double val)
	{
		m_val = (val + 0.00005) * 10000;//+0.0005表示4舍5入		
		return *this;
	}

	double get_double()	 const
	{
		return (double)(m_val) * 1.0 / 10000.0;
	}

	Int64 get_long() const
	{
		return m_val;
	}
};


///本结构体用于方便处理用Int64表示的，精确到最多2位小数的浮点类型，大多用于金额，资金字段
struct T_AMOUNT_2
{
protected:
	Int64 m_val;

public:
	T_AMOUNT_2()
	{
		m_val = 0;
	}

	T_AMOUNT_2& operator = (double val)
	{
		m_val = (val + 0.005) * 100 ;//+0.005表示4舍5入		
		return *this ;
	}

	double get_double()
	{		
		return (double)(m_val) * 1.0 / 100.0 ;
	}

	Int64 get_long()
	{
		return m_val;
	}
};

struct T_AMOUNT_4
{
protected:
	Int64 m_val;

public:
	T_AMOUNT_4()
	{
		m_val = 0;
	}

	T_AMOUNT_4& operator = (double val)
	{
		m_val = (val + 0.00005) * 10000;//+0.005表示4舍5入		
		return *this;
	}

	double get_double()
	{
		return (double)(m_val) * 1.0 / 10000.0;
	}

	Int64 get_long()
	{
		return m_val;
	}
};



///本结构体，8个字节，用于大部分时间戳的值，存储方式为高4个字节为从1970年1月1日0点开始的秒数，低四位是一秒内的纳秒数
struct T_TIMESTAMP
{	
	uInt64 m_val;
	T_TIMESTAMP()
	{
		m_val = 0;
	}

	T_TIMESTAMP& operator = (const T_TIMESTAMP& other)
	{
		m_val = other.m_val;
		return *this;
	}

	T_TIMESTAMP& operator = (const uInt64 val)
	{
		m_val = val;
		return *this;
	}

	bool operator == (const T_TIMESTAMP& other)
	{
		return m_val == other.m_val;
	}

	bool operator > (const T_TIMESTAMP& other)
	{
		return m_val > other.m_val;
	}

	bool operator < (const T_TIMESTAMP& other)
	{
		return m_val < other.m_val;
	}

	bool operator <= (const T_TIMESTAMP& other)
	{
		return m_val <= other.m_val;
	}

	bool operator >= (const T_TIMESTAMP& other)
	{
		return m_val >= other.m_val;
	}

	operator uInt64 ()
	{
		return m_val;
	}

	T_TIMESTAMP(uInt32 tTime, uInt32 uNanoSeconds)
	{		
		set(tTime, uNanoSeconds) ;
	}

	void set(uInt32 tTime, uInt32 uNanoSeconds)
	{		
		char* p = (char*)(&m_val);
		memcpy(p, &uNanoSeconds, 4);
		memcpy(p + 4, &tTime, 4);		
	}

	void set_nsec( uInt32 uNanoSeconds)
	{		
		char* p = (char*)(&m_val);
		memcpy(p, &uNanoSeconds, 4);
	}

	void GetNow()
	{
		char* p = (char*)(&m_val);

#ifndef SHENGLI_WINDOWS
		timeval			tv;		
		//gettimeofday(&tv, NULL);	
		uInt32 uNanoSeconds = tv.tv_usec*1000;
		memcpy(p, &uNanoSeconds, 4);
		memcpy(p + 4, &tv.tv_sec, 4);		
#else
		SYSTEMTIME localTime;
		GetLocalTime(&localTime);//for the milliseconds only
		uInt32 uNanoSeconds = localTime.wMilliseconds*1000000;
		uInt32 uSeconds = _time32(NULL);
		memcpy(p, &uNanoSeconds, 4);
		memcpy(p + 4, &uSeconds, 4);	
#endif
	}

	void GetValues(uInt32& tTime, uInt32& uNanoSeconds)
	{		
		char* p = (char*)(&m_val);
		memcpy(&tTime, p + 4, 4);
		memcpy(&uNanoSeconds, p, 4);
		return;
	}

	void GetValues(struct tm& tmTime, uInt32& uNanoSeconds)
	{
		uInt32 sec;	
		char* p = (char*)(&m_val);
		memcpy(&sec, p + 4, 4);
		memcpy(&uNanoSeconds, p, 4);
#ifdef SHENGLI_WINDOWS
		__time32_t tt32 = (__time32_t)sec;	
		_localtime32_s(&tmTime, &tt32);
		return;
#else
		time_t tt32 = (time_t)sec;
		//localtime_r(&tt32, &tmTime);
		return;
#endif
	}
};

///本结构体用于处理OrderState字段

//#END，TypeStructures
#pragma pack(pop)
