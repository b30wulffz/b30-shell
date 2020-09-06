#include "headers.h"

int echo(char *data)
{
    if (data == NULL)
    {
        printf("\n");
    }
    else
    {
        printf("%s\n", data);
    }
    return 1;
}