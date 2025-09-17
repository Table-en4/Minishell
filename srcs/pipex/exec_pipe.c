/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:37:57 by molapoug          #+#    #+#             */
/*   Updated: 2025/09/12 14:03:59 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_pipe(t_minibox *minibox, t_miniparsing *node, t_env *env)
{
	int		pipe_fd[2];
	pid_t	left_pid;
	pid_t	right_pid;
	int		status;

	if (pipe(pipe_fd) == -1)
		return (perror("pipe"), 1);
	left_pid = fork();
	if (left_pid == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		exit(execute_ast(minibox, node->left, env));
	}
	right_pid = fork();
	if (right_pid == 0)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		exit(execute_ast(minibox, node->right, env));
	}
	1 && (close(pipe_fd[0]), close(pipe_fd[1]), waitpid(left_pid, &status, 0));
	return (waitpid(right_pid, &status, 0), WEXITSTATUS(status));
}
