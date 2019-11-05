/**-----------------------------------------------------------------------------------------------------------------
 * @file	_string.cpp
 *
 * Copyright (c) 2019-2019 Jim Zhang 303683086@qq.com
 *------------------------------------------------------------------------------------------------------------------
*/


#include "_string.hpp"


/*-----------------------------------------------------------------------------------------------------------------
 * 
 *                                          FUNCTION PROTOTYPES
 *
 *------------------------------------------------------------------------------------------------------------------
*/


/*-----------------------------------------------------------------------------------------------------------------
 * 
 *                                          FUNCTIONS IMPLEMENT
 *
 *------------------------------------------------------------------------------------------------------------------
*/
/**
 *	@brief		Returns the string of the specified position that has been split by token 
 *	@param[in]	src	   - source string 
 *	@param[in]  delim  - token delimeter 	
 *	@param[in]  pos    - position of token string 
 *	@param[out] None 
 *	@return		Token string at position 'pos'	
 **/
char *_strtok(const char *src, const char *delim, int pos)
{
	int index = 0;
	char *ptr = strtok((char *)src, delim);

	while((ptr != NULL) && (++index != pos))
	{
		ptr = strtok(NULL, delim);
	}

	return ptr;
}
 
/**
 *	@brief		Returns the string of the specified position that has been split by token 
 *	@param[in]	src	  - source string 
 *	@param[in]  delim - token delimeter 	
 *	@param[in]  pos   - position of token string 
 *	@param[out] rPtr  - strings pointers of left behind in 'src' 
 *	@return		Token string at position 'pos'	
 **/
char *_strtok(const char *src, const char *delim, int pos, char *rPtr[])
{
	int index = 0;
	char *ptr = strtok_r((char *)src, delim, rPtr);

	while((ptr != NULL) && (++index != pos))
	{
		ptr = strtok_r(NULL, delim, rPtr);
	}

	return ptr;
}

