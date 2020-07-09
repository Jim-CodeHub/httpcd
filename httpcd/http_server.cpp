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
 *	@param[in]  ip			- IP address 
 *	@param[in]  _msg_cgi	- message handler 
 *	@param[out] None
 *	@return		None
 **/
http_server::http_server(const char *ip, HTTP_CGI_T _msg_cgi)
{
	rcv_size = HTTPCD_DFSIZE_RECV; this->init(ip, _msg_cgi);
}

/**
 *	@brief	    Init http server 
 *	@param[in]  ip			- IP address 
 *	@param[in]  port		- Application layer protocol port (for none-standard HTTP port)
 *	@param[in]  _msg_cgi	- message handler 
 *	@param[out] None
 *	@return		None
 **/
http_server::http_server(const char *ip, in_port_t port, HTTP_CGI_T _msg_cgi)
{
	rcv_size = HTTPCD_DFSIZE_RECV; this->init(ip, port, _msg_cgi);
} 

/**
 *	@brief	    Init http server 
 *	@param[in]  ip			- IP address 
 *	@param[in]  _msg_cgi	- message handler 
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
 *	@brief	    Init http server 
 *	@param[in]  ip			- IP address 
 *	@param[in]  port		- Application layer protocol port (for none-standard HTTP port)
 *	@param[in]  _msg_cgi	- message handler 
 *	@param[out] None
 *	@return		None
 **/
void http_server::init(const char *ip, in_port_t port, HTTP_CGI_T _msg_cgi)
{
	CGI_T f = bind(&http_server::msg_cgi, this, std::placeholders::_1, std::placeholders::_2, _msg_cgi);

	this->server_init(ip, port, f);

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
 *	@param[in]  msg_len		-	http client message length 
 *	@param[out] None
 *	@return		None
 *	@note		If 'Content-Length' is not exsist, msg_len will be used
 **/
void http_server::recv( ssize_t msg_len )
{
	char *message	= new char[rcv_size];
	char *p			= message;

	memset( message, 0, rcv_size );

	/** ------------------------------------------------------------------------- */
	/**< Load HTTP header. */

	char	ch		= 0;
	ssize_t rnCnt	= 0; 
	while ( this->data_recv(this->cfd, &ch, 1, 0) )
	{
		*p= ch; p++;

		switch ( rnCnt ) /**< Detecte '\r\n\r\n '*/
		{
			case 0:
				rnCnt = (ch == '\r')?(rnCnt + 1):0; 
				break;
			case 1:
				rnCnt = (ch == '\n')?(rnCnt + 1):0; 
				break;
			case 2: 
				rnCnt = (ch == '\r')?(rnCnt + 1):0; 
				break;
			case 3:
				rnCnt = (ch == '\n')?(rnCnt + 1):0; 
				break;
			default: ;
		}

		if ( 4 == rnCnt ) { break; } /**< HTTP Header Pass. */
	}

	/** ------------------------------------------------------------------------- */
	/**< Get Content-Length. */

	this->load_msg(message, p - message);

	ssize_t body_len = atoi( this->get_msg_head(Content_Length).c_str() );

	if ( 0 == body_len ) { /**< Field  Content-Length is not exists. */
		body_len = msg_len - (p-message); 
	}

	/** ------------------------------------------------------------------------- */
	/**< Get HTTP body. */

	ssize_t recvLen  = 0;
	while ( (recvLen = this->data_recv(this->cfd, p, rcv_size, 0), recvLen) )
	{
		p += recvLen;

		if ( recvLen >= body_len ) { break; }
	}

	this->load_msg(message, p - message);

	delete [] message; message = NULL; 

	return;
}

/**
 *	@brief	    Reset recive buff size 
 *	@param[in]  _size 
 *	@param[out] None
 *	@return		None
 *	@note		The function MUST BE used BEFOR function recv()
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

