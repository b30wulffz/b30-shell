#include "headers.h"
// #include "pwd.h"

char *pwd()
{
    char *dir;
    size_t len = 4096 * sizeof(char);
    dir = (char *)malloc(len);

    if (getcwd(dir, len) != NULL)
    {
        return dir;
    }
    else
    {
        perror("Error with getcwd()");
        return "";
    }
}