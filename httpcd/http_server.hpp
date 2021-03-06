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
 *										HTTPCD/HTTP_SERVER SHORT ALIAS 
 *
 *------------------------------------------------------------------------------------------------------------------
*/
#define  HTTPCD_DFSIZE_RECV			1024*1024


/*------------------------------------------------------------------------------------------------------------------
 * 
 *										HTTPCD/HTTP_SERVER DATA BLOCK
 *
 *------------------------------------------------------------------------------------------------------------------
*/

typedef std::function<void(class http_server &s)> HTTP_CGI_T;

/**
 *	@brief HTTP server class and function set 
 **/
class http_server : public message, public httpd{
	public:
		http_server( const char *ip,				 HTTP_CGI_T _msg_cgi					);
		http_server( const char *ip, in_port_t port, HTTP_CGI_T _msg_cgi 					);

		void emit( enum NS_SOCKETCD::method m = SELECT_TPC, int backlog=128, nfds_t nfds=0 	);

		void recv( ssize_t msg_len = 0														);

		void rst_rcv_size(ssize_t _size														);

		void send(int flags = 0															  	);

	protected:
		http_server(){ rcv_size = HTTPCD_DFSIZE_RECV; /**< 1M */   };  /**< Empty structure */

		void init(const char *ip,				  HTTP_CGI_T _msg_cgi						);
		void init(const char *ip, in_port_t port, HTTP_CGI_T _msg_cgi						);

		void msg_cgi(int cfd, const struct sockaddr_in *caddr, HTTP_CGI_T _msg_cgi		  	);

	protected:
		int cfd; ssize_t rcv_size = 1024*1024; /**< Default 1M */
};


} /* namespace NS_HTTPCD */


#endif /*__HTTP_SERVER_HPP__*/

