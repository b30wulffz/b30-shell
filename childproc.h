#ifndef __CHILDPROC_H
#define __CHILDPROC_H

#include "definitions.h"

// int getProcNum(processDetails *processList);
processDetails *getProcNode(int pid, processDetails *processList);
processDetails *generateProcNode(int pid, char *pnam, char *command, int jobid);
processDetails *addProcNode(int pid, char *pname, char *command, processDetails *processList);
void deleteProcNode(int pid, processDetails *processList);

#endif