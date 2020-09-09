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

int main()
{
    int run = 1;
    char *buffer;
    size_t bufferLen = 1024;
    buffer = (char *)malloc(bufferLen * sizeof(char));

    signal(SIGINT, sigintHandler);
    //getting user details

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
    while (run)
    {
        // printf("<%s@%s:%s> ", pw->pw_name, uBuf->nodename, path);
        printf("<%s@%s:%s> ", username, hostname, path);
        // printf("%zu", getline(&buffer, &bufferLen, stdin));
        // printf("\n>> %s\n", buffer);

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
                parsed[parsedLength - 1] = "\0";
            }

            if (trimmedCommand != NULL)
            {
                char *substring, *substringSave;
                substring = strtok_r(trimmedCommand, " ", &substringSave);
                if (substring != NULL)
                {
                    // char *command, *commandSave;
                    // command = strtok_r(trimmedBuffer, "\n", &commandSave);
                    if (strcmp(substring, "exit") == 0)
                    {
                        run = 0;
                    }
                    else
                    {
                        int procCreate = fork();
                        if (procCreate == 0)
                        {
                            printf("this is fork\n");
                            if (strcmp(substring, "cd") == 0)
                            {
                                substring = strtok_r(NULL, "\n", &substringSave);

                                cd(substring, homeDir);
                                // currDir = pwd();

                                // int flag = 0;
                                // if (strlen(currDir) >= strlen(homeDir))
                                // {
                                //     for (int i = 0; i < strlen(homeDir); i++)
                                //     {
                                //         if (homeDir[i] != currDir[i])
                                //         {
                                //             flag = 1;
                                //             break;
                                //         }
                                //     }
                                //     if (flag == 0)
                                //     {
                                //         path = (char *)malloc(sizeof(char) * (strlen(currDir) - strlen(homeDir) + 2));
                                //         int i;
                                //         path[0] = '~';
                                //         for (i = 1; i < strlen(currDir) - strlen(homeDir) + 1; i++)
                                //         {
                                //             path[i] = currDir[strlen(homeDir) + i - 1];
                                //         }
                                //         path[i] = '\0';
                                //     }
                                // }
                                // else
                                // {
                                //     path = currDir;
                                // }
                                free(path);
                                path = rootPathResolve(pwd(), homeDir);
                            }
                            else if (strcmp(substring, "pwd") == 0)
                            {
                                char *presentDir = pwd();
                                printf("%s\n", presentDir);
                            }
                            else if (strcmp(substring, "echo") == 0)
                            {
                                substring = strtok_r(NULL, "\n", &substringSave);
                                echo(substring);
                            }
                            else if (strcmp(substring, "ls") == 0)
                            {
                                substring = strtok_r(NULL, "\n", &substringSave);
                                ls(substring, homeDir, "ls");
                            }
                            else if (strcmp(substring, "la") == 0)
                            {
                                substring = strtok_r(NULL, "\n", &substringSave);
                                ls(substring, homeDir, "la");
                            }
                            else if (strcmp(substring, "ll") == 0)
                            {
                                substring = strtok_r(NULL, "\n", &substringSave);
                                ls(substring, homeDir, "ll");
                            }
                            else if (strcmp(substring, "pinfo") == 0)
                            {
                                substring = strtok_r(NULL, "\n", &substringSave);
                                pinfo(substring, homeDir);
                            }
                            else
                            {
                                execute(parsed, parsedLength);
                            }
                            exit(0);
                        }
                        else
                        {
                            if (background == 1)
                            {
                            }
                            waitpid(procCreate, NULL, 0);
                            printf("this is parent\n");
                        }
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