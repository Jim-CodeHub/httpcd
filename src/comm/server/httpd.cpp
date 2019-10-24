/**-----------------------------------------------------------------------------------------------------------------
 * @file	httpd.cpp
 * @brief   HTTP server-side communication 
 *
 * Copyright (c) 2019-2019 Jim Zhang 303683086@qq.com
 *------------------------------------------------------------------------------------------------------------------
*/

#include "httpd.hpp"


using namespace NS_LIBHTTP;

/*
--------------------------------------------------------------------------------------------------------------------
*
*			                                  FUNCTIONS IMPLEMENT
*
--------------------------------------------------------------------------------------------------------------------
*/

/**
 *	@brief	    HTTP server init 
 *	@param[in]  ip		- server ip address 
 *	@param[in]  msg_cgi - User's client message handler  
 *	@param[out] None
 *	@return		None
 **/
void httpd::server_init(const char *ip, CGI_T msg_cgi)
{
	socketd_tcp_v4::server_init(ip, LIBSOCKET_PORT_HTTP, msg_cgi);

	return;
}

/**
 *	@brief	    HTTP server start 
 *	@param[in]  method	- BLOCK/PPC/TPC/SELECT_TPC/POLL_TPC/EPOLL_TPC 
 *	@param[in]  backlog	- Size of listen queue 
 *	@param[out] None
 *	@return		None
 *	@note	    Select Multi-process services are used
 **/
void httpd::server_emit(int backlog)
{
	socketd_tcp_v4::server_emit(SELECT_TPC, backlog, 0);

	return;
}

