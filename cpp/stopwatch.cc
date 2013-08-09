#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include "stopwatch.h"

static int64_t gettimeofday_usec();

stop_watch_t::stop_watch_t()
{
}

stop_watch_t::stop_watch_t(char* buffer, size_t sz)
{
    buffer_ = buffer;
    sz_ = sz;
}

stop_watch_t::stop_watch_t(char* buffer, size_t sz, const char* fmt)
{
    buffer_ = buffer;
    sz_ = sz;
    fmt_ = fmt;
}

stop_watch_t::~stop_watch_t()
{
    cur_ = -1;
}

int stop_watch_t::start(const char* tag)
{
    int ret = -1;
    if (cur_ < NUM_WATCH)
    {
        node_t& node = node_[cur_];
        node.tag = tag;
        node.start = gettimeofday_usec();
        node.stop = -1;
        ret = cur_;
        cur_++;
    }
    return ret;
}

int64_t stop_watch_t::stop(int tag_index)
{
    int64_t ret = -1;
    if (tag_index >= 0 && tag_index < cur_ &&
        node_[tag_index].stop < 0)
    {
        int64_t cur_time = gettimeofday_usec();
        node_[tag_index].stop = cur_time;
        ret = cur_time - node_[tag_index].start;
    }
    return ret;
}

void stop_watch_t::stop_all()
{
    int64_t cur_time = gettimeofday_usec();
    for (int i = 0; i < cur_; i++)
    {
        if (node_[i].stop <= 0)
        {
            node_[i].stop = cur_time;
        }
    }
}

int64_t stop_watch_t::get_elapsed_time(int watch)
{
    int64_t ret = 0;
    if (watch < cur_)
    {
        ret = node_[watch].stop - node_[watch].start;
    }
    return ret;
}

const char* stop_watch_t::c_str(char* buffer, size_t sz, const char* fmt)
{
    const char* ret = NULL;
    if (NULL != buffer && sz > 1 && NULL == fmt)
    {
        size_t count = 0;
        for (int i = 0; i < cur_ && sz > count + 1; i++)
        {
            int n = snprintf(&buffer[count], sz - count, fmt, node_[i].tag,
                node_[i].stop - node_[i].start);
            if (n > 0)
            {
                count += n;
            }
            else
            {
                break;
            }
        }
        if (count > 0)
        {
            buffer[count - 1] = '\0';
        }
        else
        {
            buffer[0] = '\0';
        }
        ret = buffer;
    }
    return ret;
}

const char* stop_watch_t::c_str()
{
    return c_str(buffer_, sz_, fmt_);
}

const char stop_watch_t::DEFAULT_FORMAT[] = "%s:%ld,";

int64_t gettimeofday_usec()
{
    timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000L+ tv.tv_usec;
}

