#pragma  once 
#define TEST_PERFORMANCE 
#ifdef SHENGLI_WINDOWS
// nothing 
#else
//#	define TEST_PERFORMANCE 
#endif

#ifdef TEST_PERFORMANCE 

#include <time.h>
#include <string.h>

#define PERFORMANCE_ITEM_COUNT 80000000 

struct performance_item
{
	performance_item()
	{
		memset(this, 0, sizeof(performance_item) );
	}

	char p_item_name[64]  ;
	char m_ExchangeOrderToken[32] ;
	struct timespec  beg_ts ;
//	struct timespec  end_ts ;
};

performance_item * get_next_send_performance() ;


struct auto_send_performance 
{
	auto_send_performance( const char* performance_name, long n_nsec = 0  ) 
	{
		m_p_item =  get_next_send_performance() ;

		if ( m_p_item )
		{
			strncpy(m_p_item->p_item_name, performance_name, sizeof(m_p_item->p_item_name) );		
			if ( n_nsec == 0 )
			{
				clock_gettime(CLOCK_REALTIME, & (m_p_item->beg_ts ) ) ;
			}
			else
			{
				m_p_item->beg_ts.tv_sec = 0 ;
				m_p_item->beg_ts.tv_nsec = n_nsec ;				
			}
		}

	}
	~auto_send_performance()
	{
// 		if ( m_p_item )
// 			clock_gettime(CLOCK_REALTIME, & (m_p_item->end_ts) );
	}



	performance_item * m_p_item ;

protected:
	auto_send_performance(const auto_send_performance&) ;
	auto_send_performance& operator = (const auto_send_performance& );
};


performance_item * get_next_resp_performance() ;

struct auto_resp_performance 
{
	auto_resp_performance( const char* performance_name, long n_nsec = 0  ) 
	{
		m_p_item =  get_next_resp_performance() ;

		if ( m_p_item )
		{
			strncpy(m_p_item->p_item_name, performance_name, sizeof(m_p_item->p_item_name) );		
			if ( n_nsec == 0 )
			{
				clock_gettime(CLOCK_REALTIME, & (m_p_item->beg_ts ) ) ;
			}
			else
			{
				m_p_item->beg_ts.tv_sec = 0 ;
				m_p_item->beg_ts.tv_nsec = n_nsec ;				
			}
		}

	}
	~auto_resp_performance()
	{
		// 		if ( m_p_item )
		// 			clock_gettime(CLOCK_REALTIME, & (m_p_item->end_ts) );
	}



	performance_item * m_p_item ;

protected:
	auto_resp_performance(const auto_resp_performance&) ;
	auto_resp_performance& operator = (const auto_resp_performance& );
};




#endif // !TEST_PERFORMANCE

