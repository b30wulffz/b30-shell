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
        fflush(stdin);
        fflush(stdout);
        // sleep(1);
    }

    return 0;
}