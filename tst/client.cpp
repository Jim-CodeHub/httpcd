#include <httpcd/httpcd.hpp>
#include <iostream>

using namespace std;
USING_NAMESPACE_HTTPCD;


int main(void)
{
	/**<------------------------------------------------------------*/
	/**< Set HTTP message */

	message msg;

	msg.set_msg_line(POST, "127.0.0.1", HTTP_1_1);

	msg.set_msg_head(Content_Type, "multipart/related");
	msg.set_msg_head(Content_Transfer_Encoding, "7bit");

	class mime_header part_1_header;
					  part_1_header.set(Content_Type, "application/vnd.cip4 - jmf + xml");
					  part_1_header.set(Content_Transfer_Encoding, "8bit");

	msg.set_msg_part()->set_node(part_1_header, "PART 1 TEST BODY ... ...");

	class mime_header part_2_header;
					  part_2_header.set(Content_Type, "application/vnd.cip4 - jdf + xml");
					  part_2_header.set(Content_Transfer_Encoding, "8bit");

	msg.set_msg_part()->set_node(part_2_header, "PART 2 TEST BODY ... ...");
#if 0
	class mime_header part_3_header;
					  part_3_header.set(Content_Type, "application/pdf");
					  part_3_header.set(Content_Transfer_Encoding, "binary");

	class body_shadow sdbody;
					  sdbody.load("./TharstenCaseStudy_ESP_FINAL.pdf", 0, -1);

	msg.set_msg_part()->set_node(part_3_header, sdbody);
#endif

	string _message = msg.pack_msg();

	/**<------------------------------------------------------------*/
	/**< Set HTTP client */

	class httpc client;

	client.client_init("127.0.0.1");

	char buff[1000];

	client.data_send((void *)_message.data(), _message.size(), 0);
	client.data_recv(buff, sizeof(buff), 0);

	/**<------------------------------------------------------------*/
	/**< Print message from HTTP server */  

	cout << buff <<endl;

	return 0;
}

