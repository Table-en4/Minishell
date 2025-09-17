/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:36:54 by molapoug          #+#    #+#             */
/*   Updated: 2025/09/05 10:36:55 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_assign(t_env **envp, char *arg)
{
	char	*pos;
	char	*key;
	char	*value;
	char	*copy;

	pos = ft_strchr(arg, '=');
	if (!pos)
		return (0);
	*pos = '\0';
	key = arg;
	value = pos + 1;
	if (!valide_id(key))
	{
		*pos = '=';
		return (ft_dprintf(2, "bad export : '%s': identifier", arg), 1);
	}
	copy = ft_strdup(key);
	*pos = '=';
	set_env_value(envp, copy, value);
	free(copy);
	return (0);
}

// ajouter la gestion d'export sans value
int	export_no_value(t_env **envp, char *arg)
{
	char	*exist;

	if (!valide_id(arg))
		return (ft_dprintf(2, "export: '%s': not valid\n", arg), 1);
	exist = get_env(*envp, arg);
	if (exist)
		return (0);
	else
		return (set_env_value(envp, arg, ""), 0);
	return (0);
}

// ajouter la gestion d'export tout court et modifier
// la fonction execute_builtins dans exec_builtin.c
void	print_export_env(t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		ft_dprintf(1, "\e[31m declare -x\e[0m %s=%s\n", current->key,
			current->value);
		current = current->next;
	}
}

int	process_export_args(char **args, t_env **envp)
{
	int	i;
	int	error_count;

	error_count = 0;
	i = 1;
	while (args[i])
	{
		if (export_no_value(envp, args[i]) != 0)
			error_count++;
		i++;
	}
	return (error_count);
}

int	ft_export(char **args, t_env **envp)
{
	if (!args[1])
	{
		print_export_env(*envp);
		return (0);
	}
	return (process_export_args(args, envp) > 0);
}
