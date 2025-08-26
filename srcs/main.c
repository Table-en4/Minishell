#include "../incs/minishell.h"

int main(int ac, char **av, char **envp)
{
    (void)ac;
    (void)av;
    (void)envp;
    signal(SIGINT, handle_signal);
    printf("%s\n", readline("minishell> "));
}