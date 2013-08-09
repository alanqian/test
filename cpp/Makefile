SRC=$(wildcard *.c *.cpp *.cc)

TESTC=$(patsubst %.c, %, $(filter %.c, $(SRC)))
TESTCPP=$(patsubst %.cpp, %, $(filter %.cpp, $(SRC)))
TESTCC=$(patsubst %.cc, %, $(filter %.cc, $(SRC)))

#src=$(filter-out size.cpp, $(SRC))
#dir=$(notdir $(SRC))

all: $(TESTC) $(TESTCPP)

debug:
	@echo SRC=$(SRC)
	@echo T=$(T)
	@echo TESTC=$(TESTC)
	@echo TESTCPP=$(TESTCPP)
	@echo "end of make"

$(TESTC): %: %.c
	gcc -g -o $@ $^

$(TESTCPP): %: %.cpp
	g++ -g -o $@ $^ -pthread -lrt -Wl,-cref,-Map,test.map

$(TESTCC): %: %.cc
	g++-4.7 -g -o $@ $^ -std=c++11 -pthread -lrt -Wl,-cref,-Map,test.map

clean:
	rm $(TESTC) $(TESTCPP) *.o

