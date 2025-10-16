/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:37:57 by molapoug          #+#    #+#             */
/*   Updated: 2025/10/16 16:47:14 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static pid_t	exec_pipe_second_pid(int pipe_fd[2], t_minibox *minibox,
	t_miniparsing *node, t_env **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		setup_child_signals();
		(close(pipe_fd[1]), dup2(pipe_fd[0], STDIN_FILENO), close(pipe_fd[0]));
		exit(execute_ast(minibox, node->right, env));
	}
	return (pid);
}

static pid_t	exec_pipe_first_pid(int pipe_fd[2], t_minibox *minibox,
	t_miniparsing *node, t_env **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		setup_child_signals();
		(close(pipe_fd[0]), dup2(pipe_fd[1], STDOUT_FILENO), close(pipe_fd[1]));
		exit(execute_ast(minibox, node->left, env));
	}
	return (pid);
}

int	exec_pipe(t_minibox *minibox, t_miniparsing *node, t_env **env)
{
	int		pipe_fd[2];
	pid_t	pid[2];
	int		left_status;
	int		right_status;

	if (pipe(pipe_fd) == -1)
		return (perror("pipe"), 1);
	pid[0] = exec_pipe_first_pid(pipe_fd, minibox, node, env);
	if (pid[0] < 0)
		return (close(pipe_fd[0]), close(pipe_fd[1]), perror("fork"), 1);
	pid[1] = exec_pipe_second_pid(pipe_fd, minibox, node, env);
	if (pid[1] < 0)
		return (close(pipe_fd[0]), close(pipe_fd[1]), perror("fork"), 1);
	(close(pipe_fd[0]), close(pipe_fd[1]));
	(signal(SIGINT, SIG_IGN), signal(SIGQUIT, SIG_IGN));
	(waitpid(pid[0], &left_status, 0), waitpid(pid[1], &right_status, 0));
	ft_restore_signals();
	if (WIFSIGNALED(right_status))
		return (128 + WTERMSIG(right_status));
	return (WEXITSTATUS(right_status));
}
