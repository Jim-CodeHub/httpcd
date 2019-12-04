/**-----------------------------------------------------------------------------------------------------------------
 * @file	httpc.hpp
 * @brief   HTTP client-side communication 
 *
 * Copyright (c) 2019-2019 Jim Zhang 303683086@qq.com
 *------------------------------------------------------------------------------------------------------------------
*/


#ifndef __HTTPC_HPP__
#define __HTTPC_HPP__


/*-----------------------------------------------------------------------------------------------------------------
 * 
 *										HTTPCD/HTTPC INCLUDES 
 *
 *------------------------------------------------------------------------------------------------------------------
*/

#include <socketcd/socketcd.hpp>


using namespace NS_SOCKETCD;


namespace NS_HTTPCD{

	
/*-----------------------------------------------------------------------------------------------------------------
 * 
 *										HTTPCD/HTTPC DATA BLOCK
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


} /* namespace NS_HTTPCD */


#endif /*__HTTPC_HPP__*/

