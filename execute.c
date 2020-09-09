#include "headers.h"

void execute(char **data, int len)
{
    if (data != NULL && len > 0)
    {
        execvp(data[0], data);
        printf("Error: Command not found\n");
    }
}