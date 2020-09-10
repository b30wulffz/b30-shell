#include "headers.h"
#include "globals.h"
#include "generics.h"

void saveCommand(char *command)
{
    if (command != NULL)
    {
        char **historyList = getHistoryList();
        int historyLength = getHistoryLength();

        if (historyLength > 0)
        {
            if (strcmp(historyList[historyLength - 1], command) == 0)
            {
                return;
            }
        }

        if (historyLength == MAXHISTORY)
        {
            int i;
            for (i = 0; i < MAXHISTORY - 1; i++)
            {
                historyList[i] = historyList[i + 1];
            }
            historyList[i] = command;
        }
        else
        {
            historyList[historyLength] = command;
            historyLength++;
            setHistoryLength(historyLength);
        }

        char *filePath = concat(getHomeDir(), "/log.txt");

        FILE *fd = fopen(filePath, "w");
        free(filePath);

        for (int i = 0; i < historyLength; i++)
        {
            char *cmd = historyList[i];
            // if (cmd[strlen(cmd) - 1] == '\n')
            // {
            fprintf(fd, "%s", historyList[i]);
            // }
            // else
            // {
            //     fprintf(fd, "%s\n", historyList[i]);
            // }
            if (cmd[strlen(cmd) - 1] != '\n')
            {
                fprintf(fd, "\n");
            }
        }
        fclose(fd);
    }
}

void history()
{
    char **historyList = getHistoryList();
    int upper = getHistoryLength();
    int lower = upper - HISTORYCOUNT;
    if (lower < 0)
    {
        lower = 0;
    }
    for (int i = lower; i < upper; i++)
    {
        char *cmd = historyList[i];
        printf("%s", cmd);
        if (cmd[strlen(cmd) - 1] != '\n')
        {
            printf("\n");
        }
    }
}