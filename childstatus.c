#include "headers.h"

void checkChildStatus(int childProcesses[], int childProcessCount, int maxProcessCount)
{
    int status;
    int res = waitpid(-1, &status, WNOHANG);
    for (int i = 0; i < childProcessCount; i++)
    {
        int status = 0;
        // ->printf("->%d : ", childProcesses[i]);
        // waitpid(childProcesses[i], &status, WNOHANG);
        // printf("%d \n", WIFEXITED(status));
        // -> printf("%d \n", kill(childProcesses[i], 0));
    }
    if (res > 0)
    {
        if (WIFEXITED(status) == 1)
        {
            // ->printf("Defunt: %d %d", res, WEXITSTATUS(status));
        }
    }
}