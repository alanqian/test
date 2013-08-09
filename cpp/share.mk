CXX = g++
CXXFLAGS = -Wall -Werror -g -DVERSION="\"${VERSION_ID}\""

WORK_PATH=..
IDL_PATH=$(WORK_PATH)/idl/gen-cpp/
COMMON_PATH=$(WORK_PATH)/common/
CLIENT_PATH=$(WORK_PATH)/client/
TOOL_PATH=$(WORK_PATH)/tools/

THRIFT_INCLUDE=/usr/local/include/thrift
THRIFT_LIB=/usr/local/lib -lthrift

ZOOKEEPER_INCLUDE=/usr/local/include/c-client-src
ZOOKEEPER_LIB=/usr/local/lib -lzookeeper_mt

LOG4CXX_INCLUDE=/usr/local/include/log4cxx
LOG4CXX_LIB=/usr/local/lib -llog4cxx

MYSQL_INCLUDE=/usr/include
MYSQL_LIB=/usr/lib/mysql -lmysqlclient

GTEST_INCLUDE=$(WORK_PATH)/test/gtest/include
GTEST_LIB=$(WORK_PATH)/test/gtest -lgtest
GTEST_DIR=../gtest/

