#include "headers.h"
#include "generics.h"
#include "globals.h"

#include "init.h"
#include "prompt.h"
#include "shellinput.h"

int main()
{
    int run = 1;

    init();

    char *homeDir = getHomeDir();

    while (run)
    {
        prompt();
        shellInput(homeDir);
    }

    return 0;
}