#-------------------------------------------------------------------------------------------------------
#																									   #
#								Makefile for libHTTP source file 									   #
#																									   #
#-------------------------------------------------------------------------------------------------------


PROJECT			=   httpcd

CXX				=	g++

CXXFLAGS		=	-Werror -std=c++11
CXXFLAGS       += 	-Wall
#CXXFLAGS		+=  -g

SUBDIRS 		=   src/comm/client src/comm/server src/message

export CXX CXXFLAGS LD_FLAGS


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

