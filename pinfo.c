#include "headers.h"
#include "generics.h"

char *getProcessDetails(int pid, char *key)
{
    char *status = NULL;
    char *buff = (char *)malloc(sizeof(char) * 100);
    sprintf(buff, "/proc/%d/status", pid);
    if (buff != NULL && key != NULL)
    {
        FILE *fp = fopen(buff, "r");
        if (fp != NULL)
        {
            char *line = (char *)malloc(sizeof(char) * 250);

            while (1)
            {
                if (fgets(line, 250, fp) == NULL)
                    break;
                char *val = strtok(line, ":");
                if (strcmp(val, key) == 0)
                {
                    val = strtok(NULL, ":");
                    status = trim(val, 1);
                    break;
                }
            }
            fclose(fp);
        }
    }
    free(buff);
    return status;
}
/*
int getMemory(int pid)
{
    int memory = 0;
    char *buff = (char *)malloc(sizeof(char) * 100);
    sprintf(buff, "/proc/%d/statm", pid);
    if (buff != NULL)
    {
        FILE *fp = fopen(buff, "r");
        if (fp != NULL)
        {
            char *line = (char *)malloc(sizeof(char) * 250);
            if (fgets(line, 250, fp) != NULL)
            {
                char *temp = strtok(line, " ");
                memory = atoi(line);
            }
            fclose(fp);
        }
        // else
        // {
        //     printf("Error: Process doesnot exist.\n");
        // }
    }
    free(buff);
    return memory;
}

char *getVirtualMemory(int pid)
{
    char *status = NULL;
    char *buff = (char *)malloc(sizeof(char) * 100);
    sprintf(buff, "/proc/%d/status", pid);
    if (buff != NULL)
    {
        FILE *fp = fopen(buff, "r");
        if (fp != NULL)
        {
            char *line = (char *)malloc(sizeof(char) * 250);

            while (1)
            {
                if (fgets(line, 250, fp) == NULL)
                    break;
                char *val = strtok(line, ":");
                if (strcmp(val, "VmSize") == 0)
                {
                    val = strtok(NULL, ":");
                    status = trim(val, 1);
                    break;
                }
            }
            fclose(fp);
        }
        // else
        // {
        //     printf("Error: Process doesnot exist.\n");
        // }
    }
    free(buff);
    return status;
}
*/
char *getProcessExecutablePath(int pid, char *homeDir)
{
    char *path = "";
    char *buff = (char *)malloc(sizeof(char) * 100);
    sprintf(buff, "/proc/%d/exe", pid);
    if (buff != NULL)
    {
        FILE *fp = fopen(buff, "r");
        if (fp != NULL)
        {
            int path_len = 2048;
            path = (char *)malloc(sizeof(char) * path_len);
            readlink(buff, path, path_len);
            fclose(fp);
        }
    }
    free(buff);
    path = rootPathResolve(path, homeDir);
    return path;
}

void pinfo(char **parsedCommand, int parsedLength, char *homeDir)
{
    int pid = getpid();
    if (parsedLength > 1)
    {
        pid = atoi(parsedCommand[1]);
    }

    printf("pid -- %d\n", pid);
    if (getProcessDetails(pid, "State") != NULL)
    {
        printf("Process Status  -- %s\n", getProcessDetails(pid, "State"));
        printf("memory -- %s\n", getProcessDetails(pid, "VmSize"));
        printf("Executable Path -- %s\n", getProcessExecutablePath(pid, homeDir));
    }
    else
    {
        printf("Error: Process with corresponding process id does not exists.\n");
    }
}