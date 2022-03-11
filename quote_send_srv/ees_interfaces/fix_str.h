#pragma  once 

#include <string.h>
#include <stdlib.h>

#include <string>
using namespace std ;


template< unsigned short Len =32 >
struct fix_str
{	
	char	m_val[Len] ;
	fix_str()
	{
		memset(m_val, 0, Len);	
	}

	fix_str(const char* str )
	{
		*this = str ;
	}
	
	static unsigned short max_len()
	{
		return Len ;
	}

	fix_str& operator = (const fix_str & obj)
	{
		memcpy(m_val, obj.m_val, Len);
		return *this;
	}

	fix_str& operator = (const char* p_str )
	{
		int n_idx = 0 ; 
		while( p_str[n_idx] && n_idx < (Len-1) )
		{
			m_val[n_idx] = p_str[n_idx] ;
			++n_idx;
		}
		for (int i = n_idx; i < Len; i++)
			m_val[i] = 0x00 ;
		return *this ;
	}

	fix_str& operator = (const string& p_str )
	{
		*this = p_str.c_str() ;
		return *this ;
	}
	
	fix_str& assign (const char* p_str , int beg_pos, int len)
	{
		if (len > max_len())
		{
			len = max_len() - 1;
		}

		memcpy(m_val, p_str + beg_pos, len);
		m_val[len] = 0x00; 
		return *this;
	}

	//bool operator < (const char* p_str)
	//{
	//	return (strcmp(m_val, p_str) < 0);
	//}

	//bool operator < (const string& str)
	//{
	//	return (strcmp(m_val, str.c_str() ) < 0);
	//}

	//fix_str& operator += (const char* p_str)
	//{
	//	strcat(m_val, p_str) ;
	//	return *this ;
	//}

	//fix_str& operator += (const string& p_str)
	//{
	//	strcat(m_val, p_str.c_str()) ;
	//	return *this ;
	//}

	//fix_str& operator += (const char& ch )
	//{
	//	char buf[2] ; 
	//	buf[0] = ch ; 
	//	buf[1] = 0 ; 
	//	return *this += buf ;
	//}

	//fix_str& operator << (const char* p_str )
	//{
	//	return *this += p_str ;
	//}
	//
	//fix_str& operator << (const string& p_str )
	//{
	//	return *this += p_str ;
	//}
	//
	//fix_str& operator << ( const char& ch )
	//{
	//	return *this += ch ;
	//}

	bool operator == (const char* p_str )
	{
		return strcmp(m_val, p_str) == 0 ;
	}

	bool operator != (const char* p_str )
	{
		return strcmp(m_val, p_str) != 0 ;
	}
	
	//operator char* ()
	//{
	//	return m_val ;
	//}

	operator const char*()
	{
		return m_val ;
	}

	operator char*()
	{
		return m_val ;
	}


	char& operator [] (unsigned short offset)
	{
		return m_val[offset];
	}

	int length()
	{
		return strlen(m_val);
	}

	const char* cstr() const
	{
		return m_val;
	}

	char* str()
	{
		return m_val;
	}


	fix_str remove_str( const char* old_str)
	{
		return replace_str(old_str, "");
	}

	fix_str replace_str( const char* old_str, const char* new_str )
	{
		char buf[Len] = { 0x00 };
		int odlLen = strlen(old_str);
		int newLen = strlen(new_str);

		char * p_new_pos = buf; 
		char * p_pos = m_val;

		while ( *p_pos )
		{
			if ( memcmp(old_str, p_pos, odlLen) == 0 )
			{
				p_pos += odlLen;
				if (new_str != 0x00)
				{
					strcat(p_new_pos, new_str); 
					p_new_pos += newLen;
				}
			}
			else
			{
				*p_new_pos = *p_pos;
				++p_pos;
				++p_new_pos; 
			}
		}		
		*p_new_pos = 0x00;

		return fix_str(buf);
	}

	//模板类似乎不支持可变参数，只好不用

//	int format(lpcstr_sl pformat, ...)
//	{
//		va_list args;
//		va_start(args, pformat);
//		int ret = 0;
//		size_t max_size = Len;
//#ifdef SHENGLI_WINDOWS
//		ret = vsprintf_s(m_val, max_size, pformat, args);
//#else
//		ret = vsnprintf(m_val, max_size, pformat, args);
//#endif
//		va_end(args);
//		
//		
//		return strlen(m_val);
//	}
};