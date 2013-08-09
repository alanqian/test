BIN = prog 
BIN_DEBUG= prog_debug
LIBS:=pthread rt
CFLAGS=-g -Wall -O3 -m486
CXXFLAGS:=$(CFLAGS)

SOURCE:=$(wildcard *.c) $(wildcard *.cc)
OBJS:=$(patsubst %.c, %.o, $(patsubst %.cc, %.o, $(SOURCE)))  
DEPS:=$(patsubst %.o, %.d, $(OBJS))
MISSING_DEPS:=$(filter-out $(wildcard $(DEPS)), $(DEPS))
MISSING_DEPS_SOURCES:=$(wildcard $(patsubst %.c, %.c, $(MISSING_DEPS)) \
$(patsubst %.d, %.cc, $(MISSING_DEPS)))

#CPPFLAGS += -MD
CPPFLAGS += -MMD

CC=gcc


.PHONY: everything deps objs clean veryclean rebuild

release: $(BIN)

debug: $(BIN_DEBUG)

all: $(BIN) $(BIN_DEBUG)

deps: $(DEPS)

#%.d: %.c
# @set -e; rm -f $@; \
# $(CC) -MM $(CFLAGS) $< > $@.$$$$; \
# sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
# rm -f $@.$$$$


# -include $(source:.c=.d)

objs: $(OBJS)

clean:
 @$(RM) *.o
 @$(RM) *.d

veryclean: clean
 @$(RM) $(BIN)
 @$(RM) $(BIN_DEBUG)

rebuild: veryclean everything

ifneq ($(MISSING_DEPS), )
$(MISSING_DEPS):
 @$(RM) $(patsubst %.d, %.o, $@)
endif

-include $(DEPS)

$(BIN): $(OBJS)
 $(CC) -o $(BIN) $(OBJS) $(addprefix -l, $(LIBS))
$(BIN_DEBUG): $(OBJS)
 $(CC) -o $(BIN_DEBUG) $(OBJS) $(addprefix -l, $(LIBS)) -DDEBUG

