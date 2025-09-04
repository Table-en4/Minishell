#include "minishell.h"

int exec_subshell(t_miniparsing *node, t_env *env)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == -1)
        return (1);
    if (pid == 0)
        exit(execute_ast(node->left, env));
    waitpid(pid, &status, 0);
    return (WEXITSTATUS(status));
}
