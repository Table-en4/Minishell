/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 11:45:31 by molapoug          #+#    #+#             */
/*   Updated: 2025/10/14 21:44:39 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(t_env *envp, char *key)
{
	while (envp)
	{
		if (ft_strcmp(envp->key, key) == 0)
			return (envp->value);
		envp = envp->next;
	}
	return (NULL);
}

int	set_env_value(t_env **envp, char *key, char *value)
{
	t_env	*curr;
	t_env	*new_node;

	curr = *envp;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
			return (free(curr->value), (curr->value = ft_strdup(value)), 0);
		curr = curr->next;
	}
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (0);
	new_node->key = ft_strdup(key);
	if (!new_node->key)
		return (free(new_node), 0);
	new_node->value = ft_strdup(value);
	if (!new_node->value)
		return (free(new_node->key), free(new_node), 0);
	new_node->next = *envp;
	*envp = new_node;
	return (0);
}

char	*get_home(t_env *envp)
{
	return (get_env(envp, "HOME"));
}

char	*get_oldpwd(t_env *envp)
{
	return (get_env(envp, "OLDPWD"));
}
