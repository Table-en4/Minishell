/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 11:45:31 by molapoug          #+#    #+#             */
/*   Updated: 2025/08/30 11:45:32 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *get_env(t_env *envp, char *key)
{
    while (envp)
    {
        if (ft_strcmp(envp->key, key) == 0)
            return (envp->value);
        envp = envp->next;
    }
    return (NULL);
}

void    set_env_value(t_env **envp, char *key, char *value)
{
    t_env   *current;
    t_env   *new_node;

    current = *envp;
    while (current)
    {
        if (ft_strcmp(current->key, key) == 0)
        {
            free(current->value);
            current->value = ft_strdup(value);
            return ;
        }
        current = current->next;
    }
    new_node = malloc(sizeof(t_env));
    if (!new_node)
        return ;
    new_node->key = ft_strdup(key);
    new_node->value = ft_strdup(value);
    new_node->next = *envp;
    *envp = new_node;
}

char    *get_home(t_env *envp)
{
    return (get_env(envp, "HOME"));
}

char    *get_oldpwd(t_env *envp)
{
    return (get_env(envp, "OLDPWD"));
}
