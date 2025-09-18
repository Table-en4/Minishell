/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:38:12 by molapoug          #+#    #+#             */
/*   Updated: 2025/09/18 15:14:41 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_child_process(t_minibox *minibox, t_miniparsing *node,
				t_env *env, int stdio_backup[3])
{
	int	exit_code;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (node->fds && apply_redirections(node->fds, stdio_backup) < 0)
		exit(1);
	exit_code = execute_ast(minibox, node->subshell, env);
	exit(exit_code);
}

static int	handle_parent_process(pid_t pid)
{
	int	status;
	int	exit_code;
	int	sig;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			ft_dprintf(1, "\n");
		exit_code = 128 + sig;
	}
	else
		exit_code = 1;
	return (exit_code);
}

int	exec_subshell(t_minibox *minibox, t_miniparsing *node, t_env *env)
{
	pid_t	pid;
	int		stdio_backup[3];

	if (!node || !node->subshell)
		return (1);
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
