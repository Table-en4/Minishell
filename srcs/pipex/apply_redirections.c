/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 15:30:10 by molapoug          #+#    #+#             */
/*   Updated: 2025/09/17 15:30:12 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	backup_stdio(int stdio_backup[3])
{
	if (stdio_backup[0] != -1)
		return (0);
	stdio_backup[0] = dup(STDIN_FILENO);
	if (stdio_backup[0])
		return (-1);
	stdio_backup[1] = dup(STDOUT_FILENO);
	if (stdio_backup[1])
	{
		close(stdio_backup[0]);
		return (-1);
	}
	stdio_backup[2] = dup(STDERR_FILENO);
	if (stdio_backup[2])
	{
		close(stdio_backup[0]);
		close(stdio_backup[1]);
		return (-1);
	}
	return (0);
}

static int	apply_single_redirection(t_minifd *current)
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
	return (0);
}

int	apply_redirections(t_minifd *fds, int stdio_backup[3])
{
	t_minifd	*current;

	if (backup_stdio(stdio_backup) < 0)
		return (-1);
	current = fds;
	while (current)
	{
		if (apply_single_redirection(current) < 0)
			return (-1);
		current = current->next;
	}
	return (0);
}
