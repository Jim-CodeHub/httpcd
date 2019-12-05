#include <httpcd/httpcd.hpp>
#include <iostream>

using namespace std;

USING_NAMESPACE_HTTPCD;


void msg_cgi(int cfd, const struct sockaddr_in *caddr) 
{
	char buff[1000];

	recv(cfd, buff, sizeof(buff), 0);
	send(cfd, "Server : Hello client", 14, 0);

	cout << buff << endl; /**< Print client message */
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

