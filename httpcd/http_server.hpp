/**-----------------------------------------------------------------------------------------------------------------
 * @file	http_server.hpp
 * @brief	packetize and depacketize HTTP http_server
 *
 * Copyright (c) 2019-2019 Jim Zhang 303683086@qq.com
 *------------------------------------------------------------------------------------------------------------------
*/


#ifndef __HTTP_SERVER_HPP__
#define __HTTP_SERVER_HPP__


/*------------------------------------------------------------------------------------------------------------------
 * 
 *										HTTPCD/HTTP_SERVER INCLUDES 
 *
 *------------------------------------------------------------------------------------------------------------------
*/

#include <httpcd/comm/server/httpd.hpp>
#include <httpcd/message/message.hpp>


namespace NS_HTTPCD{

/*------------------------------------------------------------------------------------------------------------------
 * 
 *										HTTPCD/HTTP_SERVER DATA BLOCK
 *
 *------------------------------------------------------------------------------------------------------------------
*/

/**
 *	@brief HTTP server class and function set 
 **/
class http_server : public message, public httpd{
	public:
		http_server(){}; /**< Empty structure */
		http_server(const char *ip, void (*_msg_cgi)(class http_server &s)){this->init(ip, _msg_cgi);}; 

		void init(const char *ip, void (*_msg_cgi)(class http_server &s)							 );
		void emit(enum NS_SOCKETCD::method m = SELECT_TPC, int backlog=128, nfds_t nfds=0			 );

		void recv(ssize_t _size = 1024*1024 /**< 1M */												 );
		void recv(ssize_t _size = 1024*1024 /**< 1M */, int flags=0									 );
		void send(int flags = 0																		 );

	protected:
		void msg_cgi(int cfd, const struct sockaddr_in *caddr, void (*_msg_cgi)(class http_server &s));

	protected:
		int cfd;
};


} /* namespace NS_HTTPCD */


#endif /*__HTTP_SERVER_HPP__*/

