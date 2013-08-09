include ../share.mk

VERSION_ID = 1.0.0.0

INCLUDES=-I./ -I$(THRIFT_INCLUDE) -I$(IDL_PATH) -I$(COMMON_PATH) -I$(ZOOKEEPER_INCLUDE)
LIBS=-L$(COMMON_PATH) -lebscommon -L$(IDL_PATH) -lebsidl \
	-L$(THRIFT_LIB) -L$(ZOOKEEPER_LIB) -L$(LOG4CXX_LIB) \
	-lcrypto -lthriftnb -levent -luuid

GCOVDIR=./gcov
SRC=$(wildcard *.cpp)
OBJ=$(patsubst %.cpp, %.o, $(SRC))

MAIN=EbsBlockNode.cpp 
LSRC=$(filter-out $(MAIN), $(SRC))
LOBJ=$(patsubst %.cpp, $(GCOVDIR)/%.o, $(LSRC))

VSRC=Volume.cpp Volume.h VolumeMgr.cpp VolumeMgr.h VolumeQueue.cpp VolumeQueue.h

GCDA=$(patsubst %.cpp, %.gcda, $(filter %.cpp, $(VSRC)))
GCOV=$(patsubst %.cpp, %.cpp.gcov, $(filter %.cpp, $(VSRC)))

TARGET=libebsblocknode.a
	
all: $(TARGET)

GCOV=gcov.txt

$(LOBJ): $(GCOVDIR)/%.o: %.cpp
	$(CXX) -fprofile-arcs -ftest-coverage $(CXXFLAGS) $(INCLUDES) -c $< -o $@
	if [ -f $(GCOVDIR)/$*.gcda ]; then rm $(GCOVDIR)/$*.gcda; fi;

libebsblocknode.a: $(LOBJ)
	ar cr $@ $^

clean:
	rm -rf $(TARGET) $(RMFILE) *.gcov

$(GCOV): $(VSRC)
	gcov -o $(GCOVDIR) $^ | egrep -A3 "File '[A-Za-z]" >> $@

gcov: $(GCOV)

# %.cpp/%.h ==> %.o,%.gcno --> .a ==> unittest ==> %.gcda ==> %.gcov,gcov.txt
#			g++				ar	  ld (rm gcda)	   run		  gcov|grep 
#
