#include "generics.h"
#include "headers.h"

char *getHostName()
{
    struct utsname *uBuf;
    uBuf = (struct utsname *)malloc(sizeof(struct utsname));
    uname(uBuf);
    return uBuf->nodename;
}

char *getCurrentUser()
{
    struct passwd *pw;
    pw = getpwuid(geteuid());
    return pw->pw_name;
}

char *trim(char *src, int endline)
{
    char *dest = (char *)malloc(strlen(src) * sizeof(char));
    if (src != NULL)
    {
        int i = 0, j;
        if (endline == 1)
        {
            j = strlen(src) - 2;
        }
        else
        {
            j = strlen(src) - 1;
        }
        // from beginning
        while (src[i] == ' ' || src[i] == '\t')
        {
            i++;
        }
        //from end
        while (src[j] == ' ' || src[j] == '\t')
        {
            j--;
        }
        int ind = 0, flag = 0, flagCodes = 0;

        while (i <= j)
        {
            if (src[i] == '"' || src[i] == '\'')
            {
                if (flagCodes == 0)
                {
                    flagCodes = 1;
                }
                else
                {
                    flagCodes = 0;
                }
            }
            if ((src[i] == ' ' || src[i] == '\t') && flagCodes == 0)
            {
                flag = 1;
            }
            else
            {
                if (flag == 1)
                {
                    dest[ind] = ' ';
                    flag = 0;
                    ind++;
                }
                dest[ind] = src[i];
                ind++;
            }
            i++;
        }
        // dest[ind] = '\n';
        // ind++;
        dest[ind] = '\0';
    }
    return dest;
}

char *concat(char *str1, char *str2)
{
    char *result = (char *)malloc(sizeof(char) * (strlen(str1) + strlen(str2) + 1));
    char ind = 0;
    for (int i = 0; i < strlen(str1); i++)
    {
        result[ind] = str1[i];
        ind++;
    }
    for (int i = 0; i < strlen(str2); i++)
    {
        result[ind] = str2[i];
        ind++;
    }
    result[ind] = '\0';
    return result;
}

char *substr(char *str, int start, int end)
{
    if (start < 0)
    {
        start = 0;
    }
    if (end > strlen(str))
    {
        end = strlen(str);
    }
    if (start <= end)
    {
        char *result = (char *)malloc(sizeof(char) * (end - start + 1));
        int ind = 0;
        for (int i = start; i < end; i++)
        {
            result[ind] = str[i];
            ind++;
        }
        result[ind] = '\0';
        return result;
    }
    else
    {
        return NULL;
    }
}

char *getBaseName(char src[], char *dest)
{
    int len = strlen(src);
    if (src[len - 1] == '/')
    {
        len--;
    }
    int ind = len - 1;
    while (ind >= 0)
    {
        if (src[ind] == '/')
        {
            break;
        }
        ind--;
    }
    ind++;
    int size = len - ind;
    if (size > 0)
    {
        dest = (char *)malloc(sizeof(char) * size);
        int i = 0;
        while (ind < len)
        {
            dest[i] = src[ind];
            ind++;
            i++;
        }
    }
    else
    {
        dest = (char *)malloc(sizeof(char) * 1);
        dest[0] = '/';
    }
    return dest;
}

char *rootPathResolve(char *originalPath, char *homeDir)
{
    char *resolvedPath;
    int flag = 0;
    if (strlen(originalPath) >= strlen(homeDir))
    {
        for (int i = 0; i < strlen(homeDir); i++)
        {
            if (homeDir[i] != originalPath[i])
            {
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            resolvedPath = (char *)malloc(sizeof(char) * (strlen(originalPath) - strlen(homeDir) + 2));
            int i;
            resolvedPath[0] = '~';
            for (i = 1; i < strlen(originalPath) - strlen(homeDir) + 1; i++)
            {
                resolvedPath[i] = originalPath[strlen(homeDir) + i - 1];
            }
            resolvedPath[i] = '\0';
        }
    }
    else
    {
        resolvedPath = originalPath;
    }
    return resolvedPath;
}

int split(char *string, char delimiter, char **dest, int buffsize)
{
    int arrInd = 0;
    if (string != NULL)
    {
        char *partition = (char *)malloc(buffsize * sizeof(char));

        int i = 0, j = strlen(string) - 1;

        int ind = 0, flag = 0, flagCodes = 0, loop = 0;

        // printf("%s\n", string);

        while (i <= j)
        {
            loop = 1;
            if (string[i] == '"' || string[i] == '\'')
            {
                if (flagCodes == 0)
                {
                    flagCodes = 1;
                }
                else
                {
                    flagCodes = 0;
                }
            }
            if ((string[i] == delimiter) && flagCodes == 0)
            {
                flag = 1;
            }
            else
            {
                if (flag == 1)
                {
                    partition[ind] = '\0';
                    dest[arrInd] = partition;
                    partition = (char *)malloc(1024 * sizeof(char));
                    flag = 0;
                    ind = 0;
                    arrInd++;
                }
                partition[ind] = string[i];
                ind++;
                // printf("%c %d\n", string[i], ind);
            }
            i++;
        }
        if (loop == 1)
        {
            partition[ind] = '\0';
            dest[arrInd] = partition;
            arrInd++;
        }
    }
    return arrInd;
}