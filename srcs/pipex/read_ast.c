#include "minishell.h"

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
    else if (node->type == MINITYPE_OR)
        return (exec_or(node, env));
    else if (node->type == MINITYPE_REDIN
          || node->type == MINITYPE_REDOUT
          || node->type == MINITYPE_REDAPP
          || node->type == MINITYPE_HEREDOC)
        return (exec_redirection(node, env));
    else if (node->type == MINITYPE_SUBSHELL)
        return (exec_subshell(node, env));
    return (1);
}
