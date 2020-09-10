#include "headers.h"

char *homeDir = NULL;

void setHomeDir(char *path)
{
    homeDir = path;
}

char *getHomeDir()
{
    if (homeDir == NULL)
    {
        homeDir = (char *)malloc(sizeof(char) * 2);
        homeDir[0] = '~';
        homeDir[1] = '\0';
    }
    return homeDir;
}