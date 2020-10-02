#include "headers.h"
#include "pwd.h"
#include "globals.h"
#include "prompt.h"
#include "pinfo.h"
#include "childproc.h"
#include "definitions.h"
#include "cleanup.h"

void childProcHandler(int id)
{
    int status;
    while (1)
    {
        int pid = waitpid(-1, &status, WNOHANG);
        if (pid > 0)
        {
            processDetails *node = getProcNode(pid, getChildProcessList());
            if (node != NULL)
            {
                if ((WIFEXITED(status) != 0) && (WEXITSTATUS(status) == EXIT_SUCCESS))
                {
                    printf("%s with pid %d exited normally\n", node->pname, node->pid);
                }
                else
                {
                    printf("%s with pid %d exited abnormally\n", node->pname, node->pid);
                }
                deleteProcNode(node->pid, getChildProcessList());
            }
            else
            {
                if ((WIFEXITED(status) != 0) && (WEXITSTATUS(status) == EXIT_SUCCESS))
                {
                    printf("Process with pid %d exited normally\n", pid);
                }
                else
                {
                    printf("Process with pid %d exited abnormally\n", pid);
                }
            }
            prompt();
            fflush(stdout);
        }
        else
        {
            break;
        }
    }
}

void ctrlCHandler()
{
    int currentFgPid = getCurrentFgPid();
    if (currentFgPid != -1)
    {
        if (kill(currentFgPid, SIGINT) != -1)
        {
            setCurrentFgPid(-1);
        }
    }
}

void ctrlZHandler()
{
    int currentFgPid = getCurrentFgPid();
    if (currentFgPid != -1)
    {
        if (kill(currentFgPid, SIGTSTP) != -1)
        {
            setCurrentFgPid(-1);
        }
    }
}

void init()
{
    setHomeDir(pwd());
    signal(SIGINT, ctrlCHandler);
    // signal(SIGQUIT, SIG_IGN);
    signal(SIGCHLD, childProcHandler);
    signal(SIGTSTP, ctrlZHandler);
    initialiseChildProcessList();
    initHistoryList();

    printf("\n>> Welcome to B30-Shell <<\n\n");
}