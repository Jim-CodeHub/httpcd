/**-----------------------------------------------------------------------------------------------------------------
 * @file	http_client.hpp
 * @brief	HTTP client handler AND packetize and depacketize HTTP message
 *
 * Copyright (c) 2019-2019 Jim Zhang 303683086@qq.com
 *------------------------------------------------------------------------------------------------------------------
*/


#ifndef __HTTP_CLIENT_HPP__
#define __HTTP_CLIENT_HPP__


/*------------------------------------------------------------------------------------------------------------------
 * 
 *										HTTPCD/HTTP_CLIENT INCLUDES 
 *
 *------------------------------------------------------------------------------------------------------------------
*/

#include <httpcd/comm/client/httpc.hpp>
#include <httpcd/message/message.hpp>


namespace NS_HTTPCD{

/*------------------------------------------------------------------------------------------------------------------
 * 
 *										HTTPCD/HTTP_CLIENT DATA BLOCK
 *
 *------------------------------------------------------------------------------------------------------------------
*/

/**
 *	@brief HTTP client class and function set 
 **/
class http_client : public message, public httpc{
	public:
		http_client(){}; /**< Empty structure */
		http_client(const char *ip){ this->init(ip); }				   ;

		void init(const char *ip									  );
		void emit(int flags = 0										  );

		void recv(ssize_t _size = 1024*1024 /**< 1M */				  );
		void recv(ssize_t _size = 1024*1024 /**< 1M */, int flags=0	  );

		//SET, 'set_socket_opt' function to implement more performence 

	private:

};


} /* namespace NS_HTTPCD */


#endif /*__HTTP_CLIENT_HPP__*/

