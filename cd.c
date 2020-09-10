#include "headers.h"
#include "generics.h"

int cd(char *path, char *homeDir)
{
    if (path != NULL)
    {
        if (path[0] == '~')
        {
            char *tmp = substr(path, 1, strlen(path));
            path = concat(homeDir, tmp);
            free(tmp);
        }

        if (chdir(path) == 0)
        {
            return 1;
        }
        else
        {
            perror("Error");
            return 0;
        }
    }
}