#include "minishell.h"
#include "minibox.h"

int execute_ast(t_miniparsing *node, t_env *env)
{
    if (!node)
        return (1);
    if (node->type == MINITYPE_CMD)
        return (exec_command(node, env));
    else if (node->type == MINITYPE_PIPE)
        return (exec_pipe(node, STDIN_FILENO, env));
    else if (node->type == MINITYPE_AND)
        return (exec_and(node, env));
}