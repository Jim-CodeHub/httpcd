# Open source HTTP C/S library with C++ language

# Note
The library depends on library socketcd and libmime

# Install

$./contrib/download
$make contrib
$make 
$make install --PREFIX=xxx //By default, select current directory which under dir 'install'

# Usage

`#include <httpcd/httpcd.hpp>`

`USING_NAMESPACE_HTTPCD`

int main(void)
{
	class message msg;

	//Set header
	msg.set_msg_head(xxxx);

	//Set body OR set part 
	//[OPT 1] set body
	msg.set_msg_body(xxx);

	//[OPT 2] set part
	msg.set_msg_part(xHEAD)->set_node(xHEAD1, xBODY1);
	msg.set_msg_part(xHEAD)->set_node(xHEAD2, xBODY2);
	
	class mime_entity *p = set_msg_part(xHEAD); /**< Ready to nest part */

	p->set_msg_part(xHEAD3)->set_node(xHEAD4, xBODY4);
	.....

	//Package message
	string _msg = msg.pack_msg();
	....

	//MAY BE sent message by client
	class  httpc _client;

	_client.data_send(_msg.data(), _msg.size(), 0);
	...
}

*-g++ *.cpp  -lhttpcd -lsocketcd -lmime -lpthread -o *.out 
