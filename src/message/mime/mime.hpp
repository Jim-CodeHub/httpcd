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
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


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
		void set_msg_head(enum mime_mulsub m, string &boundary);

		void set_msg_body(const char *path, off_t offset, off_t len);
		void set_msg_body(const void *data, size_t len);
		void set_msg_part(string boundary, string data);
		void set_msg_over(string boundary);

		string packaging_messages(void);

		string construct_boundary(void);

	protected:
		string message_head;
		string message_body;
};

	
} /*< NS_LIBHTTP */


#endif /*__LIBHTTP_MIME_HPP__*/

