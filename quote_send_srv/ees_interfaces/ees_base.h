#pragma once

#include "shengli_tool/shengli_define.h"
#include "shengli_tool/date_time.h"
#include "shengli_tool/lock.h"
#include "i_performance.h"	

using namespace SHENGLI::TOOLS;

#include "msg_define.h"

/// 2014-08-12 以涨跌停的价格报价不做限制，在目前的价格上再上下浮动15%即可, 在行情模块中存储为原有的值, 只是向外报或者外部获取时增减
#define QUOTE_LIMIT_PRICE_EXTENTED_RATE (0.0)

/// @brief 从本地配置文件 "ees_db_entry.xml" 读取数据库入口地址，ot还需要读取ot_id, eqs需要读取eqs_id
/// @param db_entry：输出数据库入口地址
/// @param ot_id：输出ot的id，目前只有ot模块关心，无论主动模式还是被动模式，如果配置文件中没有此节点，那么返回空字符串
/// @param ot_id：输出eqs的id，目前只有eqs模块关心，如果配置文件中没有此节点，那么返回空字符串
/// @return： true：成功读取。false：文件不存在、或者格式不正确
bool load_db_entry(string& db_entry, string& back_db_entry);

void set_max_order_id( u64_sl max_id );
u64_sl get_max_order_id();
u64_sl get_next_max_order_id() ;

void set_max_exec_id( u64_sl max_id ) ;
u64_sl get_max_exec_id();
u64_sl get_next_max_exec_id();


///2014/08/12, 为了和硬件一致，以下所有get_nano_seconds_of_day函数的返回值，改为从1970-1-1 0点开始的秒数+纳秒数，高4位为一秒内的纳秒数，低4位为秒数，相当于time_t的值
///<取从1970-1-1 00:00:00开始的纳秒数
u64_sl get_nano_seconds_of_day();


///<获取order_refer_num在第bit_loc位上值,bit_loc取值范围0-63
u8_sl get_bit(u64_sl order_refer_num, u8_sl bit_loc);

///<设置order_refer_num在第bit_loc位上值为1
u64_sl set_bit_to_one(u64_sl order_refer_num, u8_sl bit_loc);

///<设置order_refer_num在第bit_loc位上值为0
u64_sl set_bit_to_zero(u64_sl order_refer_num, u8_sl bit_loc);

//获取一个格式为yyyyMMdd-HH:mm:ss.ffffff的当前时间字符串，精确至微秒 
string get_cur_time_str();


i64_sl get_cl_ord_key(u32_sl user_id, u32_sl cl_ord_token);

void from_cl_ord_key(i64_sl order_key, u32_sl& user_id, u32_sl& cl_ord_token);

///<调整命令行的空格，提高兼容性
string get_adjust_cmd(lpcstr_sl ch_cmd);

const char * get_str_exchange_id( T_EXCHANGE ees_change_id );
T_EXCHANGE get_ees_exchange_id( const char*  exchange_id );


double normalize_fee(double exec_fee);//将手续费以四舍五入的方式，整到分一级，这里只处理成交后真正扣除的，冻结、解冻的不用这个函数了。

void get_trade_session_id(int id1, int id2, const char* p_str, T_SESSION_ID& buf);


/// 用于risk memory相关值的转换
template<long long mutipler = 1> class multi_amount
{
public:
	unsigned long long m_val;  /// store as memory

public:
	multi_amount<mutipler>& operator = (double val)
	{
		long long l_val = val*mutipler;
		memcpy(&m_val, &l_val, sizeof(m_val));
		return *this;
	}

	multi_amount<mutipler>& operator = (long long val)
	{
		memcpy(&m_val, &val, sizeof(m_val));
		return *this;
	}

	double get_real_value()
	{
		long long l_val;
		memcpy(&l_val, &m_val, sizeof(m_val));
		return l_val * 1.0 / mutipler;
	}
};

#ifdef TEST_PERFORMANCE 
	bool init_performance() ;

	performance_item * get_next_send_performance();
	bool add_send_split_performance_item() ;
	bool write_send_performance_info()  ;

	performance_item * get_next_resp_performance();
	bool add_resp_split_performance_item() ;
	bool write_resp_performance_info()  ;

#endif

///将系统的一个8字节数字，例如硬件给出的timestamp，转换成struct tm和一秒钟内的纳秒数
void convert_from_timestamp(u64_sl timestamp, tm& tm_result, u32_sl& nano_sec);
///将struct tm和一秒钟内的纳秒数,转换成系统的一个8字节数字,例如硬件给出的timestamp
u64_sl convert_to_timestamp(tm& tm_struct, const u32_sl nano_sec);
///将当前时间,转换成系统的一个8字节数字,例如硬件给出的timestamp
u64_sl convert_now_to_timestamp();

///将一个时分秒格式"08:30:24"转换成系统的一个8字节数字,例如硬件给出的timestamp
typedef char  TimeFormatType[9];	
u64_sl convert_timestr_to_timestamp(TimeFormatType strtime);

////////////////////////////下面几个函数是RSA 2048加密算法//////////////////////////////////////

/// 使用RSA 2048机密算法对text进行加密，输出到buffer
int get_ciphertext(const char* key, const char* text, int text_len, char* buffer, int len);

/// 根据buffer内存数据加密
int rsa_encrypt(const char* key, int in_len, const char* strData, int data_len, char* outOut);

/// base64
int base64_encode(const char* pSrc, int nSrcLen, char* pDst, int nDstLen);


///<性能记录相关的时间
///本类不加锁处理，避免对性能造成过多影响，调用者需要保证线程安全性
class performance_counter
{
#define PERF_COUNTER_STEP	14
#define	PERF_COUNTER_NUMBER	20000
#define STEP_DESC_LEN 100
	typedef i64_sl usec_matrix[PERF_COUNTER_STEP][PERF_COUNTER_NUMBER];
	typedef i64_sl start_usec_arr[PERF_COUNTER_NUMBER];
	typedef char step_desc_arr[PERF_COUNTER_STEP][STEP_DESC_LEN];
public:
	performance_counter();
	~performance_counter();
	void set_ctoh_start_time();
	void set_htoc_start_time();
	void set_itoh_start_time();
	void set_htoi_start_time();
	void set_mtoh_start_time();
	void set_htom_start_time();
	void update_ctoh_perf(int step_idx);
	void update_htoc_perf(int step_idx);
	void update_itoh_perf(int step_idx);
	void update_htoi_perf(int step_idx);
	void update_mtoh_perf(int step_idx);
	void update_htom_perf(int step_idx);
	void increase_ctoh_counter_idx();
	void increase_htoc_counter_idx();
	void increase_itoh_counter_idx();
	void increase_htoi_counter_idx();
	void increase_mtoh_counter_idx();
	void increase_htom_counter_idx();

	void flush_perf_count();

	static i64_sl get_current_microseconds();

private:
	usec_matrix m_htoc_counter;
	start_usec_arr m_htoc_start_time;
	usec_matrix m_htoi_counter;
	start_usec_arr m_htoi_start_time;
	usec_matrix m_htom_counter;
	start_usec_arr m_htom_start_time;
	
	int m_htoc_counter_idx;
	int m_htoi_counter_idx;
	int m_htom_counter_idx;

	usec_matrix m_ctoh_counter;
	start_usec_arr m_ctoh_start_time;
	usec_matrix m_itoh_counter;
	start_usec_arr m_itoh_start_time;
	usec_matrix m_mtoh_counter;
	start_usec_arr m_mtoh_start_time;

	int m_ctoh_counter_idx;
	int m_itoh_counter_idx;
	int m_mtoh_counter_idx;

	void flush_one_perf_count(start_usec_arr start_time_arr, FILE* file, usec_matrix counter, step_desc_arr step_desc);
	static inline void update_one_perf(int step_idx, int counter_idx, usec_matrix& counter);
	
	step_desc_arr ctoh_step_desc;
	step_desc_arr htoc_step_desc;
	step_desc_arr itoh_step_desc;
	step_desc_arr htoi_step_desc;
	step_desc_arr mtoh_step_desc;
	step_desc_arr htom_step_desc;
};

//extern performance_counter g_performance_counter;

#ifndef MAX
#	define MAX(a,b) (((a) > (b)) ? (a) : (b))
#endif 

#ifndef MIN
#	define MIN(a,b) (((a) > (b)) ? (b) : (a))
#endif


extern mutex_lock	g_order_id_lock ;
extern u64_sl		g_max_order_id;
extern u64_sl		g_max_market_order_token;

extern mutex_lock g_order_exec_id_lock;
extern u64_sl		g_max_exec_id;


void get_transformed_uuid(int recursive_time, lpcstr_sl orig_uuid, int user_id, T_SESSION_ID& transformed_uuid);

