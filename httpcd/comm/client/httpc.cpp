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
 *	@return		None
 **/
void httpc::client_init(const char *ip)
{
	socketc_tcp_v4::client_init(ip, SOCKETCD_PORT_HTTP);

	return;
}
