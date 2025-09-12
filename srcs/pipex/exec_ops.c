#include "minishell.h"

int exec_and_seq(t_minibox *minibox, t_env *env, t_miniparsing *node)
{
    int left_exit;
    int right_exit;

    if (!node)
        return (1);
    if (node->type != MINITYPE_AND)
        return (execute_parsing_node(minibox, env, node));
    left_exit = execute_parsing_node(minibox, env, node->left);
    if (left_exit != 0)
        return (left_exit);
    return (right_exit = exec_and_seq(minibox, env, node->right), right_exit);
}

int exec_or_seq(t_minibox *minibox, t_env *env,t_miniparsing *node)
{
    int left_exit;
    int right_exit;

    if (!node)
        return (1);
    if (node->type != MINITYPE_OR)
        return (execute_parsing_node(minibox, env, node));
    left_exit = execute_parsing_node(minibox, env, node->left);
    if (left_exit == 0)
        return (left_exit);
    return (right_exit = exec_or_seq(minibox, env, node->right), right_exit);
}

int exec_with_seq(t_minibox *minibox, t_env *env,t_miniparsing *node)
{
    if (!node)
        return (1);
    if (node->type == MINITYPE_SUBSHELL)
        return (exec_subshell(minibox, env));
    else if (node->type == MINITYPE_PIPE)
        return (exec_pipe_chain(minibox, env, node));
    else if (node->type == MINITYPE_AND)
        return (exec_and_seq(minibox, env, node));
    else if (node->type == MINITYPE_OR)
        return (exec_or_seq(minibox, env, node));
    else if (node->type == MINITYPE_CMD)
        return (exec_command(minibox, env));
    else
        return (1);
}
