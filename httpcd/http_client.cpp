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
 *	@param[in]  None 
 *	@param[out] None
 *	@return		None
 *	@note		The function perform a loop style, and 
 *				it cannot be returned if the peer does not close the file descriptor after data send
 **/
void http_client::recv(void)
{
	this->clear(); /**< Clear MIME message tree */

	char *message = new char[rcv_size];

	ssize_t data_size = this->data_recv(message, rcv_size);

	this->load_msg(message, data_size);

	delete [] message; return;
}

/**
 *	@brief	    recv http message 
 *	@param[in]  flags - socket 'recv' flags options 
 *	@param[out] None
 *	@return		None
 **/
void http_client::recv(int flags)
{
	this->clear(); /**< Clear MIME message tree */

	char *message = new char[rcv_size];

	ssize_t data_size = this->data_recv(message, rcv_size, flags);

	this->load_msg(message, data_size);

	delete [] message; return;
}

/**
 *	@brief	    Reset recive buff size 
 *	@param[in]  _size 
 *	@param[out] None
 *	@return		None
 **/
void http_client::rst_rcv_size(ssize_t _size)
{
	this->rcv_size = (_size <= 0)?(1024*1024):_size;

	return;
}

