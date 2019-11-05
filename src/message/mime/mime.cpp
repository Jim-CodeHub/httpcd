/**-----------------------------------------------------------------------------------------------------------------
 * @file	mime.cpp
 * @brief	MIME Assemply, parser etc.
 * @ref		RFC2045, RFC2046, RFC2047, RFC2049
 *
 * Copyright (c) 2019-2019 Jim Zhang 303683086@qq.com
 *------------------------------------------------------------------------------------------------------------------
*/

#include "mime.hpp"


using namespace NS_LIBHTTP;


/*
--------------------------------------------------------------------------------------------------------------------
*
*			                                  FUNCTIONS IMPLEMENT
*
--------------------------------------------------------------------------------------------------------------------
*/

/**
 *	@brief	    Construct boundary for MIME multipart type 
 *	@param[in]  None 
 *	@param[out] None 
 *	@return	    boudnary string	
 *	@note		The function will not produce duplicate values for at leaset 256 calls 
 **/
string mime::construct_boundary(void)
{
	static unsigned char seed_count = 0;

	string boundary;
	char   asciibet[] = "abcdefghijklmnopqrstuvwxyz_()+/=,:?'ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	auto time_ms = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch());

	default_random_engine e(time_ms.count() + (seed_count++));

	stringstream ss;

	ss << e(); ss >> boundary;

	boundary.insert(boundary.end(), seed_count % 70, asciibet[seed_count % sizeof(asciibet)]);

	return boundary.substr(0, 70);  /**< The length of the Upper limit : 70 */
}

/**
 *	@brief	    Packetize MIME header with official headers 
 *	@param[in]  header
 *	@param[in]  val	   - the value of the header	
 *	@param[in]  param  - optional param of the val 
 *	@param[out] None
 *	@return		None
 *	@note		The function can be called repeatedly, AND all values can be saved.
 *	@warning	Except for certain headers, other headers should not be repeated
 **/
void mime::set_msg_head(enum mime_header h, const char *val, const char *param)
{
	string space = " "	 ;
	string colon = ":"	 ;
	string CRLF  = "\r\n";
	string semic = ";"	 ;
	string _NULL = ""	 ;

	const char *header[] = {
		"Content-Base", "Content-Location", "Content-Type", "Content-ID", "Content-Transfer-Encoding", "MIME-Version"
	};

	message_head += header[h] + colon + space; 
	message_head += val;
	message_head += (_NULL == param)?CRLF:(semic + space + param + CRLF);

	return;
}

/**
 *	@brief	    Packetize MIME header with Content-Type headers in multipart type 
 *	@param[in]  m		 - Sub types of multipart   
 *	@param[in]  boundary - Multipart boundary 
 *	@param[out] None
 *	@return		None
 *	@warning	The function SHOULD NOT BE called repeatedly
 **/
void mime::set_msg_head(enum mime_mulsub m, string &boundary)
{
	string space = " "	 ;
	string colon = ":"	 ;
	string CRLF  = "\r\n";
	string semic = ";"	 ;
	string _NULL = ""	 ;
	string slash = "/"	 ;
	string equal = "="   ;

	const char *sub_type[] = {
		"mixed", "alternative", "digest", "parallel", "related"
	};

	message_head += "Content-Type" + colon + space; 
	message_head += "multipart" + slash;
	message_head += sub_type[m] + semic + space;
	message_head += "boundary" + equal; 
	message_head += boundary + CRLF;

	return;
}

/**
 *	@brief	    Packetize MIME body with any type of data in the file 
 *	@param[in]  path   - file path 
 *	@param[in]  offset - content start location 
 *	@param[in]  len    - data length 
 *	@param[out] None
 *	@return		None
 *	@note		The function can be called repeatedly, BUT only to save the latest setting.
 *	@note		If param 'len' is set to zero or larger than the file length, all file content will be set to message 
 **/
void mime::set_msg_body(const char *path, off_t offset, off_t len)
{
	int fd, ret = 0		;
	off_t off, size		;
	string CRLF = "\r\n";

	fd = open(path, O_RDONLY);

	if (-1 == fd)  {throw "Body set failure : file open error";}

	off = lseek(fd, offset, SEEK_END);
		  lseek(fd, offset, SEEK_SET);

	if (-1 == off) {throw "Body set failure : file seek error";}

	size = ((0 == len) || (len >= off))?off:len;

	char data[size]; //+ \0

	ret = read(fd, data, len);

	if (-1 == ret) {throw "Body set failure : file read error";}

	message_body  = CRLF;
	message_body += data + CRLF;

	return;
}

/**
 *	@brief	    Packetize MIME body with any type of data
 *	@param[in]  data
 *	@param[in]  len    - data length 
 *	@param[out] None
 *	@return		None
 *	@note		The function can be called repeatedly, BUT only to save the latest setting.
 **/
void mime::set_msg_body(const void *data, size_t len)
{
	string CRLF   = "\r\n";

	char *pdata   = (char *)data;

	message_body  = CRLF;

	while(len--) {message_body += *pdata; pdata++;}

	message_body += CRLF;

	return;
}

/**
 *	@brief	    Packetize MIME body-part with boundary 
 *	@param[in]  boundary - Multipart boundary 
 *	@param[in]  data
 *	@param[out] None
 *	@return		None
 *	@note		The function can be called repeatedly, AND all parts can be saved.
 **/
void mime::set_msg_part(string boundary, string data)
{
	string CRLF = "\r\n";
	string PREF = "--"  ;

	message_body += CRLF;
	message_body += PREF + boundary + CRLF;
	message_body += data + CRLF; 

	return;
}

/**
 *	@brief	    Packetize MIME body-part with boundary end sign 
 *	@param[in]  boundary - Multipart boundary 
 *	@param[out] None
 *	@return		None
 *	@note		The function works with function 'set_msg_part' to mark the body-part end 
 *	@note		The function SHOULD NOT be called repeatedly
 **/
void mime::set_msg_over(string boundary)
{
	string CRLF = "\r\n";
	string PREF = "--"  ;

	message_body += PREF + boundary + PREF; 
	message_body += CRLF;

	return;
}

