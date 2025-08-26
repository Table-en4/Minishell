#include "../incs/minishell.h"

void    handle_signal(int sig)
{
    printf("%s\n", "A signal detected", sig);
    exit(0);
}