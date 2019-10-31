/**-----------------------------------------------------------------------------------------------------------------
 * @file	mime.hpp
 * @brief	MIME Assemply, parser etc.
 * @ref		RFC2045, RFC2046, RFC2047, RFC2049
 *
 * Copyright (c) 2019-2019 Jim Zhang 303683086@qq.com
 *------------------------------------------------------------------------------------------------------------------
*/


#ifndef __LIBHTTP_MIME_HPP__
#define __LIBHTTP_MIME_HPP__


/*------------------------------------------------------------------------------------------------------------------
 * 
 *											LIBHTTP/MIME INCLUDES 
 *
 *------------------------------------------------------------------------------------------------------------------
*/

#include <random>
#include <chrono>
#include <sstream>
#include "encoding/Base64.hpp"



#include <iostream>
using namespace std;


namespace NS_LIBHTTP{


/*------------------------------------------------------------------------------------------------------------------
 * 
 *										    LIBHTTP/MIME DATA BLOCK
 *
 *------------------------------------------------------------------------------------------------------------------
*/

/**
 *	@brief MIME official headers 
 **/
enum mime_header{
	Content_Base, Content_Location, Content_Type, Content_ID, Content_Transfer_Encoding, MIME_Version
};

/**
 *	@brief MIME Content-Type field, multipart sub types 
 **/
enum mime_mulsub{mixed, alternative, digest, parallel, related};

/**
 *	@brief MIME class and function set 
 **/
class mime{
	public:
		void set_msg_head(enum mime_header h, const char *val, const char *param = "");
		void set_mul_head(enum mime_mulsub);

		void set_msg_body(const void *data, size_t len);
		void set_mul_part();
		void set_mul_over();

		void show(void){cout << message_head<< endl;}
		void showb(void){cout << message_body<< endl;}

	protected:
		string message_head;
		string message_body;

		string mul_boundary;

		string construct_boundary(void);
};

	
} /*< NS_LIBHTTP */


#endif /*__LIBHTTP_MIME_HPP__*/

