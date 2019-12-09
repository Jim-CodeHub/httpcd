/**-----------------------------------------------------------------------------------------------------------------
 * @file	http_client.cpp
 * @brief	HTTP client handler AND packetize and depacketize HTTP message
 *
 * Copyright (c) 2019-2019 Jim Zhang 303683086@qq.com
 *------------------------------------------------------------------------------------------------------------------
*/

#include <httpcd/http_client.hpp>


using namespace NS_HTTPCD;


/*
--------------------------------------------------------------------------------------------------------------------
*
*			                                  FUNCTIONS IMPLEMENT
*
--------------------------------------------------------------------------------------------------------------------
*/

/**
 *	@brief	    Init http client 
 *	@param[in]  ip - IP address 
 *	@param[out] None
 *	@return		None
 **/
void http_client::init(const char *ip)
{
	this->client_init(ip);
	return;
}

/**
 *	@brief	    emit http message 
 *	@param[in]  flags - socket 'send' flags options 
 *	@param[out] None
 *	@return		None
 **/
void http_client::emit(int flags)
{
	string *message = new string;

	*message = this->pack_msg();

	this->data_send((void *)(message->data()), (message->size()), flags);

	delete message;	return;
}

/**
 *	@brief	    recv http message 
 *	@param[in]  flags - socket 'recv' flags options 
 *	@param[in]  _size - size of recive buffer 
 *	@param[out] None
 *	@return		None
 **/
void http_client::recv(int flags, ssize_t _size)
{
	char *message = new char[_size];

	ssize_t data_size = data_recv(message, _size, flags);

	this->load_msg(message, data_size);

	delete [] message; return;
}

