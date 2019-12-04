
OBJS    = testMain 
SUBDIRS = 

PATH_LIBMIME 	=	$(shell dirname `pwd`)/contrib/libmime/install/lib
PATH_SOCKETCD   =	$(shell dirname `pwd`)/contrib/socketcd/install/lib
 
 
#-------------------------------------------------------------------------------------------------------
#																									   #
#										  Make rules 									   		   	   #
#																									   #
#-------------------------------------------------------------------------------------------------------


.PHONY: all clean $(SUBDIRS)

all:
	for i in $(OBJS);															\
	do																			\
		g++ $(CXXFLAGS) "$$i".cpp 												\
		-L$(PATH_SOCKETCD) -lsocketcd -Wl,-rpath=$(PATH_SOCKETCD)				\
		-L$(PATH_LIBMIME) -lmime -Wl,-rpath=$(PATH_LIBMIME)						\
		-L$(shell dirname `pwd`) -l$(TARGET) -Wl,-rpath=$(shell dirname `pwd`)	\
		-L$(shell dirname `pwd`) -l$(TARGET) -Wl,-rpath=$(shell dirname `pwd`)	\
								 -lpthread										\
								 								 -o "$$i".out;	\
	done

.PHONY:clean
clean:
	rm -rf *.out


#-L$(PATH_SOCKETCD)-lsocketcd -Wl,-rpath=$(PATH_SOCKETCD)\
#-L$(PATH_LIBMIME) -lmime -Wl,-rpath=$(PATH_LIBMIME)	\
#-L$(shell dirname `pwd`) -l$(TARGET) -Wl,-rpath=$(shell dirname `pwd`)  -o "$$i".out;\
