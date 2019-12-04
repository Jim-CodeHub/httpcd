/**-----------------------------------------------------------------------------------------------------------------
 * @file	message.cpp
 * @brief	packetize and depacketize HTTP message
 *
 * Copyright (c) 2019-2019 Jim Zhang 303683086@qq.com
 *------------------------------------------------------------------------------------------------------------------
*/

#include <httpcd/message/message.hpp>


using namespace NS_HTTPCD;


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
 *	@param[in]  body   - field_body which suiable the header (field_bame)
 *	@param[out] None
 *	@return		None
 *	@note		The function can be called repeatedly, AND all values can be saved.
 *	@warning	Except for certain headers, other headers should not be repeated
 **/
void message::set_msg_head(enum comm_header h, const class field_body *body)
{
	const char *header[] = {
		"Cache-Control", "Connection", "Date", "Proxy-Connection", "Trailer", "Transfer-Encoding", "Upgrade", "Via"
	};

	this->header.set(header[h], body);
	return;
}

/**
 *	@brief	    Packetize HTTP header with official request headers 
 *	@param[in]  header - request headers 
 *	@param[in]  body   - field_body which suiable the header (field_bame)
 *	@param[out] None
 *	@return		None
 *	@note		The function can be called repeatedly, AND all values can be saved.
 *	@warning	Except for certain headers, other headers should not be repeated
 **/
void message::set_msg_head(enum rqst_header h, const class field_body *body)
{
	const char *header[] = {
		"Accept", "Accept-Charset", "Accept-Encoding", "Accept-Language", "Expect", "From", "Host", "If-Modified-Since", "If-Match", "If-None-Match", 
		"If-Range", "If-Unmodified-Since", "Max-Forwards", "Pragma", "Proxy-Authorization", "Referer", "User-Agent"
	};

	this->header.set(header[h], body);
	return;
}

/**
 *	@brief	    Packetize HTTP header with official response headers 
 *	@param[in]  header - response headers 
 *	@param[in]  body   - field_body which suiable the header (field_bame)
 *	@param[out] None
 *	@return		None
 *	@note		The function can be called repeatedly, AND all values can be saved.
 *	@warning	Except for certain headers, other headers should not be repeated
 **/
void message::set_msg_head(enum rsps_header h, const class field_body *body)
{
	const char *header[] = {
		"Accept-Ranges", "Age", "Allow", "Authorization", "Location", "Proxy-Authenticate", "Public", "Retry-After",
		"Server", "Title", "Vary", "Warning", "WWW-Authenticate"
	};

	this->header.set(header[h], body);
	return;
}

/**
 *	@brief	    Packetize HTTP header with official entity headers 
 *	@param[in]  header - entity headers
 *	@param[in]  body   - field_body which suiable the header (field_bame)
 *	@param[out] None
 *	@return		None
 *	@note		The function can be called repeatedly, AND all values can be saved.
 *	@warning	Except for certain headers, other headers should not be repeated
 **/
void message::set_msg_head(enum body_header h, const class field_body *body)
{
	const char *header[] = {
		"Content-Encoding", "Content-Language", "Content-Length", "Content-MD5", "Content-Range", "ETag", "Expires", "Last-Modified", "Range"
	};

	this->header.set(header[h], body);
	return;
}

/**
 *	@brief	    Packetize HTTP header with official entity headers 
 *	@param[in]  header - entity headers
 *	@param[in]  body   - field_body which suiable the header (field_bame)
 *	@param[out] None
 *	@return		None
 *	@note		The function can be called repeatedly, AND all values can be saved.
 *	@warning	Except for certain headers, other headers should not be repeated
 **/
void message::set_msg_head(const string &field_name, const class field_body *body)
{
	this->header.set(field_name, body);
	return;
}

/**
 *	@brief	    Packetize HTTP header with official entity headers 
 *	@param[in]  header - entity headers
 *	@param[in]  body   - field_body which suiable the header (field_bame)
 *	@param[out] None
 *	@return		None
 *	@note		The function can be called repeatedly, AND all values can be saved.
 *	@warning	Except for certain headers, other headers should not be repeated
 **/
void message::set_msg_head(const string &field_name, const string &field_body)
{
	class string_body str_body(field_body );
	this->header.set(field_name, &str_body);

	return;
}

/**
 *	@brief	    Get message line
 *	@param[in]  None 
 *	@param[out] None
 *	@return		HTTP message line	
 **/
const string &message::get_msg_line(void) const noexcept
{
	return this->message_line;	
}

/**
 *	@brief	    Get (request) message method
 *	@param[in]	None 
 *	@param[out] None
 *	@return		HTTP message method 
 **/
const string message::get_msg_method(void) const noexcept
{
	class string_token str_tok(message_line, " ");

	return str_tok.get_stok(0);
}

/**
 *	@brief	    Get (request) message URL 
 *	@param[in]  None 
 *	@param[out] None
 *	@return		HTTP message URL 
 **/
const string message::get_msg_URL(const void *message) const noexcept
{
	class string_token str_tok(message_line, " ");

	return str_tok.get_stok(1);
}

/**
 *	@brief	    Get (request/response) message version 
 *	@param[in]  dir		- 1/true for reqeust, 0/flase for response 
 *	@param[out] None
 *	@return		HTTP message version 
 **/
const string message::get_msg_version(bool dir) const noexcept
{
	class string_token str_tok(message_line, " ");

	return str_tok.get_stok((true==dir)?2:0);
}

/**
 *	@brief	    Get (response) message status 
 *	@param[in]  None 
 *	@param[out] None
 *	@return		HTTP message status 
 **/
const string message::get_msg_status(void) const noexcept
{
	class string_token str_tok(message_line, " ");

	return str_tok.get_stok(1);
}

/**
 *	@brief	    Get message  header (RET field_body) with certain enumeration 
 *	@param[in]  h  - certain header (IN  field_bame) enumeration      
 *	@param[out] None
 *	@return		HTTP message header (field_body) or "" (empty)
 **/
const string message::get_msg_head(enum MIME_FNAME fname_t) const noexcept 
{
	return this->header.get_field(fname_t).get_body();
}

/**
 *	@brief	    Get message  header (RET field_body) with certain enumeration 
 *	@param[in]  h  - certain header (IN  field_bame) enumeration      
 *	@param[out] None
 *	@return		HTTP message header (field_body) or "" (empty)
 **/
const string message::get_msg_head(enum comm_header h) const noexcept
{
	const char *header[] = {
		"Cache-Control", "Connection", "Date", "Proxy-Connection", "Trailer", "Transfer-Encoding", "Upgrade", "Via"
	};

	return this->header.header::get_field(header[h]).get_body();
}

/**
 *	@brief	    Get message  header (RET field_body) with certain enumeration 
 *	@param[in]  h  - certain header (IN  field_bame) enumeration      
 *	@param[out] None
 *	@return		HTTP message header (field_body) or "" (empty)
 **/
const string message::get_msg_head(enum rqst_header h) const noexcept
{
	const char *header[] = {
		"Accept", "Accept-Charset", "Accept-Encoding", "Accept-Language", "Expect", "From", "Host", "If-Modified-Since", "If-Match", "If-None-Match", 
		"If-Range", "If-Unmodified-Since", "Max-Forwards", "Pragma", "Proxy-Authorization", "Referer", "User-Agent"
	};

	return this->header.header::get_field(header[h]).get_body();
}

/**
 *	@brief	    Get message  header (RET field_body) with certain enumeration 
 *	@param[in]  h  - certain header (IN  field_bame) enumeration      
 *	@param[out] None
 *	@return		HTTP message header (field_body) or "" (empty)
 **/
const string message::get_msg_head(enum rsps_header h) const noexcept
{
	const char *header[] = {
		"Accept-Ranges", "Age", "Allow", "Authorization", "Location", "Proxy-Authenticate", "Public", "Retry-After",
		"Server", "Title", "Vary", "Warning", "WWW-Authenticate"
	};

	return this->header.header::get_field(header[h]).get_body();
}

/**
 *	@brief	    Get message  header (RET field_body) with certain enumeration 
 *	@param[in]  h  - certain header (IN  field_bame) enumeration      
 *	@param[out] None
 *	@return		HTTP message header (field_body) or "" (empty)
 **/
const string message::get_msg_head(enum body_header h) const noexcept
{
	const char *header[] = {
		"Content-Encoding", "Content-Language", "Content-Length", "Content-MD5", "Content-Range", "ETag", "Expires", "Last-Modified", "Range"
	};

	return this->header.header::get_field(header[h]).get_body();
}

/**
 *	@brief	    Get message header with certain string 
 *	@param[in]  header
 *	@param[in]  message - HTTP message 
 *	@param[out] None
 *	@return		HTTP message head or "" (empty)
 **/
const string message::get_msg_head(const string &head) const noexcept
{
	return this->header.header::get_field(head).get_body();
}

/**
 *	@brief	    Packetize HTTP messages
 *	@param[in]  None 
 *	@param[out] None
 *	@return		HTTP messages	
 **/
const string message::pack_msg(void)
{
	return this->message_line + "\r\n" + this->make();
}

/**
 *	@brief	    Load HTTP message for further parsing
 *	@param[in]  None 
 *	@param[out] None
 *	@return		ture/flase (reserved interface) 	
 **/
bool message::load_msg(const string message)
{
	/**<---------------------------------------------------------*/
	/**< Load HTTP message line */

	class string_token str_tok; str_tok.cut(message, "\r\n");

	this->message_line = str_tok.get_stok(0);

	/**<---------------------------------------------------------*/
	/**< Load HTTP message entity */

	string mime_entity = str_tok.get_stok(1);

	return this->load(mime_entity);
}



#if 0

		//void set_msg_body();
		//const string get_msg_part(string::size_type _inx						);
		//const string get_msg_body(void);
		//
		const class body_shadow &get_sdbody(void) const noexcept				  ;

		const class mime_entity *get_part(string::size_type _inx) const noexcept  ;
#endif


