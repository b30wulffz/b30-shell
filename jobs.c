#include "headers.h"
#include "globals.h"
#include "definitions.h"
#include "pinfo.h"
#include "childproc.h"

void jobs()
{
    processDetails *childProcessList = getChildProcessList();
    processDetails *process = childProcessList->next;

    while (process != NULL)
    {
        char *status_info = getProcessDetails(process->pid, "State");
        char *status = "Running";
        if (status_info[0] == 'T' || status_info[0] == 'Z' || status_info[0] == 'X')
        {
            status = "Stopped";
        }
        printf("[%d] %s %s [%d]\n", process->jobid, status, process->command, process->pid);
        process = process->next;
    }
}

void kjob(char **parsedCommand, int parsedLength)
{
    if (parsedLength == 3)
    {
        int jobNum = atoi(parsedCommand[1]);
        int signalNum = atoi(parsedCommand[2]);

        processDetails *childProcessList = getChildProcessList();
        processDetails *process = childProcessList->next;

        int found = 0;
        while (process != NULL)
        {
            if (process->jobid == jobNum)
            {
                found = 1;
                break;
            }
            process = process->next;
        }
        if (found)
        {
            if (kill(process->pid, signalNum) != 0)
            {
                perror("Process cannot be killed");
            }
        }
        else
        {
            printf("Error: Job id does not exist\n");
        }
    }
    else
    {
        printf("Unsufficient arguments supplied\n");
    }
}

void overkill()
{
    processDetails *childProcessList = getChildProcessList();
    processDetails *process = childProcessList->next;

    while (process != NULL)
    {
        processDetails *nextProcess = process->next;
        if (kill(process->pid, SIGKILL) != 0)
        {
            perror("Process cannot be killed");
        }
        process = nextProcess;
    }
}