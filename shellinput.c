#include "headers.h"
#include "generics.h"
#include "globals.h"

#include "cd.h"
#include "pwd.h"
#include "echo.h"
#include "ls.h"
#include "pinfo.h"
#include "execute.h"

void executeCommand(char **parsed, int parsedLength)
{
    int isBackground = 0;
    if (strcmp(parsed[parsedLength - 1], "&") == 0)
    {
        isBackground = 1;
        parsed[parsedLength - 1] = NULL;
        parsedLength--;
    }

    char *homeDir = getHomeDir();
    char *command = parsed[0];
    if (strcmp(command, "cd") == 0)
    {
        cd(parsed[1], homeDir);
    }
    else if (strcmp(command, "pwd") == 0)
    {
        printf("%s\n", pwd());
    }
    else if (strcmp(command, "echo") == 0)
    {
        echo(parsed, parsedLength);
    }
    else if (strcmp(command, "ls") == 0)
    {
        ls(parsed, parsedLength, homeDir, "ls");
    }
    else if (strcmp(command, "la") == 0)
    {
        ls(parsed, parsedLength, homeDir, "la");
    }
    else if (strcmp(command, "ll") == 0)
    {
        ls(parsed, parsedLength, homeDir, "ll");
    }
    else if (strcmp(command, "pinfo") == 0)
    {
        pinfo(parsed, parsedLength, homeDir);
    }
    else
    {
        execute(parsed, parsedLength, isBackground);
    }
}

void runCommand(char *command)
{
    printf("--->%s<---\n", command);
    char **parsed = (char **)malloc((sizeof(char) * 1024) * 1024);
    int parsedLength = split(command, ' ', parsed, 1024);

    if (parsedLength > 0 && parsed != NULL)
    {
        executeCommand(parsed, parsedLength);
    }

    free(parsed);
}

void parseInput(char *buffer)
{
    char *trimmedBuffer = trim(buffer, 1);

    char **splitCommands = (char **)malloc((sizeof(char) * 1024) * 1024);
    int splitCommandsLength = split(trimmedBuffer, ';', splitCommands, 1024);

    for (int i = 0; i < splitCommandsLength; i++)
    {
        char *trimmedCommand = trim(splitCommands[i], 0);
        runCommand(trimmedCommand);
        free(trimmedCommand);
    }

    free(splitCommands);
    free(trimmedBuffer);
}

void shellInput(char *homeDir)
{
    int pid = getpid();

    char *buffer;
    size_t bufferLen = 1024;
    buffer = (char *)malloc(bufferLen * sizeof(char));

    getline(&buffer, &bufferLen, stdin);

    parseInput(buffer);

    free(buffer);
}