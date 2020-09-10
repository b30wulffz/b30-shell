#include "headers.h"
#include "pwd.h"
#include "globals.h"

void init()
{
    setHomeDir(pwd());
    // signal(SIGINT, SIG_IGN); // IGNORE ALL SIGNALS
    // signal(SIGTSTP, SIG_IGN);
    // signal(SIGQUIT, SIG_IGN);
    // signal(SIGTTIN, SIG_IGN);
    // signal(SIGTTOU, SIG_IGN);
    printf("Welcome to B30-Shell\n\n");
}