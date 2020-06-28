/**-----------------------------------------------------------------------------------------------------------------
 * @file	httpc.cpp
 * @brief   HTTP client-side communication 
 *
 * Copyright (c) 2019-2019 Jim Zhang 303683086@qq.com
 *------------------------------------------------------------------------------------------------------------------
*/

#include <httpcd/comm/client/httpc.hpp>


using namespace NS_HTTPCD;

/*
--------------------------------------------------------------------------------------------------------------------
*
*			                                  FUNCTIONS IMPLEMENT
*
--------------------------------------------------------------------------------------------------------------------
*/

/**
 *	@brief	    HTTP client init 
 *	@param[in]  ip - server ip address 
 *	@param[out] None
 *	@return		Standard sockect connect error
 **/
int httpc::client_init( const char *ip				   )
{
	return socketc_tcp_v4::client_init(ip, SOCKETCD_PORT_HTTP);
}

/**
 *	@brief	    HTTP client init 
 *	@param[in]  ip		- server ip address 
 *	@param[in]  port	- Application layer protocol port (for none-standard HTTP port)
 *	@param[out] None
 *	@return		Standard sockect connect error
 **/
int httpc::client_init( const char *ip, in_port_t port )
{
	return socketc_tcp_v4::client_init( ip, port );
}

