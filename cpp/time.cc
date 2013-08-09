int64_t gettimeofday_usec()
{
    struct timeval tv;
    int err = gettimeofday(&tv, NULL);
    if (0 != err)
    {
        LOG4CXX_WARN(logger, format("gettimeofday() error, err:%s") %
            strerror(errno));
    }

    // return microseconds value
    return tv.tv_sec * 1000000LL + tv.tv_usec;
}

void makeTimeout(const int64_t usecTimeout, timespec& ts)
{
    static const int64_t MILLION = 1000L * 1000L;
    static const int64_t BILLION = 1000L * MILLION;

    clock_gettime(CLOCK_REALTIME, &ts);
    ts.tv_sec += usecTimeout / MILLION;
    ts.tv_nsec += (usecTimeout % MILLION) * 1000L;
    if (ts.tv_nsec > BILLION)
    {
        ts.tv_sec += ts.tv_nsec / BILLION;
        ts.tv_sec %= BILLION;
    }
}

