#include "headers.h"
#include "generics.h"
#include "globals.h"

#include "cd.h"
#include "pwd.h"
#include "echo.h"
#include "ls.h"
#include "pinfo.h"
#include "execute.h"
#include "cleanup.h"
#include "history.h"

void executeCommand(char **parsed, int parsedLength)
{
    int isBackground = 0;

    if (strcmp(parsed[parsedLength - 1], "&") == 0)
    {
        isBackground = 1;
        parsed[parsedLength - 1] = NULL;
        parsedLength--;
    }
    else
    {
        parsed[parsedLength] = NULL;
    }

    if (parsedLength > 0)
    {
        char *homeDir = getHomeDir();
        char *command = parsed[0];

        saveCommand(command);

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
        else if (strcmp(command, "history") == 0)
        {
            history();
        }
        else if (strcmp(command, "exit") == 0)
        {
            cleanup();
        }
        else
        {
            execute(parsed, parsedLength, isBackground);
        }
    }
}

// void parseIORedir(char **parsed, int parsedLength)
// {
//     for(int i=0; i<parsedLength; i++){
//         if
//     }
// }

void runCommand(char *command)
{
    // printf(" --->%s<---\n", command);
    char *trimmedCommand = trim(command, 0);

    char **parsed = (char **)malloc((sizeof(char) * 1024) * 1024);
    int parsedLength = split(trimmedCommand, ' ', parsed, 1024);

    if (parsedLength > 0 && parsed != NULL)
    {
        executeCommand(parsed, parsedLength);
    }

    free(parsed);
}

void parseIORedir2(char *command)
{
    char **splitCommand = (char **)malloc((sizeof(char) * 1024) * 1024);
    int splitCommandLength = split(command, '|', splitCommand, 1024);

    int vfile[2];
    if (pipe(vfile) == -1)
    {
        perror("Error Creating Pipe");
        exit(1);
    }
    int childPid = fork();
    if (childPid == -1)
    {
        perror("Error Creating Fork");
        exit(1);
    }
    else if (childPid == 0)
    {
        // sleep(2);
        // close(vfile[0]);
        // int bkp = dup(STDIN_FILENO);
        // if (dup2(vfile[1], STDIN_FILENO) == -1)
        // {
        //     perror("Error duplicating STDIN file descriptor");
        //     exit(1);
        // }
        if (dup2(vfile[0], STDOUT_FILENO) == -1)
        {
            perror("Error duplicating STDOUT file descriptor");
            exit(1);
        }
        runCommand(splitCommand[0]);
        // write(vfile[1], splitCommand[0], strlen(splitCommand[0]));
        close(vfile[1]);
    }
    else
    {
        close(vfile[1]);
        printf("parent\n");
        wait(NULL);

        char buf;
        while (read(vfile[0], &buf, 1) > 0)
            write(STDOUT_FILENO, &buf, 1);
        write(STDOUT_FILENO, "\n\n\n", 3);
        close(vfile[0]);
        exit(EXIT_SUCCESS);
    }

    // for (int i = 0; i < splitCommandLength - 1; i++)
    // {

    //     printf("%s\n", splitCommand[i]);
    // }
    /*
    for (int i = 0; i < strlen(command); i++)
    {
        if (command[i] == '|')
        {
            int vfile[2];
            if (pipe(vfile) == -1)
            {
                perror("Error Creating Pipe");
                exit(1);
            }
            int childPid = fork();
            if (childPid == -1)
            {
                perror("Error Creating Fork");
                exit(1);
            }
            else if (childPid == 0)
            {
                //child reads from pipe
                close(vfile[1]);
                // printf("%s\n", vfile[0]);
                // int c;
                // while ((c = fgetc(vfile[0])) != EOF)
                //     putchar(c);
                // close(vfile[0]);
                printf("child\n");
                char buf;
                while (read(vfile[0], &buf, 1) > 0)
                    write(STDOUT_FILENO, &buf, 1);
                write(STDOUT_FILENO, "\n", 1);
                close(vfile[0]);
                exit(EXIT_SUCCESS);
            }
            else
            {
                //parent writes in pipe and then waits for child to read
                sleep(2);
                close(vfile[0]);
                write(vfile[1], "Hi there", 9);
                close(vfile[1]);
                wait(NULL);
            }
        }
        else if (command[i] == '>')
        {
            printf(">: %d\n", i);
        }
        else if (command[i] == '<')
        {
            printf("<: %d\n", i);
        }
    }*/
    exit(EXIT_SUCCESS);
}

void parseIORedir(char *command)
{
    char **splitCommand = (char **)malloc((sizeof(char) * 1024) * 1024);
    int splitCommandLength = split(command, '|', splitCommand, 1024);

    if (splitCommandLength > 0)
    {
        int stdinBkp = dup(STDIN_FILENO);
        if (stdinBkp == -1)
        {
            perror("Error duplicating STDIN file descriptor");
            return;
        }
        int stdoutBkp = dup(STDOUT_FILENO);
        if (stdoutBkp == -1)
        {
            perror("Error duplicating STDOUT file descriptor");
            return;
        }

        int vfile[2];
        if (pipe(vfile) == -1)
        {
            perror("Error Creating Pipe");
            return;
        }

        if (dup2(vfile[0], STDIN_FILENO) == -1)
        {
            perror("Error overwriting STDIN file descriptor");
            return;
        }
        if (dup2(vfile[1], STDOUT_FILENO) == -1)
        {
            perror("Error overwriting STDOUT file descriptor");
            return;
        }

        for (int i = 0; i < splitCommandLength - 1; i++)
        {
            runCommand(splitCommand[i]);
        }

        if (dup2(stdoutBkp, STDOUT_FILENO) == -1)
        {
            perror("Error overwriting STDOUT file descriptor");
            return;
        }
        if (splitCommandLength == 1)
        {
            if (dup2(stdinBkp, STDIN_FILENO) == -1)
            {
                perror("Error overwriting STDIN file descriptor");
                return;
            }
        }
        else
        {
            // close(vfile[0]);
            close(vfile[1]);
        }
        runCommand(splitCommand[splitCommandLength - 1]);
        close(vfile[0]);
    }
    free(splitCommand);
    // sleep(2);
    // close(vfile[0]);

    // write(vfile[1], splitCommand[0], strlen(splitCommand[0]));

    // printf("parent\n");
    // wait(NULL);

    // char buf;
    // while (read(vfile[0], &buf, 1) > 0)
    //     write(STDOUT_FILENO, &buf, 1);
    // write(STDOUT_FILENO, "\n\n\n", 3);
    // close(vfile[0]);
    // exit(EXIT_SUCCESS);
    // fflush(stdin);
    // fflush(stdout);
}

void parseInput(char *buffer)
{
    char *trimmedBuffer = trim(buffer, 1);

    char **splitCommands = (char **)malloc((sizeof(char) * 1024) * 1024);
    int splitCommandsLength = split(trimmedBuffer, ';', splitCommands, 1024);

    for (int i = 0; i < splitCommandsLength; i++)
    {
        char *trimmedCommand = trim(splitCommands[i], 0);
        // runCommand(trimmedCommand);
        parseIORedir(trimmedCommand);
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