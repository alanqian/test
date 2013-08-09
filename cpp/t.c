#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char* argv[])
{
    //bool t = false;
    char* t = malloc(1024*1025);
    t = 0;
    *t = 10;
    free(t);

    printf("%d%s\n", *t, t);
    return 0;
}
