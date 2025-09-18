/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_extern.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 15:40:54 by molapoug          #+#    #+#             */
/*   Updated: 2025/09/18 15:16:23 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_child_process(char *cmd_path, char **args, char **envp)
{
	if (execve(cmd_path, args, envp) == -1)
	{
		perror(args[0]);
		free(cmd_path);
		free_envp(envp);
		exit(1);
	}
	return (0);
}

static int	handle_parent_process(pid_t pid, char *cmd_path, char **envp)
{
	int	status;

	waitpid(pid, &status, 0);
	free(cmd_path);
	free_envp(envp);
	return (WEXITSTATUS(status));
}

int	execute_external(char **args, t_env *env_list)
{
	pid_t	pid;
	char	**envp;
	char	*cmd_path;

	if (!args || !args[0])
		return (1);
	envp = conv_env_envp(env_list);
	if (!envp)
		return (1);
	cmd_path = find_path(args[0], env_list);
	if (!cmd_path)
	{
		ft_dprintf(2, "%s: command not found\n", args[0]);
		free_envp(envp);
		return (1);
	}
	pid = fork();
	if (pid == 0)
		handle_child_process(cmd_path, args, envp);
	else if (pid > 0)
		return (handle_parent_process(pid, cmd_path, envp));
	else
		return (perror("fork"), free(cmd_path), free_envp(envp), 1);
	return (0);
}
