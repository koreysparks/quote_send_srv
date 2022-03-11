#pragma once
#include <stdarg.h>
#include "msg_define.h"

//*******************************************************************
///  Log 的等级
/*!
* @enum
* @brief 一共定义了五种log类型 
*/
//*******************************************************************
enum LOG_LEVEL
{
	LOG_LV_DEBUG = 1,///< 调试信息
	LOG_LV_INFO = 2,	///< 消处信息
	LOG_LV_WARN = 3,	///< 警告
	LOG_LV_ERROR = 4,	///< 错误
 	LOG_LV_FATAL = 4,	///< 致命错误
 	LOG_LV_USER = 5, ///< 用于给用户显示的消息
	LOG_LV_OP	= 6, ///< 用于发送操作日志类型，必须发往服务器，用特殊的文本格式发送
	LOG_LV_END		//结尾标志
};

/**
* @enum 
* Log 的类型
*/
enum LOG_DESTINATION
{
	LOG_DEST_NONE = 0x00,	///< 不记录
	LOG_DEST_FILE = 0x01,	///< 写文件标记
	LOG_DEST_REMOTE = 0x02,	///< 向远程写标记
	LOG_DEST_CONSOLE = 0x04, ///< 是否向控制台输出
	LOG_DEST_ALL = 0x07		///< 是否全部输出
};
/**
* @enum 
* Log二进制协议时，需要指明这是那种协议，不同的协议的消息id可能重复，将会采用不同的
*/
enum LOG_PROTOCOL
{
	LOG_PROTO_CLIENT,
	LOG_PROTO_INTERNAL,
	LOG_PROTO_MARKET,
	LOG_PROTO_COMM,///配置信息，报错信息等接口
	LOG_PROTO_HDS,
	LOG_PROTO_MI,  /// 用于记录MI的信息
	LOG_PROTO_END  ///不用，用作结尾标志
};

enum OP_LOG_SOURCE
{
	OP_SRC_ADMIN = 0,
	OP_SRC_BUSINESS,
	OP_SRC_TRADER,
};

enum OP_TYPE
{
	OP_TYPE_TRY_LOGIN = 0,
	OP_TYPE_LOGIN_SUCCESS,
	OP_TYPE_LOGIN_FAILED,
	OP_TYPE_CHANGE_PWD,
	OP_TYPE_DEL_ACCOUNT,
	OP_TYPE_SET_ACCOUNT_EXCHANGE_CODE,
	OP_TYPE_ADD_ACCOUNT,
	OP_TYPE_ADD_BOUND_USER,
	OP_TYPE_SET_INIT_BP,
	OP_TYPE_CASH_INOUT,
	OP_TYPE_ADD_USER,
	OP_TYPE_DEL_USER,
	OP_TYPE_RESET_USER_PWD,
	OP_TYPE_CHANGE_USER_LOGIN_ID,
	OP_TYPE_ENABLE_DISABLE_USER,
	OP_TYPE_EOD_IMPORT,
};

struct op_log_unit
{
	OP_LOG_SOURCE m_op_log_source;
	char		m_client_ip[51];
	int			m_client_port;
	int			m_op_user_id;
	char		m_logon_id[51];
	OP_TYPE		m_op_type;
	char		m_description[1800];
	op_log_unit(OP_LOG_SOURCE op_log_source, lpcstr_sl  client_ip, int client_port, int op_user_id, lpcstr_sl logon_id, OP_TYPE op_type, lpcstr_sl desc_text)
	{
		memset(this, 0, sizeof(*this));
		m_op_log_source = op_log_source;
		strncpy_sl(m_client_ip, sizeof(m_client_ip), client_ip);
		m_client_port = client_port;
		m_op_user_id = op_user_id;
		strncpy_sl(m_logon_id, sizeof(m_logon_id), logon_id);
		m_op_type = op_type;
		strncpy_sl(m_description, sizeof(m_description), desc_text);
	}

	op_log_unit()
	{
		memset(this, 0, sizeof(*this));
	}
};


/*!****************************************************************************
	@date	    2013/10/18   15:46
	@file       ees_logger.h
	@author     zhouyou
	
    @brief		约定：不同的LOG_LEVEL，不同的LOG_PROTOCOL将写入不同的文件中，这样多线程加锁可以按照类型和协议分开，增加并发性。
    @格式约定：   8位日期-时间.毫秒 5位明文长度 内容 \n，长度只包含内容长度，不包含记录头和\n结尾符
    @明文格式：   201301018-16:03:05.023123 00512 [明文内容]\n
    @二进制格式： 201301018-16:03:05.023123 00512 msg_direction枚举值 [二进制内容]\n 
    @建议：OT的Primary Core和Background Core各自使用独立的实例来记录二进制日志，避免同种消息混在一个文件中无法分辨
	
******************************************************************************/
class i_ees_logger
{
public:	
	
	virtual ~i_ees_logger(void) {}

	virtual bool initialize(lpcstr_sl log_name_prefix, lpcstr_sl log_dir) = 0;
	virtual void set_level_destination(LOG_LEVEL level, int combined_dest ) = 0;
	virtual void set_proto_destination(LOG_PROTOCOL proto, int combined_dest ) = 0;
	virtual int get_level_destination(LOG_LEVEL level) = 0;
	virtual int get_proto_destination(LOG_PROTOCOL proto) = 0;
	
	virtual int write_text(LOG_LEVEL level, lpcstr_sl pformat, ...) = 0;	
	virtual int write_debug(lpcstr_sl pformat, ...) = 0;	
	virtual int write_info(lpcstr_sl pformat, ...) = 0;
	virtual int write_warning(lpcstr_sl pformat, ...) = 0;
	virtual int write_error(lpcstr_sl pformat, ...) = 0;
	virtual int write_fatal(lpcstr_sl pformat, ...) = 0;
	virtual int write_user(lpcstr_sl pformat, ...) = 0;
	
	virtual int write_bin(LOG_PROTOCOL proto, msg_direction direction, lpcstr_sl buffer, u32_sl len) = 0;
	virtual int write_bin_client(msg_direction direction, lpcstr_sl buffer, u32_sl len) = 0;
	virtual int write_bin_internal(msg_direction direction, lpcstr_sl buffer, u32_sl len) = 0;
	virtual int write_bin_market(msg_direction direction, lpcstr_sl buffer, u32_sl len) = 0;
	virtual int write_bin_comm(msg_direction direction, lpcstr_sl buffer, u32_sl len) = 0;
	virtual int write_bin_hds(msg_direction direction, lpcstr_sl buffer, u32_sl len) = 0;
	virtual int write_bin_mi(msg_direction direction, lpcstr_sl buffer, u32_sl len) = 0;

	virtual int write_status_log( const char* p_json_log ) = 0 ; 
	

	//混合日志，这个日志混合了明文和二进制数据，并且不需要机械程序来读取
	virtual int write_mixed_log(LOG_LEVEL level, lpcstr_sl buffer, u32_sl len) = 0;

	virtual int write_comm_msg(lpcstr_sl pName, lpcstr_sl pFlag, lpcstr_sl pMsg, u32_sl nLen) = 0 ;

	//写操作日志
	virtual int write_op_log(op_log_unit& olu) = 0;
	
	virtual void flush_all() = 0;

	virtual void set_auto_flush(bool auto_flush) = 0;

	virtual bool get_current_log_server_id(T_server_id & id) = 0; 

	//是否与lgs建立了连接
	virtual bool is_connected() = 0;

	//诊断模式，因大部分模块需要调用logger模块，所以使用logger模块来存放诊断模式标志位。。。。
	virtual void set_diag_mode(ees_diag_mode diag_mode) = 0;

	virtual ees_diag_mode get_diag_mode() = 0;
};


///<简单的日志宏定义
#define LOG_INF(tmp_log, m) \
                       {\
						  if ( tmp_log ){  \
							  tmp_log->write_text(LOG_LV_INFO,"%s %s %s:%d", m, __FUNCTION__, __FILE__, __LINE__); \
						  }else{ \
						       printf("%s \n", m); \
						  }}

#define LOG_DEB(tmp_log, m) \
                        {\
	                     if ( tmp_log ){  \
	                          tmp_log->write_text(LOG_LV_DEBUG,"%s %s %s:%d", m, __FUNCTION__, __FILE__, __LINE__); \
	                     }else{ \
	                          printf("%s \n", m); \
	                     }}

#define LOG_WAR(tmp_log, m) \
                       {\
						  if ( tmp_log ){  \
							  tmp_log->write_text(LOG_LV_WARN,"%s %s %s:%d", m, __FUNCTION__, __FILE__, __LINE__); \
						  }else{ \
						       printf("%s \n", m); \
						  }}

#define LOG_ERR(tmp_log, m) \
                         {\
	                      if ( tmp_log ){  \
	                          tmp_log->write_text(LOG_LV_ERROR,"%s %s %s:%d", m, __FUNCTION__, __FILE__, __LINE__); \
	                      }else{ \
	                           printf("%s \n", m); \
	                      }}


#define LOG_FAT(tmp_log, m)  \
                         {\
	                      if ( tmp_log ){  \
	                          tmp_log->write_text(LOG_LV_FATAL,"%s %s %s:%d", m, __FUNCTION__, __FILE__, __LINE__); \
	                      }else{ \
	                           printf("%s \n", m); \
	                      }}   



