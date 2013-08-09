include share.mk

WORK_PATH=../../
INCLUDES=-I./ -I$(GTEST_INCLUDE)  -I$(COMMON_PATH) -I$(WORK_PATH)/blocknode -I$(IDL_PATH) \
	-I$(THRIFT_INCLUDE) -I$(ZOOKEEPER_INCLUDE)

LIBS= -L$(WORK_PATH)/blocknode -lebsblocknode -L$(COMMON_PATH) -lebscommon -L$(IDL_PATH) -lebsidl  -L$(GTEST_LIB) \
	-L$(THRIFT_LIB) -L$(ZOOKEEPER_LIB) -L$(LOG4CXX_LIB) -lpthread -lcrypto

SRC=$(wildcard *UT.cpp)
OBJECTS=$(patsubst %.cpp, %.o, $(SRC))
TARGET=$(patsubst %UT.cpp, blocknode_%_unittest, $(SRC))

all: $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -D PRIVATETEST $(INCLUDES) -c $< -o $@

$(TARGET): blocknode_%_unittest: %UT.o  $(WORK_PATH)/blocknode/libebsblocknode.a
	$(CXX) -o $@ $< $(LIBS)

clean:
	@echo clean immediate files...
	rm -f $(TARGET) *.o

