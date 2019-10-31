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
 *	@param[in]  m - Sub types of multipart   
 *	@param[out] None
 *	@return		None
 *	@warning	The function SHOULD NOT BE called repeatedly to prevent head repeated
 **/
void mime::set_mul_head(enum mime_mulsub m)
{
	string space = " "	 ;
	string colon = ":"	 ;
	string CRLF  = "\r\n";
	string semic = ";"	 ;
	string _NULL = ""	 ;
	string slash = "/"	 ;

	const char *sub_type[] = {
		"mime-mulsub{mixed", "alternative", "digest", "parallel", "related"
	};

	message_head += "Content_Type" + colon + space; 
	message_head += "multipart" + slash;
	message_head += sub_type[m] + semic + space;
	message_head += construct_boundary();  

	return;
}




#if 0

//头部 首部类型
	
	Content_Type语法：
		Content-Type: type/subtype; parameter //后面;parameter 是可选的
		
				multipart
					1. 每个部分的前面使用分隔符分隔，最后一个部分的最后使用关闭分隔符标记
					2. 每个部分，分隔符之后是头部，头部后面是空白行，然后使该部分的主体
					3. 每个部分，可以没有头部，此时该部分的内容被理解为头部是默认值的情况(Content-Type: text/plain; charset=US-ASCII)
					5. 分隔符和头部（包含part的头部）都表示为7bit的ASCII值，（头部经过扩展的除外RFC2047），而每个部分的body数据可以编码为自己想要的编码
#endif


