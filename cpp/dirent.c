#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <stdio.h>

int main(int argc, const char *argv[])
{
    int return_code;
    DIR* pdir;
    struct dirent entry;
    struct dirent *result;
    const char* dir = argv[1];

    pdir = opendir(dir);
    if (NULL == pdir)
    {
        perror("opendir() error");
    }
    else 
    {
        printf("contents of %s:", dir);
        while (0 == readdir_r(pdir, &entry, &result) &&
            NULL != result)
        {
            printf("%s\n", entry.d_name);
        }
        closedir(pdir);
    }
    return 0;
}

