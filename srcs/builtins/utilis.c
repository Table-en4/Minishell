/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 15:11:43 by molapoug          #+#    #+#             */
/*   Updated: 2025/09/17 15:11:49 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valide_id(char *name)
{
	int	i;

	i = 1;
	if (!name || !name[0])
		return (0);
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (0);
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	env_value(t_env **env, char *arg)
{
	t_blt	*blt;

	blt = NULL;
	blt->pos = ft_strchr(arg, '=');
	if (!blt->pos)
		return (0);
	*(blt->pos) = '\0';
	blt->key = arg;
	blt->value = blt->pos + 1;
	if (!valide_id(blt->key))
	{
		*(blt->pos) = '=';
		return (ft_dprintf(2, "env: '%s': not valid", arg), 1);
	}
	blt->copy = ft_strdup(blt->copy);
	*(blt->pos) = '=';
	set_env_value(env, blt->copy, blt->value);
	return (free(blt->copy), 0);
}

int	unset_env(t_env **envp, char *key)
{
	t_env	*current;
	t_env	*prev;

	if (!envp || !*envp || !key)
		return (1);
	current = *envp;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*envp = current->next;
			free_env_node(current);
			return (1);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}

t_env	*duplic_env(t_env *ori)
{
	t_env	*new;
	t_env	*current;

	new = NULL;
	current = ori;
	while (current)
	{
		set_env_value(&new, current->key, current->value);
		current = current->next;
	}
	return (new);
}

int	env_exec(char **args, t_env *env)
{
	pid_t	pid;
	int		status;
	char	**envp;

	envp = conv_env_envp(env);
	if (!env)
		return (1);
	pid = fork();
	if (pid == 0)
	{
		if (execve(args[0], args, envp) == -1)
		{
			perror(args[0]);
			free_envp(envp);
			exit(127);
		}
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		free_envp(envp);
		return (WEXITSTATUS(status));
	}
	return (0);
}
