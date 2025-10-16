/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:38:12 by molapoug          #+#    #+#             */
/*   Updated: 2025/10/16 16:47:14 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_child_process(t_minibox *minibox, t_miniparsing *node,
				t_env **env, int stdio_backup[3])
{
	int	exit_code;

	setup_child_signals();
	if (node->fds && apply_redirections(node->fds, stdio_backup) < 0)
	{
		restore_stdio(stdio_backup);
		exit(1);
	}
	exit_code = execute_ast(minibox, node->subshell, env);
	restore_stdio(stdio_backup);
	exit(exit_code);
}

static int	handle_parent_process(pid_t pid)
{
	int	status;
	int	exit_code;
	int	sig;

	(signal(SIGINT, SIG_IGN), signal(SIGQUIT, SIG_IGN));
	(waitpid(pid, &status, 0), ft_restore_signals());
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			1 && ft_dprintf(1, "\n"), exit_code = 130;
		else if (sig == SIGQUIT)
			1 && ft_dprintf(1, "Quit\n"), exit_code = 131;
		else
			exit_code = 128 + sig;
	}
	else
		exit_code = 1;
	return (exit_code);
}

int	exec_subshell(t_minibox *minibox, t_miniparsing *node, t_env **env)
{
	pid_t	pid;
	int		stdio_backup[3];

	if (!node || !node->subshell)
		return (1);
	init_stdio_backup_exec(stdio_backup);
	pid = fork();
	if (pid == 0)
		handle_child_process(minibox, node, env, stdio_backup);
	else if (pid > 0)
		return (handle_parent_process(pid));
	else
	{
		perror("fork");
		return (1);
	}
	return (0);
}
