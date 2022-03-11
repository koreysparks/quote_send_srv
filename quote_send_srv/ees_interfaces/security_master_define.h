#pragma  once 

#include <list>
using namespace std;

#include "fix_str.h"
#include "ees_define.h"	

struct secu_stock_instrument
{
	secu_stock_instrument()
	{
		memset(this, 0, sizeof(*this));
	}

	T_EXCHANGE			m_exchange_id; ///<  TINYINT(4) NULL DEFAULT NULL,
	T_SECURITY_CODE		m_secu_code; ///< VARCHAR(6) NOT NULL,
	fix_str<17>			m_isin; ///<  VARCHAR(16) NULL DEFAULT NULL,
	T_time				m_udp_time; ///<  TIME NULL DEFAULT NULL,
	T_SECURITY_NAME		m_secu_name; ///<  VARCHAR(16) NULL DEFAULT NULL,
	T_SECURITY_NAME		m_en_name; ///< VARCHAR(16) NULL DEFAULT NULL,
	T_SECURITY_CODE		m_base_secu_code; ///< VARCHAR(6) NULL DEFAULT NULL,
	fix_str<5>			m_mkt_type; ///< VARCHAR(4) NULL DEFAULT NULL,
	fix_str<7>			m_sse_sec_type; ///< VARCHAR(6) NULL DEFAULT NULL,
	fix_str<4>			m_sse_sec_sub_type; ///< VARCHAR(3) NULL DEFAULT NULL,
	fix_str<4>			m_currency; ///< VARCHAR(3) NULL DEFAULT NULL,
	double				m_par_value; ///< DECIMAL(15, 3) NULL DEFAULT NULL,
	T_date				m_last_date;			///< DATE NULL DEFAULT NULL,
	T_date				m_open_date; ///< DATE NULL DEFAULT NULL,
	unsigned short		m_mkt_set; ///< SMALLINT(6) NULL DEFAULT NULL,
	unsigned int		m_buy_min_qty; ///< INT(10) UNSIGNED NULL DEFAULT NULL,
	unsigned int		m_sell_min_qty; ///< INT(10) UNSIGNED NULL DEFAULT NULL,
	unsigned int		m_min_order_qty; ///< INT(10) UNSIGNED NULL DEFAULT NULL,
	unsigned int		m_max_order_qty; ///< INT(10) UNSIGNED NULL DEFAULT NULL,
	double				m_pre_close_price; ///< DECIMAL(11, 3) UNSIGNED NULL DEFAULT NULL,
	double				m_min_tick_price; ///< DECIMAL(11, 3) UNSIGNED NULL DEFAULT NULL,
	char				m_limit_type; ///< CHAR(1) NULL DEFAULT NULL,
	double				m_up_limit_price; ///< DECIMAL(11, 3) NULL DEFAULT NULL,
	double				m_low_limit_price; ///< DECIMAL(11, 3) NULL DEFAULT NULL,
	double				m_ex_rights_rate; ///< DECIMAL(11, 6) NULL DEFAULT NULL,
	double				m_ex_right_amt; ///< DECIMAL(11, 6) NULL DEFAULT NULL,
	char				m_is_financing; ///< CHAR(1) NULL DEFAULT NULL,
	char				m_is_lending; ///< CHAR(1) NULL DEFAULT NULL,
	fix_str<24>			m_stat; ///< VARCHAR(20) NULL DEFAULT NULL,
	fix_str<56>			m_memo; ///< VARCHAR(50) NULL DEFAULT NULL 
	
	int					m_internal_status;

	// 下面的几个属性，是我们自己内部需要的。
														  
	T_SECU_ADDITIONAL_FLAG	m_addi_flag;	///< 是否允许 ETF 申购与赎回
	T_SECU_FULL_TYPE	m_secu_full_type; ///< TINYINT(4) NULL DEFAULT NULL,
	int				m_is_opt_underlying; 
	T_COVER_TODAY_FLAG	m_cover_today_flag;
	int					m_volume_multiple;

	bool	is_risk_symbol()
	{
		// 这个函数，以后可能需要根据西安同事开发的证券进行修改。
		 // TODO 
		if (m_exchange_id == rem_exchange::EXCH_SHH)
		{
			return m_stat[3] == 'S' || m_stat[3] == 'T' || m_stat[3] == 'P' ;
		}
		if (m_exchange_id == rem_exchange::EXCH_SHZ)
		{
			// dodo 未完成 。	
		}
		return false; 
	}
};


struct secu_stock_etf_component
{
	secu_stock_etf_component()
	{
		memset(this, 0, sizeof(*this));
	}
	T_EXCHANGE			m_exchange_id; ///<  TINYINT(4) NULL DEFAULT NULL,
	T_SECURITY_CODE		m_secu_code; ///< VARCHAR(6) NOT NULL,

	T_EXCHANGE			m_underlying_exchange_id; ///<  TINYINT(4) NULL DEFAULT NULL,
	T_SECURITY_CODE		m_underlying_secu_code; ///< VARCHAR(6) NOT NULL,

	REM_SUBSTITUTE_FLAG	 m_subsitiute_flag; ///< 现金替代标记
	unsigned int 		 m_share;			///< 成份证券数量
	double				m_premium_ratio;	///< 溢价比例
	double				m_discount_ratio;	///< 折价比例

	T_PRICE_4			m_creation_cash_substiture;		///< 申购替代金额
	T_PRICE_4			m_redemption_cash_substitute;	///< 赎回替代金额

};

struct secu_option_instrument
{
	secu_option_instrument()
	{
		memset(this, 0, sizeof(*this)) ;		
	}

	T_SECURITY_CODE		m_secu_code ;
	T_EXCHANGE			m_exchange_id ;
	T_SECU_FULL_TYPE	m_secu_full_type ;
	T_OPT_CONTRACT_ID	m_contract_id ;
	T_OPT_NAME			m_contract_symbol ;
	T_EXCHANGE			m_underlying_exchange_id ;
	T_SECURITY_CODE		m_underlying_secu_code ;
	fix_str<16>			m_underlying_symbol ;	// 数据库里面是u8编码，最长可以是 12位长度。
	fix_str<8>			m_underlying_type;
	T_SECU_FULL_TYPE	m_underlying_secu_full_type;
	char				m_option_type ;
	char				m_put_or_call ;
	long				m_vol_multipler ;
	double				m_strike_price ;
	T_DATE_STR			m_start_date ;
	T_DATE_STR			m_end_date ;
	T_DATE_STR			m_exercise_date ;
	T_DATE_STR			m_delivery_date ;
	T_DATE_STR			m_expire_date ;
	char				m_update_version ;
	long				m_total_long_position ;
	double				m_security_close_px ;
	double				m_settl_price ;
	double				m_underlying_close_px ;
	char				m_price_limit_type ;
	double				m_daily_price_up_limit ;
	double				m_daily_price_down_limit ;
	double				m_margin_unit ;
	double				m_margin_ratio_param1 ;
	double				m_margin_ratio_param2 ;
	long				m_round_lot ;
	long				m_lmt_ord_min_floor ;
	long				m_lmt_ord_max_floor ;
	long				m_mkt_ord_min_floor ;
	long				m_mkt_ord_max_floor ;
	double				m_tick_size ;
	fix_str<16>			m_security_status_flag ;
	fix_str<16>			m_auto_split_da ;

	bool is_call()
	{
		return m_put_or_call == 'C';
	}

	bool is_put()
	{
		return m_put_or_call == 'P';
	}

};



