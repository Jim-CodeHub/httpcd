/**-----------------------------------------------------------------------------------------------------------------
 * @file	message.cpp
 * @brief	packetize and depacketize HTTP message
 * @ref		RFC2045, RFC2046, RFC2047, RFC2049
 *
 * Copyright (c) 2019-2019 Jim Zhang 303683086@qq.com
 *------------------------------------------------------------------------------------------------------------------
*/

#include "mime.hpp"

//术语
//CRFL 代表 "\r\n"
//7bit 表示值范围 1 ~ 127，NUL(0)不允许，也就是用于表示非0的ASCII字符
//8bit 表示值范围 1 ~ 255, NUL(0)不允许，也就是用于表示非0的ASCII字符扩展
//binary 表示任意8bit序列数据



using namespace NS_LIBHTTP;

enum mime_main_head{
	MIME_Version, Content_Type, Content_Transfer_Encoding
};

enum mime_part_head{
	Content_Type, Content_Transfer_Encoding, Content_Disposition, Content_ID, Content_Location, Content_Base
};

enum mime_type_main{
	text, image, audio, video, application, multipart, message
};

enum mime_type_subs{
};

enum mime_encd_data{
	_7bit, _8bit, binary, base64, quoted_printable
};


//头部 首部类型
	
	Content_Type语法：
		Content-Type: type/subtype; parameter //后面;parameter 是可选的
		
		type可以为离散类型和复合类型, 大小写不敏感
			离散:
				application //
				audio //默认子类型为basic
				video //默认子类型为mpeg
				image //默认自雷行为JPEG
				text // //默认自雷行为plain
					子类型：plain, enriched
					可选参数：charset
						charset=val， val是大小写不敏感的，默认值为us-ascii，可选ISO-8859-X, X为1~10
					text类型下，CR LF只能用于表示换行
				其它扩展

			复合：
				multipart
					1. 每个部分的前面使用分隔符分隔，最后一个部分的最后使用关闭分隔符标记
					2. 每个部分，分隔符之后是头部，头部后面是空白行，然后使该部分的主体
					3. 每个部分，可以没有头部，此时该部分的内容被理解为头部是默认值的情况(Content-Type: text/plain; charset=US-ASCII)
					4. 分隔符在整个消息中必须唯一，不能与头部和body的任何内容重复，这就需要程序去生成
					5. 分隔符和头部（包含part的头部）都表示为7bit的ASCII值，（头部经过扩展的除外RFC2047），而每个部分的body数据可以编码为自己想要的编码

					语法：
					Content-Type: multipart/xxx; boundary=paramterVal
					Content-Type: multipart/xxx; boundary="paramterVal" //这里的引号是可选的，使用是为了避免参数值里有冒号等信息

					--paramterVal //a. 使用时是一样的，有引号的要去掉
					边界分隔符不能超过70个(不包含前缀--)(1~70), 且不能以空白结尾
					如果以空白结尾，则必须删除
					组成字符可以是：数字、字母、下划线, (左右)圆括号, 加号, 除号, 逗号, :, =, ?, '

					--paramterVal-- //b, 表示后面不再有part

					//body中 ， a 之前的内容 和 b之后的内容都应该被忽略
				
					part格式：

					some text that will be ignored CRLF
					--uniqboundaryparamval *LWSP CRLF	//LWSP = liner-white-space, 在这里是可选的
					MIME-part-headers [CRLF *OCTET] CRLF //这里[]表示可选， *表示0~多个，[CRLF *OCTET]的含义是 partbody内容可有可无，有的时候先写一个CRLF，然后是内容
					--uniqboundaryparamval *LWSP CRLF
					MIME-part-headers [CRLF *OCTET] CRLF	
					--uniqboundaryparamval *LWSP CRLF
					MIME-part-headers [CRLF *OCTET] CRLF	
					--uniqboundaryparamval *LWSP CRLF
					...
					CRLF
					--uniqboundaryparamval-- *LWSP
					CRLF
					some text that will be ignored
				






				message
				其它扩展

		subtype包含各种注册和未注册的扩展类型, 大小写不敏感

		parameter是可选的，结构为："attr=val", attr大小写不敏感, val通常区分大小写，另外
		attr="val"和attr=val是等价的

		默认的Content-Type：
			Content-Type: text/plain; charset=us-ascii
			没有指定内容类型时或者遇到无法处理的类型时，都可以默认为此类型处理

			但是，当编码被指定，且无法被识别时，默认的类型是application/octet-stream，此时无论
			Content-Type是否指定了类型

		
	Content-Tranfer-Encoding语法
		Content-Tranfer-Encoding: 编码
		编码有：7bit 或 8bit 或 binary 或 quoted-printable 或 base64 或其它扩展， 大小写不敏感
		
		默认的Content-Tranfer-Encodeing:
			Content-Transfer-Encoding: 7bit

		应用范围：
			如果存在顶级头部，则对整个消息体有效。如果存在部分的头部，则仅对该部分的消息体有效
			。如果Content-Type是复合类型，则编码只能使用7bit/8bit/binary，而实际每个部分的body，可以定义所有编码

			在复合类型情况下, 如果顶级是7bit，但某部分是8bit,那也算错误，




#include <random>
uint64_t generateBoundary(void)
{
	random_device rd;
	mt19937 mt(rd());

	return mt();
}

