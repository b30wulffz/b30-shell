#include "headers.h"

int echo(char **parsedCommand, int parsedLength)
{
    if (parsedLength > 1)
    {
        for (int i = 1; i < parsedLength; i++)
        {
            if (i > 1)
            {
                printf(" ");
            }
            printf("%s", parsedCommand[i]);
        }
    }
    printf("\n");
    return 1;
}