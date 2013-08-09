#include <stdio.h>
#include <string.h>
#include <alloca.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <vector>

class foo_t
{
public:
    foo_t();

    int foo(long c, long d, int e);

private:
    long _a;
};

foo_t::foo_t()
{
}

typedef std::vector<int> int_vector;

class int_vector_class : public std::vector<int>
{
public:
    int_vector_class() {};
    ~int_vector_class() {};
};

void mk_core()
{
    int* p = NULL;
    *p = 0;
}

void test_template_param(const int_vector_class& ivc, int_vector& iv, std::vector<int>& v)
{
    printf("ivc:%ld iv:%ld\n v:%ld\n",
        ivc.size(), iv.size(), v.size());
    //mk_core();
}

int foo_t::foo(long c, long d, int e)
{
    int n = 64;
    n += c;
    n -= c;
    void* pT = alloca(n);
    memset(pT, c, n);
    _a = c;
    return 0;
}

void foo(long c, long d, int e)
{
    int_vector_class ivc;
    int_vector iv;
    std::vector<int> v;
    test_template_param(ivc, iv, v);

    printf("  vars: @%p,%p,%p\n", &c, &d, &e);
    if (c > 0)
    {
        long a[10];
        memset(a, 'a', sizeof(a));
        a[0] = 'B';
        a[9] = 'E';
        printf("  local1.if: @%p\n", &a[0]);
    }
    else
    {
        long a[10];
        memset(a, 'b', sizeof(a));
        printf("local1.else: @%p\n", &a[0]);
    }

    if (c > 0)
    {
        long a[10];
        memset(a, 'c', sizeof(a));
        printf("     local2: @%p\n", &a[0]);
    }

    printf("\n\n");

    foo_t fo;
    fo.foo(0x1234567, 0x89abcdef, 0xeeeeeeee);
}

int main(int argc, const char *argv[])
{
    size_t mystacksize;
    pthread_attr_t attr;
    pthread_attr_getstacksize(&attr, &mystacksize);
    printf("Thread %lx: stack size = %li bytes \n", (long)pthread_self(), mystacksize);

    foo_t fo;
    fo.foo(0x1234567, 0x89abcdef, 0xeeeeeeee);

    printf("main(): %p, foo():%p\n",
        &main, &foo);
    foo(0x1234567, 0x89abcdef, 0xeeeeeeee);
    printf("%'ld", 0x89abcdefL);
    return 0;
}

