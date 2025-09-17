/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:37:11 by molapoug          #+#    #+#             */
/*   Updated: 2025/09/05 10:53:32 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valide_unset(char *name)
{
	int	i;

	if (!name || !name[0])
		return (0);
	i = 0;
	while (name[i])
	{
		if (name[i] == '=' || name[i] == '-')
			return (0);
		i++;
	}
	return (valide_id(name));
}

static int	handle_option(char **args, int *i, t_env **envp, int *error_count)
{
	if (ft_strcmp(args[*i], "-v") == 0)
	{
		(*i)++;
		if (!args[*i])
		{
			ft_dprintf(2, "unset: -v option requires an argument\n");
			return ((*error_count)++, 0);
		}
		unset_env(envp, args[*i]);
		(*i)++;
	}
	else if (ft_strcmp(args[*i], "-f") == 0)
	{
		ft_dprintf(2, "unset: -f option not supported\n");
		(*error_count)++;
		(*i)++;
	}
	else if (ft_strcmp(args[*i], "--") == 0)
		(*i)++;
	else
	{
		ft_dprintf(2, "unset: '%s' invalid option\n", args[*i]);
		return (ft_dprintf(2, "unset: usage: unset [-v] [name]\n"), 1);
	}
	return (0);
}

static int	process_argument(char *arg, t_env **envp, int *error_count)
{
	if (!is_valide_unset(arg))
	{
		ft_dprintf(2, "unset: '%s' invalid id\n", arg);
		(*error_count)++;
		return (0);
	}
	if (ft_strcmp(arg, "PWD") == 0 || ft_strcmp(arg, "OLDPWD") == 0
		|| ft_strcmp(arg, "PATH") == 0)
		ft_dprintf(2, "unset: warning: unsetting '%s'\n", arg);
	unset_env(envp, arg);
	return (0);
}

int	ft_unset(char **args, t_env **envp)
{
	int	i;
	int	error_count;
	int	ret;

	if (!args[1])
		return (0);
	error_count = 0;
	i = 1;
	while (args[i])
	{
		if (args[i][0] == '-' && args[i][1] != '\0')
		{
			ret = handle_option(args, &i, envp, &error_count);
			if (ret != 0)
				return (ret);
		}
		else
		{
			process_argument(args[i], envp, &error_count);
			i++;
		}
	}
	return (error_count > 0);
}
