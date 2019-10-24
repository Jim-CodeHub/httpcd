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


#if 0

//头部 首部类型
	
	Content_Type语法：
		Content-Type: type/subtype; parameter //后面;parameter 是可选的
		
				multipart
					1. 每个部分的前面使用分隔符分隔，最后一个部分的最后使用关闭分隔符标记
					2. 每个部分，分隔符之后是头部，头部后面是空白行，然后使该部分的主体
					3. 每个部分，可以没有头部，此时该部分的内容被理解为头部是默认值的情况(Content-Type: text/plain; charset=US-ASCII)
					4. 分隔符在整个消息中必须唯一，不能与头部和body的任何内容重复，这就需要程序去生成
					5. 分隔符和头部（包含part的头部）都表示为7bit的ASCII值，（头部经过扩展的除外RFC2047），而每个部分的body数据可以编码为自己想要的编码

					语法：
					Content-Type: multipart/xxx; boundary=paramterVal
					Content-Type: multipart/xxx; boundary="paramterVal" //这里的引号是可选的，使用是为了避免参数值里有冒号等信息

					--paramterVal //a. 使用时是一样的，有引号的要去掉
					边界分隔符不能超过70个(不包含前缀--)(1~70), 且不能以空白结尾
					如果以空白结尾，则必须删除

					--paramterVal-- //b, 表示后面不再有part

					//body中 ， a 之前的内容 和 b之后的内容都应该被忽略
				
					part格式：

					some text that will be ignored CRLF
					--uniqboundaryparamval *LWSP CRLF	//LWSP = liner-white-space, 在这里是可选的
					MIME-part-headers [CRLF *OCTET] CRLF //这里[]表示可选， *表示0~多个，[CRLF *OCTET]的含义是 partbody内容可有可无，有的时候先写一个CRLF，然后是内容
					--uniqboundaryparamval *LWSP CRLF
					MIME-part-headers [CRLF *OCTET] CRLF	
					--uniqboundaryparamval *LWSP CRLF
					MIME-part-headers [CRLF *OCTET] CRLF	
					--uniqboundaryparamval *LWSP CRLF
					...
					CRLF
					--uniqboundaryparamval-- *LWSP
					CRLF
					some text that will be ignored
				










uint64_t generateBoundary(void)
{
	random_device rd;
	mt19937 mt(rd());

	return mt();
}



#endif


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



	//message_head += boundary;  

	return;
}


