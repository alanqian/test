BINDIR = ../bin
LIBDIR = ../lib
TESTDIR = ../t
INCLUDEDIR = ../include
DEPDIR = ../.deps
OBJDIR = ../.objs
COVDIR = ../.gcov

# objs dirs:
#   .objs/debug .objs/release .gcov/

LIBS = pthread rt
INCLUDES = ./ $(INCLUDEDIR)

AR = ar
CC = g++
RM = rm -f

CFLAGS = -g -Wall -Werror
CCFLAGS = -g -Wall -Werror -MMD -std=c++0x -DVERSION=$(version)
ARFLAGS = cr

MODULE=module
BIN = app1 app2
BIN_DEBUG = $(patsubst %, %_debug, $(BIN))
LIB = lib$(MODULE).a
LIB_DEBUG = lib$(MODULE)d.a
version=0.1.1

SOURCE = $(wildcard *.cc)
MAINSRC = $(patsubst %, %.cc, $(BIN))
UTSRC = $(wildcard *_test.cc)
SRC = $(filter-out $(UTSRC), $(SOURCE))
LIBSRC = $(filter-out $(MAINSRC), $(SRC))

RELOBJS = $(patsubst %.cc, $(OBJDIR)/rel/%.o, $(SOURCE))
DBGOBJS = $(patsubst %.cc, $(OBJDIR)/dbg/%.o, $(SOURCE))
LIBOBJS = $(patsubst %.cc, $(OBJDIR)/rel/%.o, $(LIBSRC))
LIBDOBJS = $(patsubst %.cc, $(OBJDIR)/dbg/%.o, $(LIBSRC))
DEPS = $(patsubst %.cc, $(DEPDIR)/%.d, $(SOURCE))
TESTS = $(patsubst %.cc, $(TESTDIR)/%, $(UTSRC))

COVOBJS = $(patsubst %.cc, $(COVDIR)/%.o, $(SRC) $(UTSRC))
COVTESTS = $(patsubst %.cc, $(COVDIR)/%, $(UTSRC))
COVLIB = $(COVDIR)/$(LIB)
COVS = $(patsubst %, $(COVDIR)/%.gcov, $(LIBSRC))
COV = $(BIN).gcov

.PHONY: show mkdir clean veryclean deps objs rebuild

TEST = one two three
test:
	@for t in $(TEST); do echo $$t; done

show:
	@echo SOURCE: $(SOURCE)
	@echo SRC: $(SRC)
	@echo MAINSRC: $(MAINSRC)
	@echo UTSRC: $(UTSRC)
	@echo LIBSRC: $(LIBSRC)
	@echo TESTS: $(TESTS)
	@echo OBJS: $(OBJS)
	@echo DEPS: $(DEPS)
	@echo COVS: $(COVS)

mkdir:
	mkdir $(INCLUDEDIR) $(DEPDIR) $(OBJDIR) $(COVDIR) $(BINDIR) $(LIBDIR) $(TESTDIR)
	mkdir $(OBJDIR)/dbg $(OBJDIR)/rel $(OBJDIR)/cov

clean:
	@$(RM) -r $(OBJDIR)/*
	@$(RM) $(DEPDIR)/* $(BIN) $(BIN_DEBUG) $(TESTS)

veryclean: clean
	$(RM) -r $(DEPDIR) $(OBJDIR) $(COVDIR) $(BINDIR) $(LIBDIR)

release: $(BIN)

debug: $(BIN_DEBUG)

all: $(BIN) $(BIN_DEBUG)

rebuild: clean all

deps: $(DEPS)

objs: $(OBJS)

$(DEPS) : $(DEPDIR)/%.d : %.cc
	@set -e; rm -f $@; \
	$(CC) -MM $(CFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

$(OBJS) : $(OBJDIR)/%.o: %.cc $(DEPDIR)/%.d
	$(CC) $(CCFLAGS) $(addprefix -I $(INCLUDES)) -c $< -o $@

-include $(DEPS)

$(BIN): $(OBJS)
	$(CC) -o $(BIN) $(OBJS) $(addprefix -l, $(LIBS))

$(BIN_DEBUG): $(OBJS)
	$(CC) -o $(BIN_DEBUG) $(OBJS) $(addprefix -l, $(LIBS)) -DDEBUG

$(LIB): $(LIBOBJS)
	$(AR) $(ARFLAGS) $@ $^

$(LIB_DEBUG): $(LIBDOBJS)
	$(AR) $(ARFLAGS) $@ $^

$(TESTS): $(TESTDIR)/% : $(OBJDIR)/%.o $(LIB_DEBUG)
	$(CC) -g -o $@ $< $(LIBS)

