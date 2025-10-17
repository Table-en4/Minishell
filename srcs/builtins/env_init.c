/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 11:45:17 by molapoug          #+#    #+#             */
/*   Updated: 2025/10/17 18:14:48 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_shlvl(t_env **env_list)
{
	char	*shlvl_str;
	int		shlvl_value;

	shlvl_str = get_env(*env_list, "SHLVL");
	if (shlvl_str)
		shlvl_value = ft_atoi(shlvl_str) + 1;
	else
		shlvl_value = 1;
	shlvl_str = ft_itoa(shlvl_value);
	if (shlvl_str)
	{
		set_env_value(env_list, "SHLVL", shlvl_str);
		free(shlvl_str);
	}
}

t_env	*init_env(char **envp)
{
	t_env	*env_list;
	char	*key;
	char	*value;
	char	*pos;
	int		i;

	env_list = NULL;
	i = 0;
	while (envp[i])
	{
		pos = ft_strchr(envp[i], '=');
		if (pos)
		{
			*pos = '\0';
			key = envp[i];
			value = pos + 1;
			set_env_value(&env_list, key, value);
			*pos = '=';
		}
		i++;
	}
	return (add_shlvl(&env_list), env_list);
}

char	**parse_line(char *line)
{
	char	**args;
	char	*token;
	int		i;

	args = malloc(64 * sizeof(char *));
	if (!args)
		return (NULL);
	i = 0;
	token = ft_strtok(line, " \t\n");
	while (token && i < 63)
	{
		args[i] = ft_strdup(token);
		token = ft_strtok(NULL, " \t\n");
		i++;
	}
	args[i] = NULL;
	return (args);
}

void	free_args(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	while (args[i])
		free(args[i++]);
	free(args);
}
