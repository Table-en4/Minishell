#include "minishell.h"
#include "minibox.h"

int exec_and(t_miniparsing *node, t_env *env)
{
    int left_exit;

    left_exit = execute_ast(node->left, env);
    if (left_exit == 0)
        return (execute_ast(node->right, env));
    return (left_exit);
}