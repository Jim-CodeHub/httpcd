/**-----------------------------------------------------------------------------------------------------------------
 * @file	httpd.cpp
 * @brief   HTTP server-side communication 
 *
 * Copyright (c) 2019-2019 Jim Zhang 303683086@qq.com
 *------------------------------------------------------------------------------------------------------------------
*/

#include <httpcd/comm/server/httpd.hpp>


using namespace NS_HTTPCD;

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
	socketd_tcp_v4::server_init(ip, SOCKETCD_PORT_HTTP, msg_cgi);

	return;
}

/**
 *	@brief	    HTTP server start 
 *	@param[in]  method	- BLOCK/PPC/TPC/SELECT_TPC/POLL_TPC/EPOLL_TPC 
 *	@param[in]  backlog	- Size of listen queue 
 *	@param[in]  nfds	- Number of poll/epoll structure, set it, if method == POLL_TPC/EPOLL_TPC
 *	@param[out] None
 *	@return		None
 *	@note	    Select Multi-process services are used
 **/
void httpd::server_emit(enum method m, int backlog, nfds_t nfds)
{
	socketd_tcp_v4::server_emit(m, backlog, nfds);

	return;
}

