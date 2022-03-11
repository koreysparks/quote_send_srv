#pragma once

#include "shengli_tool/shengli_define.h"
#include "shengli_tool/date_time.h"
#include "shengli_tool/lock.h"
#include "i_performance.h"	

using namespace SHENGLI::TOOLS;

#include "msg_define.h"

/// 2014-08-12 ���ǵ�ͣ�ļ۸񱨼۲������ƣ���Ŀǰ�ļ۸��������¸���15%����, ������ģ���д洢Ϊԭ�е�ֵ, ֻ�����ⱨ�����ⲿ��ȡʱ����
#define QUOTE_LIMIT_PRICE_EXTENTED_RATE (0.0)

/// @brief �ӱ��������ļ� "ees_db_entry.xml" ��ȡ���ݿ���ڵ�ַ��ot����Ҫ��ȡot_id, eqs��Ҫ��ȡeqs_id
/// @param db_entry��������ݿ���ڵ�ַ
/// @param ot_id�����ot��id��Ŀǰֻ��otģ����ģ���������ģʽ���Ǳ���ģʽ����������ļ���û�д˽ڵ㣬��ô���ؿ��ַ���
/// @param ot_id�����eqs��id��Ŀǰֻ��eqsģ����ģ���������ļ���û�д˽ڵ㣬��ô���ؿ��ַ���
/// @return�� true���ɹ���ȡ��false���ļ������ڡ����߸�ʽ����ȷ
bool load_db_entry(string& db_entry, string& back_db_entry);

void set_max_order_id( u64_sl max_id );
u64_sl get_max_order_id();
u64_sl get_next_max_order_id() ;

void set_max_exec_id( u64_sl max_id ) ;
u64_sl get_max_exec_id();
u64_sl get_next_max_exec_id();


///2014/08/12, Ϊ�˺�Ӳ��һ�£���������get_nano_seconds_of_day�����ķ���ֵ����Ϊ��1970-1-1 0�㿪ʼ������+����������4λΪһ���ڵ�����������4λΪ�������൱��time_t��ֵ
///<ȡ��1970-1-1 00:00:00��ʼ��������
u64_sl get_nano_seconds_of_day();


///<��ȡorder_refer_num�ڵ�bit_locλ��ֵ,bit_locȡֵ��Χ0-63
u8_sl get_bit(u64_sl order_refer_num, u8_sl bit_loc);

///<����order_refer_num�ڵ�bit_locλ��ֵΪ1
u64_sl set_bit_to_one(u64_sl order_refer_num, u8_sl bit_loc);

///<����order_refer_num�ڵ�bit_locλ��ֵΪ0
u64_sl set_bit_to_zero(u64_sl order_refer_num, u8_sl bit_loc);

//��ȡһ����ʽΪyyyyMMdd-HH:mm:ss.ffffff�ĵ�ǰʱ���ַ�������ȷ��΢�� 
string get_cur_time_str();


i64_sl get_cl_ord_key(u32_sl user_id, u32_sl cl_ord_token);

void from_cl_ord_key(i64_sl order_key, u32_sl& user_id, u32_sl& cl_ord_token);

///<���������еĿո���߼�����
string get_adjust_cmd(lpcstr_sl ch_cmd);

const char * get_str_exchange_id( T_EXCHANGE ees_change_id );
T_EXCHANGE get_ees_exchange_id( const char*  exchange_id );


double normalize_fee(double exec_fee);//������������������ķ�ʽ��������һ��������ֻ����ɽ��������۳��ģ����ᡢ�ⶳ�Ĳ�����������ˡ�

void get_trade_session_id(int id1, int id2, const char* p_str, T_SESSION_ID& buf);


/// ����risk memory���ֵ��ת��
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

///��ϵͳ��һ��8�ֽ����֣�����Ӳ��������timestamp��ת����struct tm��һ�����ڵ�������
void convert_from_timestamp(u64_sl timestamp, tm& tm_result, u32_sl& nano_sec);
///��struct tm��һ�����ڵ�������,ת����ϵͳ��һ��8�ֽ�����,����Ӳ��������timestamp
u64_sl convert_to_timestamp(tm& tm_struct, const u32_sl nano_sec);
///����ǰʱ��,ת����ϵͳ��һ��8�ֽ�����,����Ӳ��������timestamp
u64_sl convert_now_to_timestamp();

///��һ��ʱ�����ʽ"08:30:24"ת����ϵͳ��һ��8�ֽ�����,����Ӳ��������timestamp
typedef char  TimeFormatType[9];	
u64_sl convert_timestr_to_timestamp(TimeFormatType strtime);

////////////////////////////���漸��������RSA 2048�����㷨//////////////////////////////////////

/// ʹ��RSA 2048�����㷨��text���м��ܣ������buffer
int get_ciphertext(const char* key, const char* text, int text_len, char* buffer, int len);

/// ����buffer�ڴ����ݼ���
int rsa_encrypt(const char* key, int in_len, const char* strData, int data_len, char* outOut);

/// base64
int base64_encode(const char* pSrc, int nSrcLen, char* pDst, int nDstLen);


///<���ܼ�¼��ص�ʱ��
///���಻�������������������ɹ���Ӱ�죬��������Ҫ��֤�̰߳�ȫ��
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

