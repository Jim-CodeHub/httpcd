/**-----------------------------------------------------------------------------------------------------------------
 * @file	message.cpp
 * @brief	packetize and depacketize HTTP message
 *
 * Copyright (c) 2019-2019 Jim Zhang 303683086@qq.com
 *------------------------------------------------------------------------------------------------------------------
*/

#include "message.hpp"


using namespace NS_LIBHTTP;


/*
--------------------------------------------------------------------------------------------------------------------
*
*			                                  FUNCTIONS IMPLEMENT
*
--------------------------------------------------------------------------------------------------------------------
*/

/**
 *	@brief	    Packetize HTTP request line with official method	
 *	@param[in]  m	- GET/HEAD/PUT...	
 *	@param[in]	URL
 *	@param[in]  v	- HTTP_0_9/HTTP_1_0/HTTP_1_1...
 *	@param[out] None
 *	@return		None
 *	@note		The function can be called repeatedly, BUT only to save the latest setting.
 **/
void message::set_msg_line(enum method m, const char *URL, enum version v)
{
	string space = " ";
	string CRLF  = "\r\n";

	const char *method[]  = {"GET", "HEAD", "PUT", "POST", "TRACE", "OPTIONS", "DELETE"};
	const char *version[] = {"HTTP/0.9", "HTTP/1.0", "HTTP/1.1", "HTTP/2.0"}; 

	message_line  = method[m] + space;
	message_line += URL + space; 
	message_line += version[v] + CRLF;

	return;
}

/**
 *	@brief	    Packetize HTTP request line with extension method	
 *	@param[in]  method
 *	@param[in]	URL
 *	@param[in]  version - HTTP_0_9/HTTP_1_0/HTTP_1_1...
 *	@param[out] None
 *	@return		None
 *	@note		The function can be called repeatedly, BUT only to save the latest setting.
 **/
void message::set_msg_line(const char *method, const char *URL, enum version v)
{
	string space = " ";
	string CRLF  = "\r\n";

	const char *version[] = {"HTTP/0.9", "HTTP/1.0", "HTTP/1.1", "HTTP/2.0"}; 

	message_line  = method + space;
	message_line += URL + space; 
	message_line += version[v] + CRLF;

	return;
}

/**
 *	@brief	    Packetize HTTP response line with official method	
 *	@param[in]  version - HTTP_0_9/HTTP_1_0/HTTP_1_1...
 *	@param[in]  stsCode - _100/_200/_301... 
 *	@param[in]  reason	
 *	@param[out] None
 *	@return		None
 *	@note		The function can be called repeatedly, BUT only to save the latest setting.
 **/
void message::set_msg_line(enum version v, enum stsCode sc, const char *reason)
{
	string space = " ";
	string CRLF  = "\r\n";

	const char *version[] = {"HTTP/0.9", "HTTP/1.0", "HTTP/1.1", "HTTP/2.0"}; 

	stringstream ss;
	ss << sc;

	message_line  = version[v] + space + ss.str() + space;
	message_line += reason + CRLF; 

	return;
}

/**
 *	@brief	    Packetize HTTP header with official general headers 
 *	@param[in]  header - general headers 
 *	@param[in]  val	   - the value of the header	
 *	@param[in]  param  - optional param of the val 
 *	@param[out] None
 *	@return		None
 *	@note		The function can be called repeatedly, AND all values can be saved.
 *	@warning	Except for certain headers, other headers should not be repeated
 **/
void message::set_msg_head(enum comm_header h, const char *val, const char *param)
{
	string space = " "	 ;
	string colon = ":"	 ;
	string CRLF  = "\r\n";
	string semic = ";"	 ;
	string _NULL = ""	 ;

	const char *header[] = {
		"Cache-Control", "Connection", "Date", "Proxy-Connection", "Trailer", "Transfer-Encoding", "Upgrade", "Via"
	};

	message_head += header[h] + colon + space; 
	message_head += val;
	message_head += (_NULL == param)?CRLF:(semic + space + param + CRLF);

	return;
}

/**
 *	@brief	    Packetize HTTP header with official request headers 
 *	@param[in]  header - request headers 
 *	@param[in]  val	   - the value of the header	
 *	@param[in]  param  - optional param of the val 
 *	@param[out] None
 *	@return		None
 *	@note		The function can be called repeatedly, AND all values can be saved.
 *	@warning	Except for certain headers, other headers should not be repeated
 **/
void message::set_msg_head(enum rqst_header h, const char *val, const char *param)
{
	string space = " "	 ;
	string colon = ":"	 ;
	string CRLF  = "\r\n";
	string semic = ";"	 ;
	string _NULL = ""	 ;

	const char *header[] = {
		"Accept", "Accept-Charset", "Accept-Encoding", "Accept-Language", "Expect", "From", "Host", "If-Modified-Since", "If-Match", "If-None-Match", 
		"If-Range", "If-Unmodified-Since", "Max-Forwards", "Pragma", "Proxy-Authorization", "Referer", "User-Agent"
	};

	message_head += header[h] + colon + space; 
	message_head += val;
	message_head += (_NULL == param)?CRLF:(semic + space + param + CRLF);

	return;
}

/**
 *	@brief	    Packetize HTTP header with official response headers 
 *	@param[in]  header - response headers 
 *	@param[in]  val	   - the value of the header	
 *	@param[in]  param  - optional param of the val 
 *	@param[out] None
 *	@return		None
 *	@note		The function can be called repeatedly, AND all values can be saved.
 *	@warning	Except for certain headers, other headers should not be repeated
 **/
void message::set_msg_head(enum rsps_header h, const char *val, const char *param)
{
	string space = " "	 ;
	string colon = ":"	 ;
	string CRLF  = "\r\n";
	string semic = ";"	 ;
	string _NULL = ""	 ;

	const char *header[] = {
		"Accept-Ranges", "Age", "Allow", "Authorization", "Location", "Proxy-Authenticate", "Public", "Retry-After",
		"Server", "Title", "Vary", "Warning", "WWW-Authenticate"
	};

	message_head += header[h] + colon + space; 
	message_head += val;
	message_head += (_NULL == param)?CRLF:(semic + space + param + CRLF);

	return;
}

/**
 *	@brief	    Packetize HTTP header with official entity headers 
 *	@param[in]  header - entiry headers
 *	@param[in]  val	   - the value of the header	
 *	@param[in]  param  - optional param of the val 
 *	@param[out] None
 *	@return		None
 *	@note		The function can be called repeatedly, AND all values can be saved.
 *	@warning	Except for certain headers, other headers should not be repeated
 **/
void message::set_msg_head(enum body_header h, const char *val, const char *param)
{
	string space = " "	 ;
	string colon = ":"	 ;
	string CRLF  = "\r\n";
	string semic = ";"	 ;
	string _NULL = ""	 ;

	const char *header[] = {
		"Content-Encoding", "Content-Language", "Content-Length", "Content-MD5", "Content-Range", "ETag", "Expires", "Last-Modified", "Range"
	};

	message_head += header[h] + colon + space; 
	message_head += val;
	message_head += (_NULL == param)?CRLF:(semic + space + param + CRLF);

	return;
}

/**
 *	@brief	    Packetize HTTP header with extension headers 
 *	@param[in]  header
 *	@param[in]  val		- the value of the header	
 *	@param[in]  param   - optional param of the val 
 *	@param[out] None
 *	@return		None
 *	@note		The function can be called repeatedly, AND all values can be saved.
 *	@warning	Except for certain headers, other headers should not be repeated
 **/
void message::set_msg_head(const char *header, const char *val, const char *param)
{
	string space = " "	 ;
	string colon = ":"	 ;
	string CRLF  = "\r\n";
	string semic = ";"	 ;
	string _NULL = ""	 ;
	
	message_head += header + colon + space; 
	message_head += val;
	message_head += (_NULL == param)?CRLF:(semic + space + param + CRLF);

	return;
}

