#include "headers.h"
#include "pwd.h"
#include "generics.h"

char *permissions(mode_t mode)
{
    char *perm = (char *)malloc(11 * sizeof(char));
    perm[0] = S_ISDIR(mode) ? 'd' : '-';
    perm[1] = mode & S_IRUSR ? 'r' : '-';
    perm[2] = mode & S_IWUSR ? 'w' : '-';
    perm[3] = mode & S_IXUSR ? 'x' : '-';
    perm[4] = mode & S_IRGRP ? 'r' : '-';
    perm[5] = mode & S_IWGRP ? 'w' : '-';
    perm[6] = mode & S_IXGRP ? 'x' : '-';
    perm[7] = mode & S_IROTH ? 'r' : '-';
    perm[8] = mode & S_IWOTH ? 'w' : '-';
    perm[9] = mode & S_IXOTH ? 'x' : '-';
    perm[10] = '\0';
    return perm;
}

void printFlagL(struct dirent *file, struct stat fileStat)
{
    char *perm = permissions(fileStat.st_mode);
    char *userName = (getpwuid(fileStat.st_uid))->pw_name;
    char *groupName = (getgrgid(fileStat.st_gid))->gr_name;
    char *f_time = (char *)malloc(14 * sizeof(char));
    strftime(f_time, 14, "%h %d %H:%M", localtime(&fileStat.st_mtime));

    // printf("%ld %ld %16ld %d %16s \n", perm, fileStat.st_nlink, fileStat.st_size, fileStat.st_size, fileStat.st_atime, file->d_name);
    printf("%10s %ld %s %s %6ld %s %s", perm, fileStat.st_nlink, userName, groupName, fileStat.st_size, f_time, file->d_name);
    if (perm[0] == 'd')
    {
        printf("/");
    }
    printf("\n");
    free(perm);
    free(f_time);
}

void printLS(char *name, int flag_a, int flag_l)
{
    DIR *dir = opendir(name);
    struct dirent *file;
    struct stat fileStat;
    // printf("->%s\n", name);

    if (dir != NULL)
    {
        if (flag_l == 1)
        {
            int total = 0;
            while ((file = readdir(dir)) != NULL)
            {
                char *buf = (char *)malloc(sizeof(char) * BUFFSIZE);
                sprintf(buf, "%s/%s", name, file->d_name);
                stat(buf, &fileStat);
                total += fileStat.st_blocks;
                free(buf);
            }
            printf("total %d\n", total / 2);
        }
        dir = opendir(name);
        while ((file = readdir(dir)) != NULL)
        {
            char *buf = (char *)malloc(sizeof(char) * BUFFSIZE);
            sprintf(buf, "%s/%s", name, file->d_name);
            stat(buf, &fileStat);
            if (flag_a == 1 && flag_l == 1)
            {
                printFlagL(file, fileStat);
            }
            else if (flag_a == 1)
            {
                printf("%s  ", file->d_name);
            }
            else if (flag_l == 1)
            {
                if (file->d_name[0] != '.')
                {
                    printFlagL(file, fileStat);
                }
            }
            else
            {
                if (file->d_name[0] != '.')
                {
                    printf("%s  ", file->d_name);
                }
            }
            free(buf);

            // printf("%16ld %16s \n", fileStat.st_size, file->d_name);
        }
        printf("\n");
    }
    else
    {
        // printf("%s not found\n", name);
        char *buf = (char *)malloc(sizeof(char) * BUFFSIZE);
        sprintf(buf, "ls: cannot access '%s'", name);
        perror(buf);
    }
}

int ls(char *data, char *homeDir, char *mode)
{
    if (data != NULL)
    {
        // printf("##%s", data);
        char *tmpData;
        if (data != NULL)
        {
            tmpData = (char *)malloc(strlen(data) * sizeof(char));
            strcpy(tmpData, data);
        }
        char *word = strtok(data, " ");

        int flag_a, flag_l;
        flag_a = flag_l = 0;

        if (strcmp(mode, "ll") == 0)
        {
            flag_a = flag_l = 1;
        }
        else if (strcmp(mode, "la") == 0)
        {
            flag_a = 1;
        }

        int count = 0;

        // extracting flags

        while (word != NULL)
        {
            if (word[0] == '-')
            {
                for (int i = 1; i < strlen(word); i++)
                {
                    if (word[i] == 'a')
                    {
                        flag_a = 1;
                    }
                    else if (word[i] == 'l')
                    {
                        flag_l = 1;
                    }
                }
            }
            else
            {
                count++;
            }
            word = strtok(NULL, " ");
        }

        // for arguments

        if (count > 0)
        {
            // if arguments are supplied
            word = strtok(tmpData, " ");
            // printf("$$%s", word);
            while (word != NULL)
            {
                if (word[0] != '-')
                {
                    char *path = word, flag = 0;
                    if (word[0] == '~' && (strlen(word) == 1 || (word[1] == '/')))
                    {
                        char *tmp = substr(word, 1, strlen(word));
                        path = concat(homeDir, tmp);
                        flag = 1;
                        free(tmp);
                    }
                    // else
                    // {
                    //     path = concat(pwd(), word);
                    // }
                    if (count > 1)
                    {
                        printf("%s:\n", path);
                    }
                    printLS(path, flag_a, flag_l);
                    // printf("\n");

                    if (flag == 1)
                    {
                        free(path);
                    }
                }
                word = strtok(NULL, " ");
            }
        }
        else
        {
            //if only flags are supplied
            printLS(pwd(), flag_a, flag_l);
        }
    }
    else
    {
        if (strcmp(mode, "ll") == 0)
        {
            printLS(pwd(), 1, 1);
        }
        else if (strcmp(mode, "la") == 0)
        {
            printLS(pwd(), 1, 0);
        }
        else
        {
            printLS(pwd(), 0, 0);
        }
    }
}

// https://stackoverflow.com/questions/13554150/implementing-the-ls-al-command-in-c
// https://github.com/kaustubhhiware/Cshell/blob/master/shell.c
// https://www.le.ac.uk/oerresources/bdra/unix/page_38.htm