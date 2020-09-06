#include "headers.h"

int cd(char *path, char *homeDir)
{
    char homeSymbol[] = "~";
    if (strcmp(path, homeSymbol) == 0)
    {
        if (chdir(homeDir) == 0)
        {
            return 1;
        }
        else
        {
            perror("chdir() failed");
            return 0;
        }
    }
    else
    {
        if (chdir(path) == 0)
        {
            return 1;
        }
        else
        {
            perror("chdir() failed");
            return 0;
        }
    }
}