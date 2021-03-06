#-------------------------------------------------------------------------------------------------------
#																									   #
#								Makefile for libHTTP source file 									   #
#																									   #
#-------------------------------------------------------------------------------------------------------

TARGET		    =   httpcd
PROJECT			=   lib$(TARGET)
VERSION			=	0.2

CXX				=   g++	

DEP_LIBMIME		=	libmime
DEP_SOCKETCD	= 	socketcd

--PREFIX		=   ./install

CXXFLAGS		=	-Werror -std=c++11
CXXFLAGS       += 	-Wall
CXXFLAGS	   +=   -I$(CURDIR)
CXXFLAGS	   +=   -I$(CURDIR)/contrib/$(DEP_LIBMIME)/install/include
CXXFLAGS	   +=   -I$(CURDIR)/contrib/$(DEP_SOCKETCD)/install/include
#CXXFLAGS		+=  -g

SUBDIRS 		=   $(TARGET) 

export CXX CXXFLAGS TARGET


#-------------------------------------------------------------------------------------------------------
#																									   #
#									        Make rules 									   		   	   #
#																									   #
#-------------------------------------------------------------------------------------------------------

.PHONY: all clean install $(SUBDIRS) demo contrib tags

all:$(SUBDIRS)
	ar -rcs $(PROJECT).a $(shell find ./$(TARGET) -name "*.o")
	$(CXX) -fPIC -shared  $(CXXFLAGS) $(shell find ./$(TARGET) -name "*.cpp") -o $(PROJECT).so.$(VERSION)
	ln -s $(PROJECT).so.$(VERSION) $(PROJECT).so 

$(SUBDIRS):
	$(MAKE) -C $@	

demo:
	$(MAKE) -C demo 

contrib:
	$(MAKE) -C contrib/$(DEP_LIBMIME)
	$(MAKE) -C contrib/$(DEP_SOCKETCD)
	$(MAKE) install -C contrib/$(DEP_LIBMIME)
	$(MAKE) install -C contrib/$(DEP_SOCKETCD)

install:
	$(shell if [ ! -d $(--PREFIX) ]; then mkdir $(--PREFIX); fi;)
	$(shell if [ ! -d $(--PREFIX)/include ]; then mkdir $(--PREFIX)/include; fi;)
	$(shell if [ ! -d $(--PREFIX)/lib ]; then mkdir $(--PREFIX)/lib; fi;)
	@cp $(TARGET) $(--PREFIX)/include -rf
	@mv ./$(PROJECT).a ./$(PROJECT).so $(--PREFIX)/lib 
	@rm -rf `find ./$(--PREFIX)/include -name "*.o"`
	@rm -rf `find ./$(--PREFIX)/include -name "*.cpp"`
	@rm -rf `find ./$(--PREFIX)/include -name "Makefile"`

tags:
	@rm -rf ./tags
	ctags --exclude="docs"			\
		  --exclude="*.o"			\
		  --exclude="*.a"			\
		  --exclude="*.so"			\
		  --exclude="*.elf"			\
		  --exclude="*.map"			\
		  --exclude="*.lss" -Rn .

clean:
	for dir in $(SUBDIRS); do 		\
		$(MAKE) -C $$dir clean;		\
	done
	@rm -rf $(shell find ./ -name "*.o")
	@rm -rf $(PROJECT).*
	@rm -rf install

