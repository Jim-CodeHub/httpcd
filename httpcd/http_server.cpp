/**-----------------------------------------------------------------------------------------------------------------
 * @file	http_server.cpp
 * @brief	HTTP server handler AND packetize and depacketize HTTP message
 *
 * Copyright (c) 2019-2019 Jim Zhang 303683086@qq.com
 *------------------------------------------------------------------------------------------------------------------
*/

#include <httpcd/http_server.hpp>


using namespace NS_HTTPCD;


/*
--------------------------------------------------------------------------------------------------------------------
*
*			                                  FUNCTIONS IMPLEMENT
*
--------------------------------------------------------------------------------------------------------------------
*/

/**
 *	@brief	    HTTP server hook function to handler message 
 *	@param[in]  cfd 
 *	@param[in]  caddr 
 *	@param[in]  _msg_cgi -	set message cgi (parse message from client and set message for client)	
 *	@param[out] None
 *	@return		None
 **/
void http_server::msg_cgi(int cfd, const struct sockaddr_in *caddr, HTTP_CGI_T _msg_cgi)
{
	this->cfd = cfd; _msg_cgi(*this);

	return;
}

/**
 *	@brief	    Init http server 
 *	@param[in]  ip - IP address 
 *	@param[out] None
 *	@return		None
 **/
void http_server::init(const char *ip, HTTP_CGI_T _msg_cgi)
{
	CGI_T f = bind(&http_server::msg_cgi, this, std::placeholders::_1, std::placeholders::_2, _msg_cgi);

	this->server_init(ip, f);

	return;
}

/**
 *	@brief	    HTTP server start
 *	@param[in]  method	- BLOCK/PPC/TPC/SELECT_TPC/POLL_TPC/EPOLL_TPC 
 *	@param[in]  backlog	- Size of listen queue 
 *	@param[in]  nfds	- Number of poll/epoll structure, set it, if method == POLL_TPC/EPOLL_TPC
 *	@param[out] None
 *	@return		None
 *	@note		!!! NO INSTRUCTION ARE EXECUTED AFTER THE FUNCION IS CALLED
 **/
void http_server::emit(enum NS_SOCKETCD::method m, int backlog, nfds_t nfds)
{
	this->server_emit(m, backlog, nfds);

	return;
}

/**
 *	@brief	    Recive http message from client 
 *	@param[in]  None 
 *	@param[out] None
 *	@return		None
 *	@note		The function perform a loop style, and 
 *				it cannot be returned if the peer does not close the file descriptor after data send
 **/
void http_server::recv(void)
{
	char *message = new char[rcv_size];

	ssize_t data_size = this->data_recv(this->cfd, message, rcv_size);

	this->load_msg(message, data_size);

	delete [] message; return;
}

/**
 *	@brief	    Recive http message from client 
 *	@param[in]  flags - socket 'recv' flags options 
 *	@param[out] None
 *	@return		None
 **/
void http_server::recv(int flags)
{
	char *message = new char[rcv_size];

	ssize_t data_size = this->data_recv(this->cfd, message, rcv_size, flags);

	this->load_msg(message, data_size);

	delete [] message; return;
}

/**
 *	@brief	    Reset recive buff size 
 *	@param[in]  _size 
 *	@param[out] None
 *	@return		None
 **/
void http_server::rst_rcv_size(ssize_t _size)
{
	this->rcv_size = (_size <= 0)?(1024*1024):_size;

	return;
}

/**
 *	@brief	    Send http message to client 
 *	@param[in]  flags - socket 'send' flags options 
 *	@param[out] None
 *	@return		None
 **/
void http_server::send(int flags)
{
	string *message = new string;

	*message = this->pack_msg();

	this->data_send(this->cfd,(void *)(message->data()), (message->size()), flags);

	delete message; return;
}

