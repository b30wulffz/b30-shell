#ifndef __ENVVAR_H
#define __ENVVAR_H

void setEnv(char **parsedCommand, int parsedLength);
void unsetEnv(char **parsedCommand, int parsedLength);
void getEnv(char **parsedCommand, int parsedLength);

#endif
