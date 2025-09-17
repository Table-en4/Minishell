/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 15:36:21 by molapoug          #+#    #+#             */
/*   Updated: 2025/09/17 15:36:22 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_child_process(char **argv, t_env *env)
{
	char	*cmd_path;
	char	**envp;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (is_builtin(argv[0]) != -1)
		exit(execute_builtin(argv, &env));
	envp = conv_env_envp(env);
	if (!envp)
		exit(1);
	cmd_path = find_path(argv[0], env);
	if (!cmd_path)
	{
		ft_dprintf(2, "%s: command not found\n", argv[0]);
		free_envp(envp);
		exit(127);
	}
	if (execve(cmd_path, argv, envp) == -1)
	{
		perror(argv[0]);
		free(cmd_path);
		free_envp(envp);
		exit(126);
	}
	return (0);
}

static int	handle_parent_process(pid_t pid)
{
	int	status;
	int	sig;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			ft_dprintf(1, "\n");
		return (128 + sig);
	}
	return (1);
}

int	run_command(char **argv, t_env *env)
{
	pid_t	pid;

	if (!argv || !argv[0])
		return (1);
	pid = fork();
	if (pid == 0)
		handle_child_process(argv, env);
	else if (pid > 0)
		return (handle_parent_process(pid));
	else
	{
		perror("fork");
		return (1);
	}
	return (0);
}
