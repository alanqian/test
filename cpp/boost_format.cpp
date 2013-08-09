#include <stdint.h>
#include <execinfo.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <log4cxx/logger.h>
#include <boost/format.hpp>

using namespace std;
using namespace boost;

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
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < nptrs; i++)
        printf("%s ", strings[i]);
    printf("\n");

    free(strings);
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
    int a = 11;
    int b = 12;
    int c = 14;
    boost::format fmt = format("test: %s %d %d %m") % a % b % c;
    string str = fmt.str();
    cout << str << endl;
}

int main(int argc, const char *argv[])
{
    //myfunc(argc);
    try
    {
        test();
    }
    catch (std::exception& e)
    {
        cerr << "exception: " << e.what() << endl;
        print_callstack();
    }
    return 0;
}
