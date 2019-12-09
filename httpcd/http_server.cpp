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
void http_server::msg_cgi(int cfd, const struct sockaddr_in *caddr, void (*_msg_cgi)(class http_server &s))
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
void http_server::init(const char *ip, void (*_msg_cgi)(class http_server &s))
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
 *	@param[in]  flags - socket 'recv' flags options 
 *	@param[in]  _size - size of recive buffer 
 *	@param[out] None
 *	@return		None
 **/
void http_server::recv(int flags, ssize_t _size)
{
	char *message = new char[_size];

	ssize_t data_size = ::recv(this->cfd, message, _size, flags);

	if (-1 == data_size) {perror("Data rcve error"); exit(-1);}

	this->load_msg(message, data_size);

	delete [] message; return;
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

	::send(this->cfd, (void *)(message->data()), (message->size()), flags);

	delete message; return;
}
