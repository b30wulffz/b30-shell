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

char *trim(char *src)
{
    char *dest = (char *)malloc(strlen(src) * sizeof(char));
    if (src != NULL)
    {
        int i = 0, j = strlen(src) - 2;
        // from beginning
        while (src[i] == ' ')
        {
            i++;
        }
        //from end
        while (src[j] == ' ')
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
            if (src[i] == ' ' && flagCodes == 0)
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