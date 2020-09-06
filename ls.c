#include "headers.h"
#include "pwd.h"

void printLS(char *name, int flag_a, int flag_l)
{
    DIR *dir = opendir(name);
    struct dirent *file;
    struct stat fileStat;

    while ((file = readdir(dir)) != NULL)
    {
        char *buf = (char *)malloc(sizeof(char) * 1024);
        sprintf(buf, "%s/%s", pwd(), file->d_name);
        stat(buf, &fileStat);

        printf("%16ld %16s \n", fileStat.st_size, file->d_name);
    }
}

int ls(char *data)
{
    if (data != NULL)
    {
        char *tmpData;
        if (data != NULL)
        {
            tmpData = (char *)malloc(strlen(data) * sizeof(char));
            strcpy(tmpData, data);
        }
        char *word = strtok(data, " ");

        int flag_a, flag_l;
        flag_a = flag_l = 0;

        int count = 0;

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

        if (tmpData != NULL)
        {
            word = strtok(tmpData, " ");
            while (word != NULL)
            {
                if (word[0] != '-')
                {
                    if (count > 1)
                    {
                        printf("%s:\n", word);
                    }
                    // printLS(word, flag_a, flag_l);
                    printf("\n");
                }
                word = strtok(NULL, " ");
            }
        }
        else
        {
            // printLS(pwd(), flag_a, flag_l);
        }
    }
    else
    {
        printLS(pwd(), 0, 0);
    }
}

// https://stackoverflow.com/questions/13554150/implementing-the-ls-al-command-in-c