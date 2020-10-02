#ifndef __DEFINITIONS_H
#define __DEFINITIONS_H

struct procDetails
{
    int pid;
    char *pname;
    char *command;
    int jobid;
    struct procDetails *next;
};

typedef struct procDetails processDetails;

#endif