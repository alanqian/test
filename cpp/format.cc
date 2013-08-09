#include <stdio.h>
#include <stdarg.h>

const char* format(char *str, size_t size, const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    int n = vsnprintf(str, size, fmt, ap);
    va_end(ap);
    return str;
}

int main(int argc, const char* argv[])
{
    char buf[512];
    printf("output: %s", format(buf, sizeof(buf), "hello %s\n", "world, or anything"));
    printf("output: %s", format(buf, 16, "hello %s\n", NULL));
    printf("output: %s", format(buf, 16, "hello %s\n", "world, or anything"));
    printf("output: %s", format(buf, 16, "hello %s,%d\n", "s"));
}


