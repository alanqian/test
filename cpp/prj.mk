include ../share.mk

INCLUDES=-I./ -I$(THRIFT_INCLUDE) -I$(IDL_PATH) -I$(COMMON_PATH) -I$(ZOOKEEPER_INCLUDE)
LIBS=-L$(COMMON_PATH) -lebscommon -L$(IDL_PATH) -lebsidl \
	-L$(THRIFT_LIB) -L$(ZOOKEEPER_LIB) -L$(LOG4CXX_LIB) \
	-lcrypto

SRC=$(wildcard *.cpp)
OBJ=$(patsubst %.cpp, %.o, $(SRC))

TSRC=$(filter-out EbsBlockNode.cpp, $(SRC))
TOBJ=$(patsubst %.cpp, tobj/%.o, $(TSRC))

TARGET=ebsblocknode 
	
all: $(TARGET)

test: libebsblocknode.a

dir:
	@if [ ! -d tobj ]; then mkdir tobj; fi;
	
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(TOBJ): tobj/%.o: %.cpp
	@if [ ! -d tobj ]; then mkdir tobj; fi;
	$(CXX) $(CXXFLAGS) -DPRIVATETEST $(INCLUDES) -c $< -o $@

ebsblocknode: $(OBJ)	
	$(CXX) -o $@ $^ $(CXXFLAGS) $(INCLUDES) $(LIBS)

libebsblocknode.a: $(TOBJ)
	ar cr $@ $^

clean:
	rm -rf $(TARGET) *.o tobj/

