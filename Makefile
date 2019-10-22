#-------------------------------------------------------------------------------------------------------
#																									   #
#								Makefile for libsocket source file 									   #
#																									   #
#-------------------------------------------------------------------------------------------------------


PROJECT			=   HTTPcd

CXX				=	g++

PATH_LIB		=	$(shell pwd)/lib
PATH_INC		=	$(shell pwd)/include
LD_FLAGS		=	-L$(PATH_LIB) -lsocketcd -Wl,-rpath=$(PATH_LIB)

CXXFLAGS		=	-Werror -std=c++11 -I$(PATH_INC)
CXXFLAGS       += 	-Wall
#CXXFLAGS		+=  -g

SUBDIRS 		=   src/comm/client src/comm/server src/message

export CXX CXXFLAGS PATH_INC


#-------------------------------------------------------------------------------------------------------
#																									   #
#											    Make rules 								   		   	   #
#																									   #
#-------------------------------------------------------------------------------------------------------


.PHONY: all clean install $(SUBDIRS)

all:$(SUBDIRS)
	ar -rcs $(PROJECT).a $(shell find ./ -name "*.o")

$(SUBDIRS):
	$(MAKE) -C $@	

install:clean
	mkdir HTTPcd 
	cp $(shell find ./ -name "*.hpp") ./HTTPcd
	mv $(PROJECT).a ./HTTPcd
 
tags:
	@rm -rf ./tags
	ctags --exclude="docs"			\
		  --exclude="*.o"			\
		  --exclude="*.a"			\
		  --exclude="*.so"			\
		  --exclude="*.elf"			\
		  --exclude="*.map"			\
		  --exclude="*.lss" -R .

clean:
	for dir in $(SUBDIRS); do 		\
		$(MAKE) -C $$dir clean;		\
	done
	@rm -rf $(shell find ./ -name "*.o")
	@rm -rf HTTPcd 

