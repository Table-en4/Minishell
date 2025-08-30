#include "minishell.h"

t_env   *creat_env(char *key, char *value)
{
    t_env   *node;

    node = malloc(sizeof(t_env));
    if (!node)
        return (NULL);
    node->key = ft_strdup(key);
    node->value = ft_strdup(value);
    node->next = NULL;
    return (node);
}

void    free_env_node(t_env *node)
{
    if (node)
    {
        free(node->key);
        free(node->value);
        free(node);
    }
}

void    free_env_list(t_env *envp)
{
    t_env   *tmp;

    while (envp)
    {
        tmp = envp->next;
        free_env_node(envp);
        envp = tmp;
    }
}