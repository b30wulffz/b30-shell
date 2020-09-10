#include "headers.h"
#include "generics.h"
#include "pwd.h"
#include "cd.h"
#include "echo.h"
#include "ls.h"
#include "pinfo.h"
#include "execute.h"

void sigintHandler(int signalId)
{
    signal(SIGINT, sigintHandler);
    // printf("Sigint\n");
    fflush(stdin);
    // exit(0);
}

struct procDetails
{
    int pid;
    struct procDetails *next;
};

struct procDetails *addProcNode(int pid)
{
    struct procDetails *temp = (struct procDetails *)malloc(sizeof(struct procDetails));
    temp->pid = -1;
    temp->next = NULL;
    return temp;
}

int main()
{
    int run = 1;
    char *buffer;
    size_t bufferLen = 1024;
    buffer = (char *)malloc(bufferLen * sizeof(char));

    // signal(SIGINT, sigintHandler);
    //getting user details
    signal(SIGINT, SIG_IGN); // IGNORE ALL SIGNALS
    signal(SIGTSTP, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);

    // signal(SIGCHLD, SIG_IGN);
    // struct utsname *uBuf;
    // uBuf = (struct utsname *)malloc(sizeof(struct utsname));
    // uname(uBuf);

    // char *hostName;
    // size_t hostNameLen = 1024;
    // gethostname(hostName, hostNameLen);

    // struct passwd *pw;
    // pw = getpwuid(geteuid());

    char *username, *hostname;

    username = getCurrentUser();
    hostname = getHostName();

    char *homeDir, *currDir;
    homeDir = currDir = pwd();

    char *path = (char *)malloc(sizeof(char) * 2);
    path[0] = '~';
    path[1] = '\0';

    // struct procDetails *childProcesses = addProcNode(-1);
    int maxProcessCount = 1024, childProcessCount = 0;

    int childProcesses[maxProcessCount];

    int pid = getpid();

    while (run)
    {
        // printf("<%s@%s:%s> ", pw->pw_name, uBuf->nodename, path);
        printf("<%s@%s:%s> ", username, hostname, path);
        // printf("%zu", getline(&buffer, &bufferLen, stdin));
        // printf("\n>> %s\n", buffer);

        // struct procDetails *tempProcList = childProcesses->next;
        // while (tempProcList != NULL)
        // {
        //     printf("->%d ", tempProcList->pid);
        //     tempProcList = tempProcList->next;
        // }

        int status;
        int res = waitpid(-1, &status, WNOHANG);
        for (int i = 0; i < childProcessCount; i++)
        {
            int status = 0;
            // ->printf("->%d : ", childProcesses[i]);
            // waitpid(childProcesses[i], &status, WNOHANG);
            // printf("%d \n", WIFEXITED(status));
            // -> printf("%d \n", kill(childProcesses[i], 0));
        }
        if (res > 0)
        {
            if (WIFEXITED(status) == 1)
            {
                // ->printf("Defunt: %d %d", res, WEXITSTATUS(status));
            }
        }

        getline(&buffer, &bufferLen, stdin);

        char *trimmedBuffer = trim(buffer, 1);

        char **splitCommands = (char **)malloc((sizeof(char) * 1024) * 1024);
        int splitCommandsLength = split(trimmedBuffer, ';', splitCommands, 1024);

        for (int i = 0; i < splitCommandsLength; i++)
        {
            char *trimmedCommand = trim(splitCommands[i], 0);

            printf("--->%s<---\n", trimmedCommand);
            char **parsed = (char **)malloc((sizeof(char) * 1024) * 1024);
            int parsedLength = split(trimmedCommand, ' ', parsed, 1024);

            int background = 0;

            if (strcmp(parsed[parsedLength - 1], "&") == 0)
            {
                background = 1;
                parsed[parsedLength - 1] = NULL;
                parsedLength--;
            }

            if (parsed != NULL && parsedLength > 0)
            {
                // char *substring, *substringSave;
                // substring = strtok_r(trimmedCommand, " ", &substringSave);
                char *command = parsed[0];
                if (command != NULL)
                {
                    // char *command, *commandSave;
                    // command = strtok_r(trimmedBuffer, "\n", &commandSave);
                    if (strcmp(command, "exit") == 0)
                    {
                        run = 0;
                    }
                    else
                    {
                        int procCreate = fork();
                        // if (background == 1)
                        // {
                        //     setpgid(0, 0);
                        // }
                        if (procCreate > 0)
                        {
                            if (background == 1)
                            {
                                // kill(procCreate, SIGTERM);
                                childProcesses[childProcessCount] = procCreate;
                                childProcessCount++;
                                setpgid(procCreate, 0);
                                tcsetpgrp(STDIN_FILENO, pid);
                            }
                            // else
                            // {
                            //     waitpid(procCreate, NULL, 0);
                            // }
                            printf("this is parent\n");
                        }
                        else if (procCreate == 0)
                        {
                            // if (background == 1)
                            // {
                            setpgid(0, 0);
                            // }
                            printf("this is fork\n");
                            if (strcmp(command, "cd") == 0)
                            {
                                // substring = strtok_r(NULL, "\n", &substringSave);
                                cd(parsed[1], homeDir);
                                free(path);
                                path = rootPathResolve(pwd(), homeDir);
                            }
                            else if (strcmp(command, "pwd") == 0)
                            {
                                char *presentDir = pwd();
                                printf("%s\n", presentDir);
                            }
                            else if (strcmp(command, "echo") == 0)
                            {
                                // substring = strtok_r(NULL, "\n", &substringSave);
                                echo(parsed, parsedLength);
                            }
                            else if (strcmp(command, "ls") == 0)
                            {
                                // substring = strtok_r(NULL, "\n", &substringSave);
                                ls(parsed, parsedLength, homeDir, "ls");
                            }
                            else if (strcmp(command, "la") == 0)
                            {
                                // substring = strtok_r(NULL, "\n", &substringSave);
                                ls(parsed, parsedLength, homeDir, "la");
                            }
                            else if (strcmp(command, "ll") == 0)
                            {
                                // substring = strtok_r(NULL, "\n", &substringSave);
                                ls(parsed, parsedLength, homeDir, "ll");
                            }
                            else if (strcmp(command, "pinfo") == 0)
                            {
                                // substring = strtok_r(NULL, "\n", &substringSave);
                                pinfo(parsed, parsedLength, homeDir);
                            }
                            else
                            {
                                execute(parsed, parsedLength);
                            }
                            exit(0);
                        }
                        // else
                        // {
                        //     if (background == 1)
                        //     {
                        //         // kill(procCreate, SIGTERM);
                        //         childProcesses[childProcessCount] = procCreate;
                        //         childProcessCount++;
                        //         setpgid(pid, 0);
                        //         tcsetpgrp(STDIN_FILENO, getpgrp());
                        //     }
                        //     else
                        //     {
                        //         waitpid(procCreate, NULL, 0);
                        //     }
                        //     printf("this is parent\n");
                        // }
                    }
                }
                free(trimmedCommand);
            }
        }
        free(splitCommands);
        free(trimmedBuffer);
        // while (token != NULL)
        // {
        //     printf("%s\n", token);
        //     token = strtok(NULL, " ");
        // }
    }
    free(buffer);
    return 0;
}