#include "headers.h"

void execute(char **data, int len, int isBackground)
{
    if (data != NULL && len > 0)
    {
        int pid = fork();
        if (pid > 0)
        {
            //parent
            if (isBackground != 1)
            {
                waitpid(pid, NULL, 0);
            }
        }
        else if (pid == 0)
        {
            if (isBackground == 1)
            {
                setpgid(0, 0);
                printf("[] %d\n", getpid());
            }
            execvp(data[0], data);
            printf("%s: Command not found\n", data[0]);
        }
        else
        {
            printf("Error: Process can not be created\n");
        }
    }
}