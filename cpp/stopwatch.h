#ifndef __STOP_WATCH_T__
#define __STOP_WATCH_T__

#include <stdint.h>

/**
 * Usage:
 *   stop_watch_t sw();
 *   int foo = sw.start("foo");
 *
 *   int bar = sw.start("bar");
 *   sw.stop(bar);
 *
 *   int baz = sw.start("baz");
 *   sw.stop(baz);
 *
 *   sw.stop(foo);
 *
 *   char szT[64];
 *   const char* times = sw.c_str(szT, sizeof(szT), "%s:%ld,");
 *
 *   logger.warn("times:{%s}", times);
 *
 * Returns::
 *   foo:31,bar:3,baz:10
**/
class stop_watch_t {
private:
    static const int NUM_WATCH = 16;
    static const char DEFAULT_FORMAT[];

public:
	stop_watch_t();

	stop_watch_t(char* buffer, size_t sz);

	stop_watch_t(char* buffer, size_t sz, const char* fmt);

	~stop_watch_t();

	int start(const char* tag);

	int64_t stop(int tag_index);

	void stop_all();

	int64_t get_elapsed_time(int watch);

	const char* c_str(char* buffer, size_t sz, const char* fmt);

	const char* c_str();

private:
    struct node_t {
        const char* tag;
        int64_t     start;
        int64_t     stop;
    };
    node_t  node_[NUM_WATCH];
	int     cur_ = 0;
    size_t  sz_ = 0;
    char*   buffer_ = NULL;
    const char* fmt_ = DEFAULT_FORMAT;
};

#endif // __STOP_WATCH_T__
