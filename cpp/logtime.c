#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>

int get_log_asctime(char* buffer, size_t size)
{
    int err = 0;
    struct timeval tv;
    struct tm tm;

    if (NULL == buffer)
    {
        err = -1;
    }
    else
    {
        err = gettimeofday(&tv, NULL);
        if (0 != err)
        {
            err = errno;
        }
        localtime_r(&tv.tv_sec, &tm);
        snprintf(buffer, size, "%02d-%02d-%02d %02d:%02d:%02d.%06ld",
            tm.tm_year % 100, tm.tm_mon + 1, tm.tm_mday,
            tm.tm_hour, tm.tm_min, tm.tm_sec,
            tv.tv_usec);
    }
    return err;
}

int main(int argc, const char* argv[])
{
    int i;
    char t[64];
    int err = 0;
    for (i = 0; i < 30; i++)
    {
        int wait_us = 0;

        get_log_asctime(t, sizeof(t));
        wait_us = rand() % 1000000;
        fprintf(stderr, "[%s] %s %lx %s:%d \"%s\", ret=%d wait(us)=%d\n", 
            "DEBUG", t, (long)pthread_self(), __FILE__, __LINE__, 
            "wait for microseconds", err, wait_us);
        err = usleep(wait_us);
    }
    return 0;
}

