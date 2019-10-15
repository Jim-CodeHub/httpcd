/**-----------------------------------------------------------------------------------------------------------------
 * @file	message.cpp
 * @brief	packetize and depacketize HTTP message
 *
 * Copyright (c) 2019-2019 Jim Zhang 30363086@qq.com
 *------------------------------------------------------------------------------------------------------------------
*/

#include "message.hpp"


using namespace NS_LIBHTTP;


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
 *	@brief	    Packetize HTTP header with official headers 
 *	@param[in]  header - Cache_Control/Content_Base/Accept... 
 *	@param[in]  val	   - the value of the header	
 *	@param[in]  param   - optional param of the val 
 *	@param[out] None
 *	@return		None
 *	@note		The function can be called repeatedly, AND all values can be saved.
 *	@warning	Except for certain headers, other headers should not be repeated
 **/
void message::set_msg_head(enum header h, const char *val, const char *param)
{
	string space = " ";
	string colon = ":";
	string CRLF  = "\r\n";
	string semic = ";";

	const char *header[] = {
	    "Cache-Control", "Connection", "Date", "Proxy-Connection", "Trailer", "Transfer-Encoding", "Upgrade", "Via", 

	    "Content-Base", "Content-Encoding", "Content-Language", "Content-Length", "Content-Location", "Content-MD5", "Content-Range", "Content-Type",
	    "ETag", "Expires", "Last-Modified", "Range",

	    "Accept", "Accept-Charset", "Accept-Encoding", "Accept-Language", "Expect", "From", "Host", "If-Modified-Since", "If-Match", "If-None-Match", 
	    "If-Range", "If-Unmodified-Since", "Max-Forwards", "Pragma", "Proxy-Authorization", "Referer", "User-Agent",

		"Accept_Ranges", "Age", "Allow", "Authorization", "Location", "Proxy_Authenticate", "Public", "Retry_After",
		"Server", "Title", "Vary", "Warning", "WWW_Authenticate" 
	};

	message_head += header[h] + colon + space; 
	message_head += val;
	message_head += ("" == param)?CRLF:(semic + space + param + CRLF);

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
	string space = " ";
	string colon = ":";
	string CRLF  = "\r\n";
	string semic = ";";
	
	message_head += header + colon + space; 
	message_head += val;
	message_head += ("" == param)?CRLF:(semic + space + param + CRLF);

	return;
}

/**
 *	@brief	    Packetize HTTP Entity body with MIME
 *	@param[in]  MIME	- HTTP Entity body  
 *	@param[out] None
 *	@return		None
 *	@note		The function can be called repeatedly, BUT only to save the latest setting.
 **/
void message::set_msg_body(const char *MIME)
{
	string CRLF  = "\r\n";

	message_body = CRLF;

	message_body += MIME;

	return;
}




int main(void)
{
}

