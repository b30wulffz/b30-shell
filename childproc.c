#include "headers.h"
#include "globals.h"
#include "definitions.h"

int getProcNum(processDetails *processList)
{
    int count = 0;
    while (processList->next != NULL)
    {
        count++;
        processList = processList->next;
    }
    return count;
}

processDetails *getProcNode(int pid, processDetails *processList)
{
    int count = 0;
    while (processList->next != NULL)
    {
        processDetails *node = processList->next;
        if ((node->pid) == pid)
        {
            return node;
        }
        processList = processList->next;
    }
    return NULL;
}

processDetails *generateProcNode(int pid, char *pname)
{
    processDetails *node = (processDetails *)malloc(sizeof(processDetails));
    node->pid = pid;
    node->pname = pname;
    node->next = NULL;
    return node;
}

processDetails *addProcNode(int pid, char *pname, processDetails *processList)
{
    processDetails *node = generateProcNode(pid, pname);
    processDetails *temp = processList;
    while ((temp->next) != NULL)
    {
        temp = temp->next;
    }
    temp->next = node;

    return node;
}

void deleteProcNode(int pid, processDetails *processList)
{
    processDetails *temp = processList;
    while (temp->next != NULL)
    {
        processDetails *node = temp->next;
        if (node->pid == pid)
        {
            temp->next = node->next;
            free(node);
            break;
        }
        temp = temp->next;
    }
}