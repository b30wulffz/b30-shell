#ifndef __GENERICS_H
#define __GENERICS_H

char *getHostName();
char *getCurrentUser();
char *trim(char *src);
char *concat(char *str1, char *str2);
char *substr(char *str, int start, int end);
char *rootPathResolve(char *path, char *homeDir);

#endif