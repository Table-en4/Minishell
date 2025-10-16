/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 15:36:21 by molapoug          #+#    #+#             */
/*   Updated: 2025/10/16 16:47:14 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_child_process(char **argv, t_env *env, int stdio_backup[3])
{
	char	*cmd_path;
	char	**envp;

	setup_child_signals();
	if (stdio_backup[0] != -1)
		close(stdio_backup[0]);
	if (stdio_backup[1] != -1)
		close(stdio_backup[1]);
	if (stdio_backup[2] != -1)
		close(stdio_backup[2]);
	if (is_builtin(argv[0]) != -1)
		exit(execute_builtin(argv, &env));
	envp = conv_env_envp(env);
	if (!envp)
		exit(1);
	cmd_path = find_path(argv[0], env);
	if (!cmd_path)
	{
		ft_dprintf(2, "%s: command not found\n", argv[0]);
		(free_envp(envp), exit(127));
	}
	if (execve(cmd_path, argv, envp) == -1)
		(perror(argv[0]), free(cmd_path), free_envp(envp), exit(1));
	return (0);
}

static int	handle_parent_process(pid_t pid)
{
	int	status;
	int	sig;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &status, 0);
	ft_restore_signals();
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
		{
			ft_dprintf(1, "\n");
			return (130);
		}
		else if (sig == SIGQUIT)
		{
			ft_dprintf(1, "Quit\n");
			return (131);
		}
		return (128 + sig);
	}
	return (1);
}

int	run_command(char **argv, t_env *env, int stdio_backup[3])
{
	pid_t	pid;

	if (!argv || !argv[0])
		return (1);
	pid = fork();
	if (pid == 0)
		handle_child_process(argv, env, stdio_backup);
	else if (pid > 0)
		return (handle_parent_process(pid));
	else
		return (perror("fork"), 1);
	return (0);
}
