#include <httpcd/httpcd.hpp>
#include <iostream>

using namespace std;

USING_NAMESPACE_HTTPCD;


void msg_cgi(class http_server &server) 
{
	/**<-------------------------------------------------------------------------------*/
	/**< Recv HTTP message from client */

	server.recv();

	/**<-------------------------------------------------------------------------------*/
	/**< Parse HTTP message that recived from client */

	cout << "LINE      ::" << server.get_msg_line()			    	     << endl;

	cout << "URL       ::" << server.get_msg_URL()				         << endl;
	cout << "VERSION   ::" << server.get_msg_version(1)				     << endl;

	cout << "HEAD_CTYPE::" << server.get_msg_head(Content_Type)		     << endl; 
	//...

	cout << "PART0_BODY::" << server.get_msg_part(0)->get_sdbody().get() << endl;
	cout << "PART1_BODY::" << server.get_msg_part(1)->get_sdbody().get() << endl;
	//cout << "PART2_BODY::" << server.get_msg_part(2)->get_sdbody().get() << endl;
	server.get_msg_part(2)->get_sdbody().fill("./copy.pdf");
	//...

	/**<-------------------------------------------------------------------------------*/
	/**< Set HTTP message for client */ 

	server.clear();
	server.set_msg_line(HTTP_1_1, _201, "OK");

	server.set_msg_head(Content_Type, "Text/plain");
	server.set_msg_body("Server has recived message", 26);

	/**<-------------------------------------------------------------------------------*/
	/**< Send HTTP message to server */

	server.send(); return;
}

int main(void)
{
	/**<-------------------------------------------------------------------------------*/
	/**< Init HTTP server */

	class http_server server("127.0.0.1", msg_cgi); /**< OR 'server.init(...)' */

	/**<-------------------------------------------------------------------------------*/
	/**< Start HTTP server */

	server.emit();

	/**< SHOULD NOT SET ANY CODE BELOW ! */

	return 0;
}

