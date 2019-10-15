/**-----------------------------------------------------------------------------------------------------------------
 * @file	message.hpp
 * @brief	packetize and depacketize HTTP message
 *
 * Copyright (c) 2019-2019 Jim Zhang 30363086@qq.com
 *------------------------------------------------------------------------------------------------------------------
*/


#ifndef __LIBHTTP_MESSAGE_HPP__
#define __LIBHTTP_MESSAGE_HPP__


/*-----------------------------------------------------------------------------------------------------------------
 * 
 *										LIBHTTP/MESSAGE INCLUDES 
 *
 *------------------------------------------------------------------------------------------------------------------
*/

#include <string>
#include <sstream>


namespace NS_LIBHTTP{

	
/*-----------------------------------------------------------------------------------------------------------------
 * 
 *										LIBHTTP/MESSAGE DATA BLOCK
 *
 *------------------------------------------------------------------------------------------------------------------
*/

/**
 *	@brief HTTP official request method 
 **/
enum method{GET, HEAD, PUT, POST, TRACE, OPTIONS, DELETE};

/**
 *	@brief HTTP official version 
 **/
enum version{HTTP_0_9, HTTP_1_0, HTTP_1_1, HTTP_2_0, HTTP_3_0};

/**
 *	@brief HTTP official status code 
 **/
enum stsCode{
	_100 = 100, _101,
	_200 = 200, _201, _202, _203, _204, _205, _206,
	_300 = 300, _301, _302, _303, _304, _305, _306, _307,
	_400 = 400, _401, _402, _403, _404, _405, _406, _407, _408, _409, _410, _411, _412, _413, _414, _415, _416, _417,
	_500 = 500, _501, _502, _503, _504, _505
};

/**
 *	@brief HTTP official request and response headers 
 **/
enum header{
	/**< General headers */
	Cache_Control, Connection, Date, Proxy_Connection, Trailer, Transfer_Encoding, Upgrade, Via, 

	/**< General entity headers */
	Content_Base, Content_Encoding, Content_Language, Content_Length, Content_Location, Content_MD5, Content_Range, Content_Type,
	ETag, Expires, Last_Modified, Range,

	/**< Request headers */
	Accept, Accept_Charset, Accept_Encoding, Accept_Language, Expect, From, Host, If_Modified_Since, If_Match, If_None_Match, 
	If_Range, If_Unmodified_Since, Max_Forwards, Pragma, Proxy_Authorization, Referer, User_Agent,

	/**< Response headers */
	Accept_Ranges, Age, Allow, Authorization, Location, Proxy_Authenticate, Public, Retry_After,
	Server, Title, Vary, Warning, WWW_Authenticate 
};//Content_ID? Content_Transfer_Encoding

/**
 *	@brief HTTP message class and function set 
 **/
class message{
	public:
		//message(); //TBD 

		void set_msg_line(enum method m, const char *URL, enum version v);
		void set_msg_line(const char *method, const char *URL, enum version v);
		void set_msg_line(enum version v, enum stsCode, const char *reason = "");

		void set_msg_head(enum header h, const char *val, const char *param = "");
		void set_msg_head(const char *header, const char *val, const char *param = "");

		void set_msg_body(const char *body);

		//static string get_msg_line(const char *msg);
		//static string get_msg_head(const char *msg);
		//static string get_msg_body(const char *msg);

	private:
		string message_line;
		string message_head;
		string message_body;
};


} /* namespace NS_LIBHTTP */


#endif /*__LIBHTTP_MESSAGE_HPP__*/

