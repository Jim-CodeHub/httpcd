#include <httpcd/httpcd.hpp>
#include <iostream>

using namespace std;
USING_NAMESPACE_HTTPCD;

#define  URLs		"https://mirrors.edge.kernel.org/pub/linux/docs/lkml/reporting-bugs.html"

int main(void)
{
	URL_Parser URL( URLs );

	string HOST = URL.getHostName();

	list<string> LS	 = URL.getAddrList();

	list<string>::iterator _big = LS.begin(), _end = LS.end();


	class http_client client;	
					  client.init((*_big).c_str());

	client.rst_rcv_size(1024*1024*100); //100M

	client.set_msg_line( GET, URLs, HTTP_1_0);
	client.set_msg_head(Accept, "*/*");
	client.set_msg_head(Host, HOST.c_str());
	client.set_msg_head(Connection, "close");

	client.emit();

	cout << "Request IP	List: " << endl;

	for ( ; _big != _end; _big++ ) 
	{
		cout << *_big << endl;
	}

	client.recv();

	cout << "Response Line	: " << client.get_msg_line() <<endl;

	FILE *fp = fopen("./test.html", "w");

	string body = client.get_msg_body();

	fwrite(body.c_str(), body.size(), 1, fp);

	return 0;
}

