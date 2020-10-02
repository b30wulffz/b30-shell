#include "headers.h"
#include "pinfo.h"
#include "globals.h"
#include "definitions.h"
#include "childproc.h"

void execute(char **data, int len, char *trimmedCommand, int isBackground)
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
            else
            {
                processDetails *node = addProcNode(pid, data[0], trimmedCommand, getChildProcessList());
                printf("[%d] %d\n", node->jobid, node->pid);
            }
        }
        else if (pid == 0)
        {
            //child
            if (isBackground == 1)
            {
                setpgid(0, 0);
            }
            execvp(data[0], data);
            printf("%s: Command not found\n", data[0]);
            exit(0);
        }
        else
        {
            printf("Error: Process can not be created\n");
        }
    }
}