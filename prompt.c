#include "headers.h"
#include "generics.h"
#include "pwd.h"
#include "globals.h"

void prompt()
{
    char *username = getCurrentUser();
    char *hostname = getHostName();

    char *path = rootPathResolve(pwd(), getHomeDir());

    printf("<%s@%s:%s> ", username, hostname, path);

    free(path);
}