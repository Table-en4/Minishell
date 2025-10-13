/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 15:30:10 by molapoug          #+#    #+#             */
/*   Updated: 2025/10/10 22:13:55 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	backup_stdio(int stdio_backup[3])
{
	if (stdio_backup[0] != -1)
		return (0);
	stdio_backup[0] = dup(STDIN_FILENO);
	if (stdio_backup[0] == -1)
		return (-1);
	stdio_backup[1] = dup(STDOUT_FILENO);
	if (stdio_backup[1] == -1)
	{
		close(stdio_backup[0]);
		return (-1);
	}
	stdio_backup[2] = dup(STDERR_FILENO);
	if (stdio_backup[2] == -1)
	{
		close(stdio_backup[0]);
		close(stdio_backup[1]);
		return (-1);
	}
	return (0);
}

static void	apply_single_redirection_switch(int *result, t_minifd *current)
{
	if (current->type == MINITYPE_REDIN)
	{
		*result = redirect_input(current->file);
		if (current->fd >= 0)
			close(current->fd);
	}
	else if (current->type == MINITYPE_REDOUT)
	{
		*result = redirect_output(current->file, O_TRUNC);
		if (current->fd >= 0)
			close(current->fd);
	}
	else if (current->type == MINITYPE_REDAPP)
	{
		*result = redirect_output(current->file, O_APPEND);
		if (current->fd >= 0)
			close(current->fd);
	}
	else if (current->type == MINITYPE_HEREDOC)
		*result = redirect_heredoc(current->fd);
}

static int	apply_single_redirection(t_minifd *current)
{
	int	result;

	result = 0;
	apply_single_redirection_switch(&result, current);
	if (result < 0)
		return (-1);
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
