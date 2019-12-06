#include <httpcd/httpcd.hpp>
#include <iostream>

using namespace std;

USING_NAMESPACE_HTTPCD;


void msg_cgi(int cfd, const struct sockaddr_in *caddr) 
{
	/**<------------------------------------------------------*/
	/**< Recv message */

	char _recv[1024*100];

	recv(cfd, _recv, sizeof(_recv), 0);

	/**<------------------------------------------------------*/
	/**< Load message from buff */

	class message msg; msg.load_msg(_recv, sizeof(_recv));

	char _send[] = "Server : Message loaded";

	send(cfd, _send, sizeof(_send), 0);

	/**<------------------------------------------------------*/
	/**< Load message from buff */

	cout << msg.pack_msg() <<endl;
}

int main(void)
{
	class httpd _server;

//	_server.set_deamon(1);

	_server.server_init("127.0.0.1", msg_cgi);
	_server.server_emit();

	/**< SHOULD NOT SET ANY CODE BELOW ! */

	return 0;
}

