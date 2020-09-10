#include "headers.h"
#include "generics.h"
#include "globals.h"

#include "init.h"
#include "prompt.h"
#include "childstatus.h"
#include "shellinput.h"

void sigintHandler(int signalId)
{
    signal(SIGINT, sigintHandler);
    // printf("Sigint\n");
    fflush(stdin);
    // exit(0);
}

struct procDetails
{
    int pid;
    struct procDetails *next;
};

struct procDetails *addProcNode(int pid)
{
    struct procDetails *temp = (struct procDetails *)malloc(sizeof(struct procDetails));
    temp->pid = -1;
    temp->next = NULL;
    return temp;
}

int main()
{
    int run = 1;

    init();

    char *homeDir = getHomeDir();

    // struct procDetails *childProcesses = addProcNode(-1);
    int maxProcessCount = 1024, childProcessCount = 0;
    int childProcesses[maxProcessCount];

    while (run)
    {
        checkChildStatus(childProcesses, childProcessCount, maxProcessCount);
        prompt(homeDir);
        shellInput(homeDir);
    }

    return 0;
}