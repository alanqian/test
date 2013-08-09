#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <sys/time.h>
#include <errno.h>

void test_time()
{
    static const int64_t MILLION = 1000L * 1000L;
    static const int64_t BILLION = 1000L * MILLION;

    int err = 0;
    struct timeval tv;
    struct timespec ts;
    err = clock_gettime(CLOCK_REALTIME, &ts);
    err = gettimeofday(&tv, NULL);

    // return microseconds value
    int64_t usec = tv.tv_sec * 1000000LL + tv.tv_usec;

    printf("ts: %ld.%09ld\ntv: %ld.%06ld\n",
        ts.tv_sec, ts.tv_nsec,
        tv.tv_sec, tv.tv_usec);
}

int main(int argc, const char *argv[])
{
    test_time();
    return 0;
}
