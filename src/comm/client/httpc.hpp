/**-----------------------------------------------------------------------------------------------------------------
 * @file	httpc.hpp
 * @brief   HTTP client-side communication 
 *
 * Copyright (c) 2019-2019 Jim Zhang 303683086@qq.com
 *------------------------------------------------------------------------------------------------------------------
*/


#ifndef __LIBHTTP_HTTPC_HPP__
#define __LIBHTTP_HTTPC_HPP__


/*-----------------------------------------------------------------------------------------------------------------
 * 
 *										LIBHTTP/HTTPC INCLUDES 
 *
 *------------------------------------------------------------------------------------------------------------------
*/

#include <socketc.hpp>


using namespace NS_LIBSOCKET;


namespace NS_LIBHTTP{

	
/*-----------------------------------------------------------------------------------------------------------------
 * 
 *										LIBHTTP/HTTPC DATA BLOCK
 *
 *------------------------------------------------------------------------------------------------------------------
*/

/**
 *	@brief HTTP client class with socket tcp v4 client
 **/
class httpc : public socketc_tcp_v4{
	public:
		void client_init(const char *ip);

		//url functions, DNS catch TBD

	private:
}; 


} /* namespace NS_LIBHTTP */


#endif /*__LIBHTTP_HTTPC_HPP__*/

