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
void message::set_msg_head(const char *header, size_t val, const char *param)
{
	set_msg_head(header, to_string(val).c_str(), param);

	return;
}

/**
 *	@brief	    Packetize HTTP messages
 *	@param[in]  None 
 *	@param[out] None
 *	@return		HTTP messages	
 **/
string message::packaging_messages(void)
{
	string message = message_line + message_head + message_body;

	return message;
}

/**
 *	@brief	    Get message line
 *	@param[in]  message - HTTP message 
 *	@param[out] None
 *	@return		HTTP message line	
 **/
string message::get_msg_line(const void *message)
{
	string line;

	char *p = (char *)message;

	while((*p != '\r') || (*(p + 1) != '\n')) { line += *p; p++; }

	return line;
}

/**
 *	@brief	    Get (request) message method
 *	@param[in]  message - HTTP method
 *	@param[out] None
 *	@return		HTTP message method 
 **/
string message::get_msg_method(const void *message)
{
	string line  = get_msg_line(message);

	return _strtok(line.c_str(), " ", 1);
}

/**
 *	@brief	    Get (request) message URL 
 *	@param[in]  message - HTTP message 
 *	@param[out] None
 *	@return		HTTP message URL 
 **/
string message::get_msg_URL(const void *message)
{
	string line  = get_msg_line(message);

	return _strtok(line.c_str(), " ", 2);
}

/**
 *	@brief	    Get (request/response) message version 
 *	@param[in]  dir		- 1/true for reqeust, 0/flase for response 
 *	@param[in]  message - HTTP message 
 *	@param[out] None
 *	@return		HTTP message version 
 **/
string message::get_msg_version(bool dir, const void *message)
{
	string line  = get_msg_line(message);

	return _strtok(line.c_str(), " ", (true==dir)?3:1);
}

/**
 *	@brief	    Get (response) message status 
 *	@param[in]  message - HTTP message 
 *	@param[out] None
 *	@return		HTTP message status 
 **/
string message::get_msg_status(const void *message)
{
	string line  = get_msg_line(message);

	return _strtok(line.c_str(), " ", 2);
}

/**
 *	@brief	    Get message heads 
 *	@param[in]  message - HTTP message 
 *	@param[out] None
 *	@return		HTTP message heads 
 **/
string message::get_msg_head(const void *message)
{
	string CRLF  = "\r\n";
	string head;

	char *p = (char *)message;

	while((*p != '\r') || (*(p + 1) != '\n')) {p++;} /**< Pass line */

	p++; p++; /**< Pass CR & LF */

	while(true)
	{
		if ((*p == '\r') && (*(p + 1) == '\n') && (*(p + 2) == '\r') && (*(p + 3) == '\n'))
		{
			head += CRLF; /**< Add the last CRLF */
			break;
		}

		head += *p; p++;
	}

	return head;
}

/**
 *	@brief	    Get message header with certain string 
 *	@param[in]  header
 *	@param[in]  message - HTTP message 
 *	@param[out] None
 *	@return		HTTP message head or "" (empty)
 **/
string message::get_msg_head(const char *header, const void *message)
{
	string head, set;

	set = get_msg_head(message);

	char *rPtr[1];

	char *str = _strtok(set.c_str(), "\r\n", 1, rPtr);

	while (NULL != str)
	{
		char *mPtr[1];
		if (strcmp(_strtok(str, ":", 1, mPtr), header) == 0)
		{
			head = mPtr[0]; break;
		}

		str = _strtok(rPtr[0], "\r\n", 1, rPtr);
	}

	return head.erase(0, 1); /**< Delete header space */
}

/**
 *	@brief	    Get message header with certain enumeration 
 *	@param[in]  h       
 *	@param[in]  message - HTTP message 
 *	@param[out] None
 *	@return		HTTP message head or "" (empty)
 **/
string message::get_msg_head(enum mime_header h, const void *message)
{
	const char *header[] = {
		"Content-Base", "Content-Location", "Content-Type", "Content-ID", "Content-Transfer-Encoding", "MIME-Version"
	};

	return get_msg_head(header[h], message); 
}

/**
 *	@brief	    Get message header with certain enumeration 
 *	@param[in]  h       
 *	@param[in]  message - HTTP message 
 *	@param[out] None
 *	@return		HTTP message head or "" (empty)
 **/
string message::get_msg_head(enum comm_header h, const void *message)
{
	const char *header[] = {
		"Cache-Control", "Connection", "Date", "Proxy-Connection", "Trailer", "Transfer-Encoding", "Upgrade", "Via"
	};

	return get_msg_head(header[h], message); 
}

/**
 *	@brief	    Get message header with certain enumeration 
 *	@param[in]  h       
 *	@param[in]  message - HTTP message 
 *	@param[out] None
 *	@return		HTTP message head or "" (empty)
 **/
string message::get_msg_head(enum rqst_header h, const void *message)
{
	const char *header[] = {
		"Accept", "Accept-Charset", "Accept-Encoding", "Accept-Language", "Expect", "From", "Host", "If-Modified-Since", "If-Match", "If-None-Match", 
		"If-Range", "If-Unmodified-Since", "Max-Forwards", "Pragma", "Proxy-Authorization", "Referer", "User-Agent"
	};

	return get_msg_head(header[h], message); 
}

/**
 *	@brief	    Get message header with certain enumeration 
 *	@param[in]  h       
 *	@param[in]  message - HTTP message 
 *	@param[out] None
 *	@return		HTTP message head or "" (empty)
 **/
string message::get_msg_head(enum rsps_header h, const void *message)
{
	const char *header[] = {
		"Accept-Ranges", "Age", "Allow", "Authorization", "Location", "Proxy-Authenticate", "Public", "Retry-After",
		"Server", "Title", "Vary", "Warning", "WWW-Authenticate"
	};

	return get_msg_head(header[h], message); 
}

/**
 *	@brief	    Get message header with certain enumeration 
 *	@param[in]  h       
 *	@param[in]  message - HTTP message 
 *	@param[out] None
 *	@return		HTTP message head or "" (empty)
 **/
string message::get_msg_head(enum body_header h, const void *message)
{
	const char *header[] = {
		"Content-Encoding", "Content-Language", "Content-Length", "Content-MD5", "Content-Range", "ETag", "Expires", "Last-Modified", "Range"
	};

	return get_msg_head(header[h], message); 
}

/**
 *	@brief	    Get message entity body
 *	@param[in]  message - HTTP message 
 *	@param[out] None
 *	@return		HTTP message head or "" (empty)
 **/
string message::get_msg_body(const void *message)
{
	int cLen	    ;
	string body, len;

	len = get_msg_head(Content_Length, message);

	if ("" == len) { return ""; }

	cLen = stoi(len);

	if (0 == cLen) { return ""; }

	char *p = (char *)message;

	while(true)
	{
		if ((*p == '\r') && (*(p + 1) == '\n') && (*(p + 2) == '\r') && (*(p + 3) == '\n'))
		{
			p += 4; /**< Pass CRLF CRLF */
			break;
		}

		p++;
	}

	while(cLen--) { body += *p; p++; }

	return body;
}

/**
 *	@brief	    Get message certain part
 *	@param[in]  part	- one of body part 
 *	@param[in]  message - HTTP message 
 *	@param[out] None
 *	@return		HTTP message head or "" (empty or non multi mode)
 **/
string message::get_msg_part(int part, const void *message)
{
	/**< Check legitimacy and Get boundary */
	string type = get_msg_head(Content_Type, message);

	if ("" == type) { return ""; }

	string subType = type;
	if (strcmp("multipart", _strtok(subType.c_str(), "/", 1)) != 0)
	{
		return "";	
	}

	string boundary = _strtok(type.c_str(), "=", 2);

	/**< Get message part */
	string s_bd = "--" + boundary, e_bd = s_bd + "--"; 

	string body = get_msg_body(message);

	return "";
}

