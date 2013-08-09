#include <stdint.h>
#include <execinfo.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <iostream>
#include <string>
#include <exception>

using namespace std;
namespace t {   // test __PRETTY_FUNCTION__

void print_callstack()
{
    int i, nptrs;

    void* buffer[100];
    char** strings;

    nptrs = backtrace(buffer, 100);
    printf("backtrace() returned %d addresses\n", nptrs);

    /* The call backtrace_symbols_fd(buffer, nptrs, STDOUT_FILENO)
       would produce similar output to the following: */
    strings = backtrace_symbols(buffer, nptrs);
    if (strings == NULL)
    {
        perror("backtrace_symbols");
        _exit(-1);
    }

    for (i = 0; i < nptrs; i++)
        printf("%s ", strings[i]);
    printf("\n");

    free(strings);
}

class my_error : public std::exception
{
public:
    explicit my_error(const char* what_arg);
    virtual ~my_error() throw() {};
    virtual const char* what() const throw();

private:
    const char* _what;
};

my_error::my_error(const char* what_arg)
{
    cout << endl;
    cout << "my_error() ctor begin" << endl;
    _what = what_arg;
    cout << __PRETTY_FUNCTION__ << endl;
    cout << __FUNCTION__ << endl;
    print_callstack();
    cout << "my_error() ctor end" << endl << endl;
}

const char* my_error::what() const throw()
{
    return _what;
}

static void   /* "static" means don't export the symbol... */
myfunc2(void)
{
    print_callstack();
}

void myfunc(int ncalls)
{
    if (ncalls > 1)
        myfunc(ncalls - 1);
    else
        myfunc2();
}

int test()
{
    cout << "test(): will throw my_error" << endl;
    throw my_error("throw in test");
}
} // namespace

using namespace t;

int main(int argc, const char *argv[])
{
    //myfunc(argc);
    try
    {
        test();
        cout << "no throw!" << endl;
    }
    catch (std::exception& e)
    {
        cerr << "exception: " << e.what() << endl;
        print_callstack();
    }
    return 0;
}
