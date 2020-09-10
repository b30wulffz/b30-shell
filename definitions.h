#ifndef __DEFINITIONS_H
#define __DEFINITIONS_H

struct procDetails
{
    int pid;
    char *pname;
    struct procDetails *next;
};

typedef struct procDetails processDetails;

#endif