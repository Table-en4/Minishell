/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:36:47 by molapoug          #+#    #+#             */
/*   Updated: 2025/09/05 10:36:48 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_env_list(t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		ft_dprintf(1, "%s=%s\n", current->key, current->value);
		current = current->next;
	}
}

static int	handle_options(char **args, t_env **env, int *i)
{
	if (ft_strcmp(args[*i], "-i") == 0)
	{
		free_env_list(*env);
		*env = NULL;
	}
	else if (ft_strcmp(args[*i], "-u") == 0)
	{
		(*i)++;
		if (!args[*i])
		{
			ft_dprintf(2, "env: option requires argument -- u\n");
			return (1);
		}
		unset_env(env, args[*i]);
	}
	else if (ft_strchr(args[*i], '='))
	{
		if (export_no_value(env, args[*i]) != 0)
			return (1);
	}
	else
		return (2);
	return (0);
}

static int	process_args(char **args, t_env **env)
{
	int	i;
	int	ret;

	i = 1;
	while (args[i])
	{
		ret = handle_options(args, env, &i);
		if (ret == 1)
			return (-1);
		if (ret == 2)
			break ;
		i++;
	}
	return (i);
}

int	ft_env(char **args, t_env **envp)
{
	t_env	*env;
	int		cmd_index;
	int		result;

	if (!args[1])
	{
		print_env_list(*envp);
		return (0);
	}
	env = duplic_env(*envp);
	cmd_index = process_args(args, &env);
	if (cmd_index == -1)
		return (free_env_list(env), 1);
	if (!args[cmd_index])
	{
		print_env_list(env);
		return (free_env_list(env), 0);
	}
	result = env_exec(&args[cmd_index], env);
	free_env_list(env);
	return (result);
}
