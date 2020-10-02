#include "headers.h"
#include "generics.h"
#include "globals.h"
#include "pwd.h"

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
        else if (strcmp(path, "-") == 0)
        {
            path = getOldDir();
            if (path == NULL)
            {
                printf("Error: Old Directory Not Set\n");
                return 0;
            }
        }
        setOldDir(pwd());

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