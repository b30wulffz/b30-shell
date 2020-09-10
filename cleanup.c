#include "headers.h"
#include "definitions.h"
#include "globals.h"

void cleanup()
{
    printf("> Exiting . . .\n");
    char *homeDir = getHomeDir();
    free(homeDir);

    char **historyList = getHistoryList();
    free(historyList);

    processDetails *temp, *head;
    temp = head = getChildProcessList();
    while ((temp->next) != NULL)
    {
        processDetails *node = temp->next;
        kill(node->pid, SIGKILL);
        printf("> Killed %s with pid %d\n", node->pname, node->pid);
        head = temp;
        temp = temp->next;
        free(head);
    }
    free(head);
    printf("\n############################################################\n\n");
    printf("Thanks for using B30-Shell\n");
    printf("\n");
    printf("# Developed By: Shlok Pandey\n");
    printf("# Roll Number: 2020121008\n");
    printf("\n------------------------------------------------------------\n\n");
    exit(0);
}