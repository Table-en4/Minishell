/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 21:28:31 by molapoug          #+#    #+#             */
/*   Updated: 2025/09/08 21:28:31 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_heredoc(int fd)
{
	if (fd < 0)
		return (-1);
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		return (-1);
	}
	close(fd);
	return (0);
}
/*
int	apply_redirections(t_minifd *fds, int stdio_backup[3])
{
	t_minifd	*current;

	if (stdio_backup[0] == -1)
	{
		stdio_backup[0] = dup(STDIN_FILENO);
		stdio_backup[1] = dup(STDOUT_FILENO);
		stdio_backup[2] = dup(STDERR_FILENO);
	}
	current = fds;
	while (current)
	{
		if (current->type == MINITYPE_REDIN)
		{
			if (redirect_input(current->file) < 0)
				return (-1);
		}
		else if (current->type == MINITYPE_REDOUT)
		{
			if (redirect_output(current->file, O_TRUNC) < 0)
				return (-1);
		}
		else if (current->type == MINITYPE_REDAPP)
		{
			if (redirect_output(current->file, O_APPEND) < 0)
				return (-1);
		}
		else if (current->type == MINITYPE_HEREDOC)
		{
			if (redirect_heredoc(current->fd) < 0)
				return (-1);
		}
		current = current->next;
	}
	return (0);
}*/

void	restore_stdio(int stdio_backup[3])
{
	if (stdio_backup[0] != -1)
	{
		dup2(stdio_backup[0], STDIN_FILENO);
		close(stdio_backup[0]);
	}
	if (stdio_backup[1] != -1)
	{
		dup2(stdio_backup[1], STDOUT_FILENO);
		close(stdio_backup[1]);
	}
	if (stdio_backup[2] != -1)
	{
		dup2(stdio_backup[2], STDERR_FILENO);
		close(stdio_backup[2]);
	}
}

int	exec_redirection(t_minibox *minibox, t_miniparsing *node, t_env *env)
{
	int	exit_code;
	int	stdio_backup[3];

	stdio_backup[0] = -1;
	stdio_backup[1] = -1;
	stdio_backup[2] = -1;
	if (!node)
		return (1);
	if (apply_redirections(node->fds, stdio_backup) < 0)
		return (1);
	if (node->left)
		exit_code = execute_ast(minibox, node->left, env);
	else if (node->right)
		exit_code = execute_ast(minibox, node->right, env);
	else
		exit_code = 0;
	restore_stdio(stdio_backup);
	return (exit_code);
}
