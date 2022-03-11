
#pragma once 
#include <string.h>
#include "eqs_define.h"
//#ifndef SHENGLI_WINDOWS
#include <assert.h>
#include "msg_define_internal.h"
//#endif

///#include "../../include/ees_interfaces/ees_base.h"

#define REM_VERSION							"1.3.0"
#define REM_FULL_VERSION					REM_VERSION#SVN_VERSION
#define REM_TRADE_PROTO_VERSION					5
#define EES_HDS_VERSION							1	

/// #define HDS_CLUSTER_ID_LEN          16



#define ORDER_REJ_GRAMMER_CHECK_SIZE		32 
#define ORDER_REJ_RISK_CHECK_SIZE			96 

#define PRICE_PRECISION 4

#define ORDER_PRICE_LIMIT_BELOW 0.0001
#define ORDER_PRICE_LIMIT_ABOVE 13743895.3471

#pragma pack(push, 1)

namespace rem_adjust_qty
{
	enum adjust_qty 
	{
		add_pos_qty = 0 , 
		decrease_pos_qty = 1 ,
	};
}

namespace rem_adjust_pos_day
{
	enum _
	{
		pos_day_ovn = 0 ,
		pos_day_today = 1,
	};
}
typedef rem_adjust_pos_day::_	T_rem_pos_day; 


///<@brief 消息模式,目前我们的消息可以分为账户类消息, 用户类消息, 还有其他种类的消息
enum msg_style
{
	CLIENT_ID_TYPE = 0,
	USER_TYPE,
	OTHER_TYPE,
};

///<@brief 消息方向(目前不同方向的消息ID是可能相同的)
enum msg_direction
{
	CLIENT_TO_HARDWARE = '0',  ///<交易客户端到硬件(OT)方向的消息
	HARDWARE_TO_CLIENT = '1',      ///<硬件(OT)到交易客户端方向的消息
	HARDWARE_TO_INTERNAL = '2',    ///<硬件(OT)到内部方向的消息
	INTERNAL_TO_HARDWARE = '3',    ///<内部方向到硬件(OT)的消息
	HARDWARE_TO_MARKET = '4',      ///<硬件(OT)到市场方向的消息
	MARKET_TO_HARDWARE = '5',       ///<市场方向到硬件(OT)的消息
	COMM_TO_HARDWARE = '6',		///COMM（OT) 接口配给硬件的消息
	HARDWARE_TO_COMM = '7',		///从硬件收到的COMM接口消息
	HDS_MSG_DIR = '8',			///左右有关HDS的消息类型
	MI_MSG_DIR = '9',             ///MI记录bk的消息类型
	MI_EX_ORDER_ID,			///mi 记录交易所报单的最大值 
	MSG_DIR_END,			///结束位标志，以后任何新的direction方向必须放在这行上面
};


struct cherry_msg_key
{
    cherry_msg_key() {};

    cherry_msg_key(msg_direction direction, u32_sl msg_type)
     : m_direction(direction), m_msg_type(msg_type)
     {
     };

	void reset(msg_direction direction, u32_sl msg_type)
	 {
		 m_direction = direction;
		 m_msg_type  = msg_type;
	 }

    bool operator< (const cherry_msg_key& msg_key) const
	 {
		 if (m_direction > msg_key.m_direction)
		 {
			 return false;
		 }

		 if (m_direction == msg_key.m_direction)
		 {
			if (m_msg_type >= msg_key.m_msg_type)
			{
				return false;
			}
		 }

		 return true;
	}

	msg_direction m_direction;
	u32_sl         m_msg_type;
};



///<@brief 软件层需要的一些额外的信息,目前使用的思路是软CORE的账户线程中需要植入这些信息
///<       主要用于Background Core识别的外部消息(用枚举msg_direction赋值)
struct ees_msg_prefix_head
{
	uInt8    direction; 
	u32_sl  sequence_num;  // 增加一个sequence, 不使用时直接置为0
};


//与ees_trading_data中的t_fut_orders表对应结构体
struct t_fut_orders_data_item
{
	T_OT_CLUSTER_ID ot_cluster_id;
	uInt64 internal_order_id; 
	char trading_date[9];
	uInt64 order_ref_number;
	uInt32 user_id;
	uInt32 order_token;
	T_EXCHANGE_ORDER_TOKEN market_order_token;
	T_EXCHANGE_ORDER_ID market_order_ref_num;
	uInt8 order_type;
	uInt8 buy_sell;
	uInt8 cross_type;
	uInt32 quantity;
	uInt8 sec_type;
	T_SECURITY_CODE symbol;	     
	double price;
	double stop_price;
	uInt32 tif;
	uInt16 firm_id;
	T_FUND_ACCOUNT account_id;   
	uInt8 capacity;
	uInt8 exec_dest;
	uInt8 exec_sub_dest;
	uInt32 min_qty;
	uInt32 max_floor;
	uInt8 force_close_reason;
	uInt8 ISO_indicator;
	uInt8 reserved1;
	uInt8 reserved2;
	uInt64 reserved3;
	uInt8 order_state;
	uInt64 order_accept_time;
	uInt64 order_routed_time;
	uInt64 order_finished_time;
	uInt32 executed_qty;
	uInt32 cancelled_qty;
	uInt32 market_pending_qty;
	uInt32 cancel_pending_qty;
};

//与ees_trading_data中的t_fut_executions表对应结构体
struct t_fut_executions_data_item
{
	T_OT_CLUSTER_ID ot_cluster_id;
	uInt64 internal_order_id; 
	uInt64 internal_exec_id;
	char trading_date[9];
	uInt64 exec_time;
	uInt64 exec_ref_number;
	uInt32 exec_qty;
	double exec_price;
	uInt8 liquitidy_flag;
	double commission_fee;
	T_EXCHANGE_EXEC_ID market_exec_number;
	uInt8 exec_state;
};

//与ees_trading_data中的t_fut_position_rt表对应结构体
struct t_fut_position_rt_data_item
{
	T_FUND_ACCOUNT account_id;
	T_OT_CLUSTER_ID ot_cluster_id;
	uInt8 exchange_id;
	T_SECURITY_CODE symbol;
	uInt8 pos_dir;
	char trading_date[9];
	double init_ovn_qty;
	double init_ovn_margin;
	double cur_ovn_qty;
	double frozen_ovn_qty;
	double ovn_occupied_margin;
	double cur_today_qty;
	double frozen_today_qty;
	double ovn_liquid_pl;
	double today_liquid_pl;
	double ovn_market_pl;
	double today_market_pl;
	double pos_cost;
	double avg_price;
	double pre_settled_price;
	uInt8 security_type;
	double total_commission_fee;
	uInt8   hedge_flag;
};


#pragma pack(pop)

#pragma pack(push, 1)

#include "msg_define_client.h"

//#START，KIWIUM相关

/// KIWI, 软件通知硬件登录成功
struct kwum_stoh_login_success
{
	msg_standard_hdr			m_Header;
	uInt8						m_SessionID;
	uInt8						m_Reserved[3];
	uInt32						m_UserID;
	kwum_stoh_login_success()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = kwum_types::KWUM_STOH_LOGIN_SUCCESS;
		m_Header.m_MsgLen = sizeof(*this);
	}
};

//硬件UM报错， 1089
struct kwum_error_report
{
	kwum_error_report()
	{
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = kwum_types::KWUM_HTOS_SESSION_ERROR_REPORT;
		m_Header.m_MsgLen = sizeof(*this);
	}
	msg_standard_hdr			m_Header;
	uInt8						m_SessionID;
	uInt8						m_Reason;	//0: 不用; 1：版本校验失败; 2：接收到message type不认识; 3：违反：刚连接时第一个包是版本校验消息，第二个包是登录消息的规则。;4下单或者撤单时，使用的user id不是登录的user id
	char						m_Reserved[6];///凑齐8字节

};

/// KIWI 状态报告消息1212
struct kwum_htos_status_report_hdr
{
	msg_standard_hdr			m_Header;	
	uInt8						m_ErrorID;
	uInt8						m_StateID;
	uInt16						m_SessionID;	
	char						m_Reserved1[4];
	uInt8						m_RemoteIP[4];//StateID=21, ARP表上传时，该值无用
	uInt16						m_RemotePort;//StateID=21, ARP表上传时，该值无用
	char						m_Reserved2[10];
	kwum_htos_status_report_hdr()
	{
		//该结构体只会用于接收消息，因此不做初始化也行。
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = kwum_types::KWUM_HTOS_STATUS_REPORT;
		m_Header.m_MsgLen = sizeof(*this);//头部32个字节，当StateID=21时，总长544，其余只有头部32个字节
	}

};

/// KIWI IP黑名单列表消息
struct kwum_htos_black_ip_list_report_hdr
{
	msg_standard_hdr			m_Header;	
	uInt8						m_ErrorID;
	uInt8						m_StateID;
	uInt16						m_SessionID;	
	char						m_Reserved1[4];
	uInt8						m_RemoteIP[4];//StateID=21, ARP表上传时，该值无用
	uInt16						m_RemotePort;//StateID=21, ARP表上传时，该值无用
	char						m_Reserved2[10];
	uInt32						m_black_ip[32];
	kwum_htos_black_ip_list_report_hdr()
	{
		//该结构体只会用于接收消息，因此不做初始化也行。
		memset(this, 0, sizeof(*this));
		m_Header.m_MsgType = kwum_types::KWUM_HTOS_STATUS_REPORT;
		m_Header.m_MsgLen = sizeof(*this);//头部32个字节，当StateID=21时，总长544，其余只有头部32个字节
	}
};

#pragma pack(pop)


#include "msg_define_client.h"
#include "msg_define_rewind.h"
#include "msg_define_internal.h"
#include "msg_define_market.h"
#include "msg_define_hw_cam_conf.h"
#include "msg_define_hds.h"


///  内部使用，不再对外。
struct qmsc_position_query_resp
{
	qmsc_position_query_resp()
	{
		memset(this, 0, sizeof(*this));
	}
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
	full_position_info			m_PositionInfo;
};


//#END，REM响应
//#END，Client查询类和响应类




// BK数据记录
#pragma pack(push, 1)


struct t_secu_rt_order
{
	T_OT_CLUSTER_ID		ot_cluster_id ; 
	T_DATE_STR			trading_date ;
	
	long long  premium_frozen ;
	long long  margin_frozen ;
	long long  fee_frozen ; 
	long long  using_price ; 

	order_snapshot_body order_snapshot;
};

struct t_secu_rt_order_reff_id
{
	T_OT_CLUSTER_ID		ot_cluster_id ; 
	T_DATE_STR			trading_date ;
 
	tmsh_set_order_link_market_reff_id order_reff ;
};

struct t_secu_rt_cxl_order
{
	T_OT_CLUSTER_ID			node_id ; 
	T_DATE_STR				trading_date ;
	T_CLIENT_PROD_INFO		prod_info;
	cxl_req_snapshot_body	cxl_order;
};
//
//struct t_secu_rt_exec
//{
//	T_OT_CLUSTER_ID		ot_cluster_id ; 
//	T_DATE_STR			trading_date ;
//	int				m_side ;
//	T_SECURITY_CODE		m_underlying_symbol ;
//	T_SECURITY_CODE		m_symbol ;
//	
//	long long			premium_real ;
//	long long			margin_real ;
//	long long			fee_real ; 
//
//	exec_snapshot_body	exec_snapshot ;
//};
//
//struct t_secu_rt_position
//{	
//	T_DATE_STR				trading_date ;
//	T_OT_CLUSTER_ID			ot_cluster_id ; 
//	T_CUST_ID		secu_client_id ;
//	T_FUND_ACCOUNT			fund_account ;
//	T_FUND_ACCOUNT_TYPE		fund_account_type ;
//	T_EXCHANGE				exchange_id ;
//	T_EXCHANGE_ACCOUNT		exchange_account ;
//	T_SECURITY_CODE			secu_code ;
//	T_SECU_FULL_TYPE		secu_full_type ;
//	T_POS_DIR				pos_dir ;
//	uInt32					today_qty ;
//	uInt32					ovn_qty ;
//	uInt32					covered_call_pledged_qty ;
//	uInt32					redeemed_qty ;
//	uInt32					covered_locked_qty ;
//	double					last_close_price ;
//	double					avg_price ;
//	double					margin ;
//} ;

//
//struct t_secu_rt_bp
//{	
//	t_secu_rt_bp()
//	{
//		memset(this, 0 , sizeof(t_secu_rt_bp) ) ;
//	}
//
//	T_DATE_STR				trading_date ;
//	T_OT_CLUSTER_ID			ot_cluster_id ; 
//	T_CUST_ID		secu_client_id ;
//	T_FUND_ACCOUNT			fund_account ;
//	T_FUND_ACCOUNT_TYPE		fund_account_type ;
//
//	double					availble_bp ;
//	double					fund_bln ; 
//	double					fund_frz ; 
//	double					fund_ufz ;
//	double					fund_trd_frz ; 
//	double					fund_trd_ufz ; 
//	double					fund_trd_bln ; 
//	double					margin_used ; 
//	double					margin_incl_rlt ; 
//} ;

#pragma pack(pop)


//#Old Structures
//struct comm_risk_status_resp
//{
//	u8_sl	            m_msg_type;			   ///<息类型	211 业务出错反馈
//	u16_sl              m_msg_len;             ///<数据包长度
//	u8_sl               m_reserved1[5];        ///<保留
//	u8_sl               m_module_id;           ///<ID=6
//	u8_sl               m_db_flag;             ///<DB
//	price6              m_reserved2;           ///<保留
//	u64_sl		        m_account_id;		   ///<查询的account id
//	u64_sl		        m_symbol_id;		   ///<查询的aymbol id
//    i8_sl               m_risk_memory[0];
//};

/// account risk memory 通过转化后 risk真实数值结构体
//struct account_risk_real_data
//{
//	//account_risk_real_data& operator= (const account_db_data& data)
//	void convert_from_hw_data(const hw_account_db_data& data, bool kiwi_flag)//kiwiflag为true表示精简risk rule后的risk memory 结构体
//	{
//		m_broker_margin = convert_amount8_to_double(data.m_broker_margin);
//		m_exchange_margin = convert_amount8_to_double(data.m_exchange_margim);
//		m_fee = convert_amount8_to_double(data.m_fee);
//		m_bp = convert_amount8_to_double(data.m_bp);
//
//		m_Rev1 = data.m_Rev1;
//		m_Rev2 = data.m_Rev1;		
//		m_Rev3 = data.m_Rev3;		
//		m_Rev4 = data.m_Rev4;
//
//
//		m_1_limit_val  = data.m_1_limit_val;//没有累计值
//		
//		m_2_limit_val = convert_amount8_to_double(data.m_2_limit_val);//没有累计值
//		
//		//rule 3门限值 在 account_symbol_risk_real_data，没有累计值
//
//		//rule 4门限值 在 account_symbol_risk_real_data，没有累计值		
//
//		m_5_limit_val = convert_rule_5_6_8_60_61_to_double(data.m_5_limit_val);//没有累计值
//
//		m_6_limit_val = convert_rule_5_6_8_60_61_to_double(data.m_6_limit_val);//没有累计值	
//
//		//rule 7门限值 在 account_symbol_risk_real_data，没有累计值
//
//		m_8_limit_val = convert_rule_5_6_8_60_61_to_double(data.m_8_limit_val);//没有累计值
//
//		m_9_limit_val = data.m_9_limit_val;//没有累计值
//
//		m_10_limit_val = data.m_10_limit_val;//没有累计值
//
//		m_11_limit_val = data.m_11_limit_val;
//		m_11_accumulate_val = data.m_11_accumulate_val;
//
//		m_12_limit_val = data.m_12_limit_val;
//		m_12_accumulate_val = data.m_12_accumulate_val;
//
//		m_13_limit_val = convert_amount8_to_double(data.m_13_limit_val);
//		m_13_accumulate_val = convert_amount8_to_double(data.m_13_accumulate_val);
//
//		m_14_limit_val_1 = data.m_14_limit_val_1;
//		m_14_time_val = data.m_14_time_val;
//		m_14_limit_val_2 = data.m_14_limit_val_2;
//		m_14_accumulate_val = data.m_14_accumulate_val;
//
//		m_15_limit_val_1 = data.m_15_limit_val_1;
//		m_15_time_val = data.m_15_limit_val_1;
//		m_15_limit_val_2 = data.m_15_limit_val_1;
//		m_15_accumulate_val = data.m_15_limit_val_1;
//		
//		//rule16没有门限值和累计值
//		
//		m_17_limit_val = data.m_17_limit_val;
//		m_17_accumulate_val = data.m_17_accumulate_val;
//		
//		m_18_limit_val = data.m_18_limit_val;
//		m_18_accumulate_val = data.m_18_accumulate_val;
//
//		m_19_limit_val = data.m_19_limit_val;
//		m_19_accumulate_val = data.m_19_accumulate_val;
//
//		m_20_limit_val = convert_amount8_to_double(data.m_20_limit_val);
//		//20号累加值，需要在外部计算，= 39的累加值+m_broker_margin+m_bp
//
//		m_21_limit_val = convert_amount8_to_double(data.m_21_limit_val);
//		m_21_accumulate_val = convert_amount8_to_double(data.m_21_accumulate_val);
//
//		m_22_limit_val = data.m_22_limit_val;
//		m_22_accumulate_val = data.m_22_accumulate_val;
//
//		//rule 23门限值 在 account_symbol_risk_real_data
//		//rule 23累计值 在 account_symbol_risk_real_data
//
//		m_24_limit_val_1 = data.m_24_limit_val_1;
//		m_24_time_val = data.m_24_time_val;
//		m_24_limit_val_2 = data.m_24_limit_val_2;
//		m_24_accumulate_val = data.m_24_accumulate_val;
//
//		m_25_limit_val_1 = data.m_25_limit_val_1;
//		m_25_time_val = data.m_25_time_val;
//		m_25_limit_val_2 = data.m_25_limit_val_2;
//		m_25_accumulate_val = data.m_25_accumulate_val;
//
//		if (kiwi_flag)
//		{
//			//rule 26已经取消
//			m_26_limit_val_1 = 0;
//			m_26_accumulate_val = 0;
//			m_26_limit_val_2 = 0;
//		}
//		else
//		{
//			m_26_limit_val_1 = data.m_26_limit_val_1;
//			m_26_accumulate_val = data.m_26_accumulate_val;
//			m_26_limit_val_2 = data.m_26_limit_val_2;
//		}
//
//		m_27_limit_val = data.m_27_limit_val;
//		//m_27_accumulate_val = data.m_41_accumulate_val + data.m_42_accumulate_val;//27累计=41累计+42累计
//
//		m_28_limit_val = convert_amount8_to_double(data.m_28_limit_val);
//		//m_28_accumulate_val = data.m_43_accumulate_val + data.m_44_accumulate_val;//28累计=43累计+44累计
//
//		if (kiwi_flag)
//		{
//			//rule59已取消, 原值的位置放29的值,
//			m_29_limit_val = data.m_59_limit_val;
//			m_29_accumulate_val = data.m_59_accumulate_val;
//		}
//		else
//		{
//			m_29_limit_val = data.m_29_limit_val;
//			m_29_accumulate_val = data.m_29_accumulate_val;
//		}
//
//		m_30_limit_val = convert_amount8_to_double(data.m_30_limit_val);
//		m_30_accumulate_val = convert_amount8_to_double(data.m_30_accumulate_val);
//
//		m_31_limit_val = data.m_31_limit_val;
//		m_31_accumulate_val = data.m_31_accumulate_val;
//
//		m_32_limit_val = data.m_32_limit_val;
//		m_32_accumulate_val = data.m_32_accumulate_val;
//
//		if (kiwi_flag)
//		{
//			//rule 26已经取消，原位置放rule33的值
//			m_33_limit_val = data.m_26_limit_val_1;
//			m_33_accumulate_val = data.m_26_accumulate_val;
//		}
//		else
//		{
//			m_33_limit_val = data.m_33_limit_val;
//			m_33_accumulate_val = data.m_33_accumulate_val;
//		}
//
//		m_34_limit_val_2 = data.m_34_limit_val_2;
//		m_34_time_val = data.m_34_time_val;
//		m_34_limit_val_1 = data.m_34_limit_val_1;
//		m_34_accumulate_val = data.m_34_accumulate_val;
//
//		m_35_limit_val_2 = data.m_35_limit_val_2;
//		m_35_time_val = data.m_35_time_val;
//		m_35_limit_val_1 = data.m_35_limit_val_1;
//		m_35_accumulate_val = data.m_35_accumulate_val;
//
//		m_36_limit_val_1 = data.m_36_limit_val_1;
//		m_36_time_val = data.m_36_time_val;
//		m_36_limit_val_2 = data.m_36_limit_val_2;
//		m_36_accumulate_val = data.m_36_accumulate_val;
//
//		m_37_limit_val_1 = data.m_37_limit_val_1;
//		m_37_time_val = data.m_37_time_val;
//		m_37_limit_val_2 = data.m_37_limit_val_2;
//		m_37_accumulate_val = data.m_37_accumulate_val;
//
//		m_38_limit_val = convert_amount8_to_double(data.m_38_limit_val);
//		m_38_accumulate_val = convert_price6_to_double(data.m_38_accumulate_val) - m_fee;//38查询所得的累计值，未扣手续费
//
//		//rule39，门限值和累加值，在account_risk_real_data_mpl中
//
//		m_40_limit_val = convert_amount8_to_double(data.m_40_limit_val);
//		//40的累计值，= 38 + 39的累计值
//
//		m_41_limit_val = data.m_41_limit_val;
//		m_41_accumulate_val = data.m_41_accumulate_val;
//
//		m_42_limit_val = data.m_42_limit_val;
//		m_42_accumulate_val = data.m_42_accumulate_val;
//
//		m_43_limit_val = convert_amount8_to_double(data.m_43_limit_val);
//		m_43_accumulate_val = convert_amount8_to_double(data.m_43_accumulate_val);
//
//		m_44_limit_val = convert_amount8_to_double(data.m_44_limit_val);
//		m_44_accumulate_val = convert_amount8_to_double(data.m_44_accumulate_val);
//
//		//45的门限值和累计值，在account_symbol_real_data_resp中
//
//		//46的门限值和累计值，在account_symbol_real_data_resp中
//
//		//47的门限值和累计值，在account_symbol_real_data_resp中
//
//		//48的门限值和累计值，在account_symbol_real_data_resp中
//
//		//49的门限值和累计值，在account_symbol_real_data_resp中
//
//		//50的门限值和累计值，在account_symbol_real_data_resp中
//
//		//51的门限值和累计值，在account_symbol_real_data_resp中
//
//		//52的门限值和累计值，在account_symbol_real_data_resp中
//
//		//53的门限值和累计值，在account_symbol_real_data_resp中
//		
//		m_54_limit_val = data.m_54_limit_val;
//		m_54_accumulate_val = data.m_54_accumulate_val;//需要覆盖为56+57
//
//		m_55_limit_val = convert_amount8_to_double(data.m_55_limit_val);
//		m_55_accumulate_val = convert_amount8_to_double(data.m_55_accumulate_val);//需要覆盖为58+59
//
//		m_56_limit_val = data.m_56_limit_val;
//		m_56_accumulate_val = data.m_56_accumulate_val;
//
//		m_57_limit_val = data.m_57_limit_val;
//		m_57_accumulate_val = data.m_57_accumulate_val;		
//
//		m_58_limit_val = convert_amount8_to_double(data.m_58_limit_val);
//		m_58_accumulate_val = convert_amount8_to_double(data.m_58_accumulate_val);
//
//		if (kiwi_flag)
//		{
//			//rule 59已经取消
//			m_59_limit_val = 0.0;
//			m_59_accumulate_val = 0.0;
//		}
//		else
//		{
//			m_59_limit_val = convert_amount8_to_double(data.m_59_limit_val);
//			m_59_accumulate_val = convert_amount8_to_double(data.m_59_accumulate_val);
//		}
//
//		m_60_limit_val = convert_rule_5_6_8_60_61_to_double(data.m_60_limit_val);
//		//60累计值需要计算
//
//		m_61_limit_val = convert_rule_5_6_8_60_61_to_double(data.m_61_limit_val);
//		//61累计值需要计算
//
//		m_62_limit_val_1 = data.m_62_limit_val_1;
//		m_62_time_val = data.m_62_limit_val_1;
//		m_62_limit_val_2 = data.m_62_limit_val_1;
//		m_62_accumulate_val = data.m_62_limit_val_1;
//
//		m_63_limit_val_1 = data.m_63_limit_val_1;
//		m_63_time_val = data.m_63_limit_val_1;
//		m_63_limit_val_2 = data.m_63_limit_val_1;
//		m_63_accumulate_val = data.m_63_limit_val_1;		
//
//		//return *this;
//	}
//
//	double				m_43_limit_val;		
//	double				m_43_accumulate_val;
//	double				m_38_limit_val;
//	double				m_38_accumulate_val;
//	i64_sl				m_41_limit_val;
//	i64_sl				m_41_accumulate_val;
//	double				m_44_limit_val;
//	double				m_44_accumulate_val;
//	i64_sl				m_29_limit_val;
//	i64_sl				m_29_accumulate_val;
//	i64_sl				m_42_limit_val;
//	i64_sl				m_42_accumulate_val;
//	i64_sl				m_54_limit_val;
//	i64_sl				m_54_accumulate_val;
//	double				m_30_limit_val;
//	double				m_30_accumulate_val;
//	i64_sl				m_56_limit_val;
//	i64_sl				m_56_accumulate_val;
//	double				m_55_limit_val;
//	double				m_55_accumulate_val;
//	double				m_58_limit_val;
//	double				m_58_accumulate_val;
//	i64_sl				m_57_limit_val;
//	i64_sl				m_57_accumulate_val;
//	i64_sl				m_31_limit_val;
//	i64_sl				m_31_accumulate_val;
//	double				m_59_limit_val;
//	double				m_59_accumulate_val;
//	i64_sl				m_35_limit_val_2;
//	i64_sl				m_35_time_val;
//	i64_sl				m_35_limit_val_1;
//	i64_sl				m_35_accumulate_val;
//	i64_sl				m_34_limit_val_2;
//	i64_sl				m_34_time_val;
//	i64_sl				m_34_limit_val_1;
//	i64_sl				m_34_accumulate_val;
//	double				m_broker_margin;
//	double				m_exchange_margin;
//	double				m_fee;
//	double				m_bp;
//	double				m_13_limit_val;
//	double				m_13_accumulate_val;
//	double				m_21_limit_val;
//	double				m_21_accumulate_val;
//	i64_sl				m_14_limit_val_1;
//	i64_sl				m_14_time_val;
//	i64_sl				m_14_limit_val_2;
//	i64_sl				m_14_accumulate_val;
//	i64_sl				m_15_limit_val_1;
//	i64_sl				m_15_time_val;
//	i64_sl				m_15_limit_val_2;
//	i64_sl				m_15_accumulate_val;
//	i64_sl				m_62_limit_val_1;
//	i64_sl				m_62_time_val;
//	i64_sl				m_62_limit_val_2;
//	i64_sl				m_62_accumulate_val;
//	i64_sl				m_63_limit_val_1;
//	i64_sl				m_63_time_val;
//	i64_sl				m_63_limit_val_2;
//	i64_sl				m_63_accumulate_val;
//	i64_sl				m_11_limit_val;
//	i64_sl				m_11_accumulate_val;
//	i64_sl				m_32_limit_val;
//	i64_sl				m_32_accumulate_val;
//	i64_sl				m_17_limit_val;
//	i64_sl				m_17_accumulate_val;
//	i64_sl				m_12_limit_val;
//	i64_sl				m_12_accumulate_val;
//	i64_sl				m_19_limit_val;
//	i64_sl				m_19_accumulate_val;
//	i64_sl				m_18_limit_val;
//	i64_sl				m_18_accumulate_val;
//	double				m_5_limit_val;
//	i64_sl				m_Rev1;
//	i64_sl				m_Rev2;
//	double				m_2_limit_val;
//	i64_sl				m_9_limit_val;
//	double				m_8_limit_val;
//	i64_sl				m_Rev3;
//	double				m_6_limit_val;
//	double				m_61_limit_val;
//	double				m_60_limit_val;
//	i64_sl				m_1_limit_val;
//	i64_sl				m_10_limit_val;
//	double				m_20_limit_val;
//	double				m_40_limit_val;
//	double				m_28_limit_val;
//	i64_sl				m_27_limit_val;
//	i64_sl				m_24_limit_val_1;
//	i64_sl				m_24_time_val;
//	i64_sl				m_24_limit_val_2;
//	i64_sl				m_24_accumulate_val;
//	i64_sl				m_25_limit_val_1;
//	i64_sl				m_25_time_val;
//	i64_sl				m_25_limit_val_2;
//	i64_sl				m_25_accumulate_val;
//	i64_sl				m_26_limit_val_1;
//	i64_sl				m_26_accumulate_val;
//	i64_sl				m_22_limit_val;
//	i64_sl				m_22_accumulate_val;
//	i64_sl				m_33_limit_val;
//	i64_sl				m_33_accumulate_val;
//	i64_sl				m_26_limit_val_2;
//	i64_sl				m_Rev4;
//	i64_sl				m_36_limit_val_1;
//	i64_sl				m_36_time_val;
//	i64_sl				m_36_limit_val_2;
//	i64_sl				m_36_accumulate_val;
//	i64_sl				m_37_limit_val_1;
//	i64_sl				m_37_time_val;
//	i64_sl				m_37_limit_val_2;
//	i64_sl				m_37_accumulate_val;
//};


//DBFLAG = 6, 专门导出market pl相关的数据
//struct account_risk_real_data_mpl
//{
//	account_risk_real_data_mpl& operator= (const hw_sym_acc_mpl_data& data)
//	{
//		m_39_limit_val = convert_amount8_to_double(data.m_rule39_value);
//		m_39_accumulate_val = convert_price6_to_double(data.m_short_position) + convert_price6_to_double(data.m_long_position);
//		return *this;
//	}
//	double m_39_limit_val;
//	double m_39_accumulate_val;
//};

//struct account_risk_real_data_req
//{
//	account_risk_real_data_req()
//	{
//		memset(this, 0, sizeof(account_risk_real_data_req));
//		m_msg_type = CHERRY_CLIENT_TO_SOFTWARE_QUERY_ACCOUNT_RISK_DATA ;
//	}
//	uInt8		m_msg_type ;	///消息类型=82, CHERRY_CLIENT_TO_SOFTWARE_QUERY_ACCOUNT_RISK_DATA
//	uInt32		m_user_id ;		///< 	登录用户的ID
//	AccountID	m_account_id ;	///< 	账户ID
//	uInt32		m_request_id;	///<	查询请求ID，请从1开始编号，响应中返回同样的值。
//	char        m_reserved[7];							///用于对齐8个字节
//};

//struct account_risk_real_data_resp
//{
//	account_risk_real_data_resp()
//	{
//		m_msg_type = QUERY_ACCOUNT_RISK_DATA_RESP_MSG_ID;
//	}
//	uInt8		m_msg_type;				///消息类型=82
//	AccountID	m_account_id ;	///< 	账户ID
//	uInt32		m_user_id ;		///< 	登录用户的ID
//	uInt32		m_request_id;	///<	查询请求ID，请从1开始编号，响应中返回同样的值。
//	uInt64		m_last_update_time;	///<	最后更新的时间戳，微秒单位，取当日0：00开始的微秒数
//	account_risk_real_data	m_account_risk_real_data;
//	//新增market pl相关的值，及几个新增的累加值
//	account_risk_real_data_mpl m_account_mpl_data;
//	double m_20_accumulate_val;
//	i64_sl m_27_accumulate_val;
//	double m_28_accumulate_val;	
//	double m_40_accumulate_val;
//	double m_60_accumulate_val;
//	double m_61_accumulate_val;
//	char   m_reserved[7];							///用于对齐8个字节
//	// HPC需要计算一下获取部分相关信息, SPC和BGC无需调用此函数
//	void calc()
//	{
//		m_20_accumulate_val = m_account_mpl_data.m_39_accumulate_val + m_account_risk_real_data.m_bp + m_account_risk_real_data.m_broker_margin;
//		m_27_accumulate_val = m_account_risk_real_data.m_41_accumulate_val + m_account_risk_real_data.m_42_accumulate_val;//27累计=41累计+42累计
//		m_28_accumulate_val = m_account_risk_real_data.m_43_accumulate_val + m_account_risk_real_data.m_44_accumulate_val;//28累计=43累计+44累计
//		m_40_accumulate_val = m_account_risk_real_data.m_38_accumulate_val + m_account_mpl_data.m_39_accumulate_val;
//		m_account_risk_real_data.m_54_accumulate_val = m_account_risk_real_data.m_56_accumulate_val + m_account_risk_real_data.m_57_accumulate_val;
//		m_account_risk_real_data.m_55_accumulate_val = m_account_risk_real_data.m_58_accumulate_val + m_account_risk_real_data.m_59_accumulate_val;
//		m_60_accumulate_val = m_account_risk_real_data.m_broker_margin / m_20_accumulate_val;
//		m_61_accumulate_val = m_account_risk_real_data.m_exchange_margin / m_20_accumulate_val;
//	}
//};

/// account symbol risk memory 通过转化后 risk真实数值结构体
/// 2015年8月第四期修改，多数值分开了投机套利标志，本协议暂时不动，只传输投机的值
/// 日后可以考虑将reserved字段分出一个字节来存放投机套利标志，请求同理
//struct account_symbol_risk_real_data
//{
//	account_symbol_risk_real_data& operator= (const hw_acc_sym_db_data& data)
//	{
//		m_onp_short_pos_settle_price = convert_price6_to_double(data.m_onp_short_pos_settle_price);
//		m_onp_long_pos_settle_price  = convert_price6_to_double(data.m_onp_long_pos_settle_price);
//		m_onp_long_pos_quantity      = data.m_onp_long_pos_qty_speculation;//暂时不动和客户端的协议，只传输投机的值
//		m_onp_long_pos_margin        = 0.0;//convert_amount8_to_double(data.m_onp_long_pos_margin);//暂时不动和客户端的协议，只传输投机的值
//		m_open_fee_rate_2            = convert_amount8_to_double(data.m_open_fee_rate_long_speculation.m_fee_rate_2);
//		m_open_fee_rate_1            = convert_amount_fee_rate_to_double(data.m_open_fee_rate_long_speculation.m_fee_rate_1);
//		m_onp_short_pos_quantity     = data.m_onp_short_pos_qty_speculation;//暂时不动和客户端的协议，只传输投机的值
//		m_onp_short_pos_margin       = 0.0;//convert_amount8_to_double(data.m_onp_short_pos_margin);//暂时不动和客户端的协议，只传输投机的值
//		m_broker_margin_rate         = convert_cfg_fraction_to_double(data.m_margin_rate[2].m_long_margin_rate);//2为投机
//		m_fee_caculate_mode          = 0;
//		m_cover_fee_rate_2           = convert_amount8_to_double(data.m_close_today_fee_rate_long_speculation.m_fee_rate_2);
//		m_cover_fee_rate_1           = convert_amount_fee_rate_to_double(data.m_close_today_fee_rate_long_speculation.m_fee_rate_1);
//		m_snpl                       = convert_amount8_to_double(data.m_snpl);
//		m_bnpl                       = convert_amount8_to_double(data.m_bnpl);
//		m_fee                        = convert_amount8_to_double(data.m_fee);
//		m_onp_short_pos_qty          = data.m_onp_short_pos_qty_speculation;//暂时不动和客户端的协议，只传输投机的值
//		m_today_short_pos_qty        = data.m_today_short_pos_qty_speculation;//暂时不动和客户端的协议，只传输投机的值
//		m_onp_long_pos_qty           = data.m_onp_long_pos_qty_speculation;//暂时不动和客户端的协议，只传输投机的值
//		m_today_long_pos_qty         = data.m_today_long_pos_qty_speculation;//暂时不动和客户端的协议，只传输投机的值
//		m_Rev                        = data.m_rev1;
//
//		m_3_limit_val                = convert_price6_to_double(data.m_3_limit_val);//没有累计值
//		m_4_limit_val                = convert_price6_to_double(data.m_4_limit_val);//没有累计值
//		m_7_limit_val                = convert_price6_to_double(data.m_7_limit_val);//没有累计值
//		//rule16没有累加值和门限值
//		m_23_limit_val               = data.m_23_limit_val;
//		m_23_accumulate_val          = data.m_23_accumulate_val;
//
//		m_45_limit_val               = data.m_45_limit_val;
//
//		m_46_limit_val               = data.m_46_limit_val;
//
//		m_47_limit_val               = convert_amount8_to_double(data.m_47_limit_val);
//
//		m_48_limit_val               = convert_amount8_to_double(data.m_48_limit_val);
//
//		m_49_limit_val               = data.m_49_limit_val;
//
//		m_50_limit_val               = convert_amount8_to_double(data.m_50_limit_val);
//
//		m_51_limit_val               = convert_amount8_to_double(data.m_51_limit_val);
//
//		m_52_limit_val               = convert_amount8_to_double(data.m_52_limit_val);
//
//		m_53_limit_val               = convert_amount8_to_double(data.m_53_limit_val);
//				
//
//		return *this;
//	}
//
//	double	            m_onp_short_pos_settle_price;
//	double	            m_onp_long_pos_settle_price;
//	i64_sl	            m_onp_long_pos_quantity;
//	double	            m_onp_long_pos_margin;
//	double				m_open_fee_rate_2;
//	double				m_open_fee_rate_1;
//	i64_sl				m_onp_short_pos_quantity;
//	double				m_onp_short_pos_margin;
//	double				m_broker_margin_rate;
//	i64_sl				m_fee_caculate_mode;
//	double				m_cover_fee_rate_2;
//	double				m_cover_fee_rate_1;
//	double				m_53_limit_val;
//	double				m_fee;
//	i32_sl				m_onp_short_pos_qty;
//	i32_sl				m_today_short_pos_qty;
//	i32_sl				m_onp_long_pos_qty;
//	i32_sl				m_today_long_pos_qty;
//	i64_sl				m_46_limit_val;
//	double				m_snpl;				///任意合约空仓累计净收益(snpl)
//	double				m_45_limit_val;
//	double				m_bnpl;				///任意合约多仓累计净收益(snpl)
//	double				m_48_limit_val;
//	double				m_4_limit_val;
//	double				m_47_limit_val;
//	double				m_3_limit_val;
//	double				m_52_limit_val;
//	double				m_51_limit_val;
//	double				m_50_limit_val;
//	i64_sl				m_49_limit_val;
//	i64_sl				m_Rev;
//	double				m_7_limit_val;
//	i64_sl				m_23_limit_val;
//	i64_sl				m_23_accumulate_val;
//};

/// symbol account risk memory 通过转化后 risk真实数值结构体