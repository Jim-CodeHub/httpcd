#include "src/message/message.hpp"
#include "src/comm/client/httpc.hpp"
#include "src/comm/server/httpd.hpp"
#include <iostream>

using namespace std;
using namespace NS_LIBHTTP;


int main(void)
{

	message msg;

	msg.set_msg_line(GET, "www.test.com", HTTP_1_1);


	string bound = msg.construct_boundary();
	msg.mime::set_msg_head(related, bound); 

		message msg2;
		msg2.set_msg_head(Content_Length, "120");
		msg2.mime::set_msg_head(Content_Type, "application/xml");
		msg2.set_msg_body("data2...", 8);

	msg.set_msg_part(bound, msg2.packaging_messages()); 

		message msg3;
		msg3.set_msg_head(Content_Length, "130");
		msg3.mime::set_msg_head(Content_Type, "application/jdf");
		msg3.set_msg_body("data3...", 8);

	msg.set_msg_part(bound, msg3.packaging_messages()); 
	msg.set_msg_over(bound);

	//msg.set_msg_head(Content_Length, to_string(msg.getBodySize()).c_str());
	msg.set_msg_head("Content-Length", msg.getBodySize());

	string m = msg.packaging_messages() ;

	cout << m << endl;

	cout << "-------------" << endl;

	//cout << message::get_msg_body(m.c_str()) << endl;
	
	cout << message::get_msg_part(1, m.c_str()) << endl;

	return 0;
}

