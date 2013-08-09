#include <stdint.h>
#include <string>
#include <iostream>
#include <vector>
#include <limits.h>
#include <stdio.h>

using namespace std;

typedef struct _type_size_t
{
    const char* _typename;
    size_t      _size;
} type_size_t;

class class_no_member
{
public:
    class_no_member() { };
};

struct struct_with_bit
{
    int64_t bad_state : 1;
    int64_t count : 23;
};

class_no_member a[3];

#define DEFINE_TYPE_SIZE(type) \
    { #type, sizeof(type) }


#define sizeofarray(arr) \
    (sizeof(arr) / sizeof(arr[0]))

#define PASTE(name, line) name##line
#define UNIQUE_VAR(name, line) PASTE(name, line)
#define SCOPEGUARD UNIQUE_VAR(_guard, __LINE__)
#define DEFINE_ASCIIZ(name) \
    char name[] = "hello asciiz"

void test_int()
{
    int imin = INT_MIN;
    int imax = INT_MAX;

    printf("min=0x%x, -min=0x%x\n", imin, -imin);
    imin >>= 1;
    printf("max=0x%x, -max=0x%x\n", imax, -imax);
}

int main(int argc, const char *argv[])
{


    int i = 0;
    DEFINE_ASCIIZ(SCOPEGUARD);
    cout << _guard58 << endl;

    type_size_t types[] =
    {
        DEFINE_TYPE_SIZE(char),
        DEFINE_TYPE_SIZE(wchar_t),
        DEFINE_TYPE_SIZE(short),
        DEFINE_TYPE_SIZE(int),
        DEFINE_TYPE_SIZE(long),
        DEFINE_TYPE_SIZE(long long),
        DEFINE_TYPE_SIZE(size_t),
        DEFINE_TYPE_SIZE(void*),
        DEFINE_TYPE_SIZE(float),
        DEFINE_TYPE_SIZE(double),
        DEFINE_TYPE_SIZE(string),
        DEFINE_TYPE_SIZE(vector<char>),
        DEFINE_TYPE_SIZE(class_no_member),
        DEFINE_TYPE_SIZE(struct_with_bit),
    };

    for (i = 0; i < sizeofarray(types); i++)
    {
        cout << "sizeof(" << types[i]._typename << ") = " << types[i]._size << "\n";
    }

    unsigned int u = -1;
    int64_t t = 1L << 63;
    i = u % 31;
    cout << "sizeof(class_no_member[3]): " << sizeof(a[3]) << endl;
    cout << __func__ << ".i:" << i << endl;
    cout << "1 << 63 = " << t << endl;
    cout << "LONG_MIN = " << LONG_MIN << endl;
    i = -1;
    float f = *(float*)&i;
    cout << "float(-1)=" << f << endl;
    int* p = new int;

    cout << "stack: @" << hex << &i << endl;
    cout << "heap: @" << hex << p << endl;
    delete p;
    return 0;
}

