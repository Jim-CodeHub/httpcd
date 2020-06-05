#include <httpcd/httpcd.hpp>
#include <iostream>

using namespace std;
USING_NAMESPACE_HTTPCD;


int main(void)
{
	/**<-------------------------------------------------------------------------------*/
	/**< Init HTTP client */

	class http_client client("127.0.0.1"); 


	/**<-------------------------------------------------------------------------------*/
	/**< Set HTTP message */

	client.set_msg_line(POST, "127.0.0.1", HTTP_1_1);

	client.set_msg_head(Content_Type, "multipart/related");
	client.set_msg_head(Content_Transfer_Encoding, "7bit");

	class mime_header part_1_header;
					  part_1_header.set(Content_Type, "application/vnd.cip4 - jmf + xml");
					  part_1_header.set(Content_Transfer_Encoding, "8bit");

	client.set_msg_part()->set_node(part_1_header, "PART 1 TEST BODY ... ...");

	class mime_header part_2_header;
					  part_2_header.set(Content_Type, "application/vnd.cip4 - jdf + xml");
					  part_2_header.set(Content_Transfer_Encoding, "8bit");

	client.set_msg_part()->set_node(part_2_header, "PART 2 TEST BODY ... ...");

	class mime_header part_3_header;
					  part_3_header.set(Content_Type, "application/pdf");
					  part_3_header.set(Content_Transfer_Encoding, "binary");

	class body_shadow sdbody;
					  sdbody.load("./TharstenCaseStudy_ESP_FINAL.pdf", 0, -1);

	client.set_msg_part()->set_node(part_3_header, sdbody);


	/**<-------------------------------------------------------------------------------*/
	/**< Send HTTP message to server */

	client.emit();

	cout << "message has been send "							<< endl;

	/**<-------------------------------------------------------------------------------*/
	/**< Recive HTTP message from server */

	client.recv();

	/**<-------------------------------------------------------------------------------*/
	/**< Parse HTTP message that are recived from sever */

	cout << "LINE      ::" << client.get_msg_line()			    <<endl;

	cout << "VERSION   ::" << client.get_msg_version(0)			<<endl;
	cout << "STATUS    ::" << client.get_msg_status()			<<endl;

	cout << "HEAD_CTYPE::" << client.get_msg_head(Content_Type) <<endl; 
	//...

	cout << "MSG_BODY  ::" << client.get_msg_body()			    <<endl;
	//... OR get_msg_part

	return 0;
}

