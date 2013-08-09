class scoped_guard_t
{
public:
    explicit scoped_guard_t(std::function<void()> cleaner)
        : cleaner_(cleaner), is_canceled_(false)
    { }

    ~scoped_guard_t()
    {
        if(!is_canceled_)
        {
            cleaner_();
        }
    }

    void cancel()
    {
        is_canceled_ = true;
    }

private:
    std::function<void()> cleaner_;
    bool is_canceled_;

private: // noncopyable
    scoped_guard_t(scoped_guard_t const&);
    scoped_guard_t& operator=(scoped_guard_t const&);
};

HANDLE h = CreateFile(...);
scoped_guard_t onExit([&] { CloseHandle(h); })

#define PASTE(name, line) name##line
#define UNIQUE_VAR(name, line) PASTE(name, line)
#define SCOPEGUARD UNIQUE_VAR(_guard, __LINE__)

#define FINALLY(callback) scoped_guard_t SCOPEGUARD(callback)

FINNALY([&] { CloseHandle(h); });

