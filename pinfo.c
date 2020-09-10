#include "headers.h"
#include "generics.h"

char *getProcessStatus(int pid)
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
                if (strcmp(val, "State") == 0)
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

char *getExecutablePath(int pid, char *homeDir)
{
    char *path = "";
    char *buff = (char *)malloc(sizeof(char) * 100);
    sprintf(buff, "/proc/%d/exe", pid);
    if (buff != NULL)
    {
        FILE *fp = fopen(buff, "r");
        if (fp != NULL)
        {

            // fseek(fp, 0, SEEK_END);
            // long len = ftell(fp);
            // fseek(fp, 0, SEEK_SET);

            // char *temp = (char *)malloc(sizeof(char) * (len + 1));

            // fread(temp, 1, len, fp);

            int path_len = 2048;
            path = (char *)malloc(sizeof(char) * path_len);
            readlink(buff, path, path_len);
            fclose(fp);
        }
        // else
        // {
        //     printf("Error: Process doesnot exist.\n");
        // }
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

    // if (buff != NULL)
    // {
    //     char *rowStore, *colStore;
    //     char *row = strtok_r(buff, "\n", rowStore);
    //     while (row != NULL)
    //     {
    //         printf("%s", row);
    //         row = strtok_r(NULL, "\n", rowStore);
    //     }
    // }

    printf("pid -- %d\n", pid);
    if (getProcessStatus(pid) != NULL)
    {
        printf("Process Status  -- %s\n", getProcessStatus(pid));
        printf("memory -- %s\n", getVirtualMemory(pid));
        printf("Executable Path -- %s\n", getExecutablePath(pid, homeDir));
    }
    else
    {
        printf("Error: Process with corresponding process id does not exists.\n");
    }

    // FILE *fp = fopen(buff, "r");
    // if (fp != NULL)
    // {
    //     int c;
    //     while (c = fgetc(fp))
    //     {
    //         if (feof(fp))
    //         {
    //             break;
    //         }
    //         printf("%c", c);
    //     }
    //     printf("\n%d %s", pid, buff);
    // }
    // else
    // {
    //     printf("Error: Process doesnot exist.\n");
    // }
}