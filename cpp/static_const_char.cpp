#include <stdio.h>

#define SAMPLE_TEXT "sample text"
static const char test1[] = SAMPLE_TEXT;
static const char test2[] = SAMPLE_TEXT;

int main(int argc, const char* argv[])
{
    printf("test1=%p,%s\n", test1, test1);
    printf("test2=%p,%s\n", test2, test2);
    return 0;
}

