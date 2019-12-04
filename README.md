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
	xxx;
}

*-g++ *.cpp  -lhttpcd -lsocketcd -lmime -lpthread -o *.out 
