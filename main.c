#include "headers.h"
#include "generics.h"
#include "pwd.h"
#include "cd.h"
#include "echo.h"
#include "ls.h"

int main()
{
    int run = 1;
    char *buffer;
    size_t bufferLen = 1024;
    buffer = (char *)malloc(bufferLen * sizeof(char));

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

    char *path = "~";
    while (run)
    {
        // printf("<%s@%s:%s> ", pw->pw_name, uBuf->nodename, path);
        printf("<%s@%s:%s> ", username, hostname, path);
        // printf("%zu", getline(&buffer, &bufferLen, stdin));
        // printf("\n>> %s\n", buffer);

        getline(&buffer, &bufferLen, stdin);

        char *trimmedBuffer = trim(buffer);

        printf("--->%s<---\n", trimmedBuffer);

        char *substring, *substringSave;
        substring = strtok_r(trimmedBuffer, " ", &substringSave);

        char *command, *commandSave;
        command = strtok_r(trimmedBuffer, "\n", &commandSave);

        if (strcmp(substring, "cd") == 0)
        {
            substring = strtok_r(NULL, "\n", &substringSave);

            cd(substring, homeDir);
            currDir = pwd();

            int flag = 0;
            if (strlen(currDir) >= strlen(homeDir))
            {
                for (int i = 0; i < strlen(homeDir); i++)
                {
                    if (homeDir[i] != currDir[i])
                    {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0)
                {
                    path = (char *)malloc(sizeof(char) * (strlen(currDir) - strlen(homeDir) + 2));
                    int i;
                    path[0] = '~';
                    for (i = 1; i < strlen(currDir) - strlen(homeDir) + 1; i++)
                    {
                        path[i] = currDir[strlen(homeDir) + i - 1];
                    }
                    path[i] = '\0';
                }
            }
            else
            {
                path = currDir;
            }
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
            ls(substring);
        }

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