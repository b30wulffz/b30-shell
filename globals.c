#include "headers.h"
#include "definitions.h"
#include "childproc.h"
#include "generics.h"

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

/* ***************************** */

processDetails *childProcessList = NULL;

void initialiseChildProcessList()
{
    if (childProcessList == NULL)
    {
        childProcessList = generateProcNode(0, "<No Process>", "<No Command>", 0);
    }
}

void setChildProcessList(processDetails *procList)
{
    childProcessList = procList;
}

processDetails *getChildProcessList()
{
    return childProcessList;
}

/* ***************************** */

char **historyList = NULL;
int historyLength = 0;
int historyError = 0;

void initHistoryList()
{
    if (historyList == NULL)
    {
        historyList = (char **)malloc((sizeof(char) * MAXHISTORY) * MAXHISTORY);
    }
    char *filePath = concat(getHomeDir(), "/log.txt");

    FILE *fd1 = fopen(filePath, "r");
    if (fd1 == NULL)
    {
        // creating if file does not exists
        FILE *fd2 = fopen(filePath, "w");
        if (fd2 != NULL)
        {
            fclose(fd2);
        }
        else
        {
            printf("Error: Log File Cannot be Created\n");
            historyError = 1;
        }
    }
    if (historyError == 0)
    {
        fd1 = fopen(filePath, "r");
        if (fd1 != NULL)
        {
            char *data = (char *)malloc(sizeof(char) * 50);
            int i = 0;
            while (fgets(data, 50, fd1) != NULL)
            {
                if (i >= 20)
                {
                    break;
                }
                historyList[i] = data;
                i++;
                data = (char *)malloc(sizeof(char) * 50);
            }
            free(data);
            historyLength = i;
            fclose(fd1);
        }
    }
    free(filePath);
}

char **getHistoryList()
{
    return historyList;
}

int getHistoryLength()
{
    return historyLength;
}

void setHistoryLength(int len)
{
    historyLength = len;
}
// FILE *historyFd = NULL;

// void initialiseChildProcessList()
// {
//     historyFd = fopen("command_log");
// }

/* ***************************** */

char *oldDir = NULL;

void setOldDir(char *dir)
{
    oldDir = dir;
}

char *getOldDir()
{
    return oldDir;
}

/* ***************************** */

int currentFgPid = -1;

void setCurrentFgPid(int fgPid)
{
    currentFgPid = fgPid;
}

int getCurrentFgPid()
{
    return currentFgPid;
}