/**-----------------------------------------------------------------------------------------------------------------
 * @file	message.hpp
 * @brief	packetize and depacketize HTTP message
 *
 * Copyright (c) 2019-2019 Jim Zhang 303683086@qq.com
 *------------------------------------------------------------------------------------------------------------------
*/


#ifndef __MESSAGE_HPP__
#define __MESSAGE_HPP__


/*------------------------------------------------------------------------------------------------------------------
 * 
 *										HTTPCD/MESSAGE INCLUDES 
 *
 *------------------------------------------------------------------------------------------------------------------
*/

#include <string>
#include <sstream>
#include <libmime/mime.hpp>


using namespace NS_LIBMIME;

namespace NS_HTTPCD{

/*------------------------------------------------------------------------------------------------------------------
 * 
 *										HTTPCD/MESSAGE DATA BLOCK
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
 *	@brief HTTP official general headers 
 **/
enum comm_header{
	Cache_Control, Connection, Date, Proxy_Connection, Trailer, Transfer_Encoding, Upgrade, Via
};

/**
 *	@brief HTTP official request headers 
 **/
enum rqst_header{
	Accept, Accept_Charset, Accept_Encoding, Accept_Language, Expect, From, Host, If_Modified_Since, If_Match, If_None_Match, 
	If_Range, If_Unmodified_Since, Max_Forwards, Pragma, Proxy_Authorization, Referer, User_Agent
};

/**
 *	@brief HTTP official response headers 
 **/
enum rsps_header{
	Accept_Ranges, Age, Allow, Authorization, Location, Proxy_Authenticate, Public, Retry_After,
	Server, Title, Vary, Warning, WWW_Authenticate 
};

/**
 *	@brief HTTP official entity headers 
 **/
enum body_header{
	Content_Encoding, Content_Language, Content_Length, Content_MD5, Content_Range, ETag, Expires, Last_Modified, Range
}; 

/**
 *	@brief HTTP message class and function set 
 **/
class message : public mime_message{
	public:
		message() { this->nest = true; } /**< Empty constructure */					 ;

		void set_msg_line(enum method m,      const char *URL, enum version v		);
		void set_msg_line(const char *method, const char *URL, enum version v		);
		void set_msg_line(enum version v, enum stsCode, const char *reason = ""		);

		void set_msg_head(enum comm_header h, const class field_body *body			);
		void set_msg_head(enum rqst_header h, const class field_body *body			);
		void set_msg_head(enum rsps_header h, const class field_body *body			);
		void set_msg_head(enum body_header h, const class field_body *body			);
		void set_msg_head(enum MIME_FNAME  h, const class field_body *body			);
		void set_msg_head(enum comm_header h, const string &field_body				);
		void set_msg_head(enum rqst_header h, const string &field_body				);
		void set_msg_head(enum rsps_header h, const string &field_body				);
		void set_msg_head(enum body_header h, const string &field_body				);
		void set_msg_head(enum MIME_FNAME  h, const string &field_body  			);
		void set_msg_head(const string &field_name, const class field_body *body	);
		void set_msg_head(const string &field_name, const string &field_body		);

		void set_msg_body(const char *body, string::size_type _size					);

		class mime_entity *set_msg_part(class mime_header &header					);
		class mime_entity *set_msg_part(void										);

		const string pack_msg(void													);
		bool		 load_msg(const string message									);
		bool		 load_msg(const char  *message, string::size_type _size	    	);

		const string &get_msg_line(void) const noexcept								 ;

		const string get_msg_method(void) const noexcept							 ;
		const string get_msg_version(bool dir) const noexcept						 ;
		const string get_msg_URL(const void *message) const noexcept				 ;
		const string get_msg_status(void) const noexcept							 ;

		const string get_msg_head(enum MIME_FNAME fname_t) const noexcept			 ;
		const string get_msg_head(enum comm_header h) const noexcept				 ;
		const string get_msg_head(enum rqst_header h) const noexcept				 ;
		const string get_msg_head(enum rsps_header h) const noexcept				 ;
		const string get_msg_head(enum body_header h) const noexcept				 ;
		const string get_msg_head(const string &head) const noexcept				 ;

		const string &get_msg_body(void												);

		const class mime_entity *get_msg_part(string::size_type _inx				);

	private:
		string message_line;
};


} /* namespace NS_HTTPCD */


#endif /*__MESSAGE_HPP__*/

