/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_extern.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 15:40:54 by molapoug          #+#    #+#             */
/*   Updated: 2025/10/14 17:52:13 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_child_process(char *cmd_path, char **args, char **envp)
{
	setup_child_signals();
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
	int	sig;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &status, 0);
	restore_exec_signals();
	free(cmd_path);
	free_envp(envp);
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			return (130);
		else if (sig == SIGQUIT)
			return (131);
		return (128 + sig);
	}
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
		return (127);
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
