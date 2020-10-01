#include "headers.h"

void setEnv(char **parsedCommand, int parsedLength)
{
    if (parsedLength == 3)
    {
        if (setenv(parsedCommand[1], parsedCommand[2], 1) != -1)
        {
            printf("%s=%s\n", parsedCommand[1], parsedCommand[2]);
        }
        else
        {
            printf("setenv: [Error] environment variable cannot be set.\n");
        }
    }
    else
    {
        printf("setenv: Unsufficient argument supplied.\n");
    }
}

void unsetEnv(char **parsedCommand, int parsedLength)
{
    if (parsedLength == 2)
    {
        if (unsetenv(parsedCommand[1]) != -1)
        {
            printf("unsetenv: Successfully unset %s\n", parsedCommand[1]);
        }
        else
        {
            printf("unsetenv: [Error] environment variable cannot be unset\n");
        }
    }
    else
    {
        printf("unsetenv: Unsufficient argument supplied\n");
    }
}

void getEnv(char **parsedCommand, int parsedLength)
{
    if (parsedLength == 2)
    {
        char *value;
        value = getenv(parsedCommand[1]);
        if (value != NULL)
        {
            printf("%s\n", value);
        }
        else
        {
            printf("getenv: %s does not exist\n", parsedCommand[1]);
        }
    }
    else
    {
        printf("getenv: Unsufficient argument supplied\n");
    }
}