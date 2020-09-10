#ifndef __PINFO_H
#define __PINFO_H

void pinfo(char **parsedCommand, int parsedLength, char *homeDir);
char *getProcessDetails(int pid, char *key);
char *getProcessExecutablePath(int pid, char *homeDir);

#endif