/**-----------------------------------------------------------------------------------------------------------------
 * @file	httpd.hpp
 * @brief   HTTP server-side communication 
 *
 * Copyright (c) 2019-2019 Jim Zhang 303683086@qq.com
 *------------------------------------------------------------------------------------------------------------------
*/


#ifndef __HTTPD_HPP__
#define __HTTPD_HPP__


/*-----------------------------------------------------------------------------------------------------------------
 * 
 *										HTTPCD/HTTPD INCLUDES 
 *
 *------------------------------------------------------------------------------------------------------------------
*/

#include <socketcd/socketcd.hpp>


using namespace NS_SOCKETCD;


namespace NS_HTTPCD{

	
/*-----------------------------------------------------------------------------------------------------------------
 * 
 *										HTTPCD/HTTPD DATA BLOCK
 *
 *------------------------------------------------------------------------------------------------------------------
*/

/**
 *	@brief HTTP server class with socket tcp v4 server 
 **/
class httpd : public socketd_tcp_v4{
	public:
		void server_init(const char *ip, CGI_T msg_cgi);
		void server_emit(int backlog=128);

	private:
}; 


} /* namespace NS_HTTPCD */


#endif /*__HTTPD_HPP__*/

