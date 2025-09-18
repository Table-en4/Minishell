/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 11:45:06 by molapoug          #+#    #+#             */
/*   Updated: 2025/09/18 15:09:45 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (-1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "echo") == 0)
		return (2);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (3);
	if (ft_strcmp(cmd, "unset") == 0)
		return (4);
	if (ft_strcmp(cmd, "env") == 0)
		return (5);
	if (ft_strcmp(cmd, "export") == 0)
		return (6);
	if (ft_strcmp(cmd, "exit") == 0)
		return (7);
	return (-1);
}

int	execute_builtin(char **args, t_env **envp)
{
	int	builtin;

	builtin = is_builtin(args[0]);
	if (builtin == 1)
		return (ft_cd(args, envp));
	else if (builtin == 2)
		return (ft_echo(args));
	else if (builtin == 3)
		return (ft_pwd(args, envp));
	else if (builtin == 4)
		return (ft_unset(args, envp));
	else if (builtin == 5)
		return (ft_env(args, envp));
	else if (builtin == 6)
		return (ft_export(args, envp));
	else if (builtin == 7)
	{
		ft_dprintf(1, "\e[46mfin de l'experience utilisateur\e[0m\n");
		free_args(args);
		free_env_list(*envp);
		exit(0);
	}
	return (-1);
}

char	**conv_env_envp(t_env *env_list)
{
	int		count;
	int		i;
	int		len;
	t_env	*current;
	char	**envp;

	1 && (current = env_list, i = 0, count = 0);
	while (current)
		1 && (count++, current = current->next);
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	current = env_list;
	while (current && i < count)
	{
		len = ft_strlen(current->key) + ft_strlen(current->value) + 2;
		envp[i] = malloc(len);
		if (envp[i])
		{
			1 && (ft_strcpy(envp[i], current->key), ft_strcat(envp[i], "="));
			ft_strcat(envp[i], current->value);
		}
		1 && (current = current->next, i++);
	}
	return (envp[i] = NULL, envp);
}

void	free_envp(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return ;
	while (envp[i])
		free(envp[i++]);
	free(envp);
}
