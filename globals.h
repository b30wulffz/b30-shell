#ifndef __GLOBALS_H
#define __GLOBALS_H

#include "definitions.h"

void setHomeDir(char *path);
char *getHomeDir();

void initialiseChildProcessList();
void setChildProcessList(processDetails *procList);
processDetails *getChildProcessList();

void initHistoryList();
char **getHistoryList();
int getHistoryLength();
void setHistoryLength(int len);

// extern processDetails *childProcessList;

#endif