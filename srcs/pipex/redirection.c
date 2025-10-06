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
		return (perror("dup2"), -1);
	return (close(fd), 0);
}

void	restore_stdio(int stdio_backup[3])
{
	if (stdio_backup[0] != -1)
	{
		dup2(stdio_backup[0], STDIN_FILENO);
		close(stdio_backup[0]);
		stdio_backup[0] = -1;
	}
	if (stdio_backup[1] != -1)
	{
		dup2(stdio_backup[1], STDOUT_FILENO);
		close(stdio_backup[1]);
		stdio_backup[1] = -1;
	}
	if (stdio_backup[2] != -1)
	{
		dup2(stdio_backup[2], STDERR_FILENO);
		close(stdio_backup[2]);
		stdio_backup[2] = -1;
	}
}

static void	init_stdio_backup_redir(int stdio_backup[3])
{
	stdio_backup[0] = -1;
	stdio_backup[1] = -1;
	stdio_backup[2] = -1;
}

int	exec_redirection(t_minibox *minibox, t_miniparsing *node, t_env *env)
{
	int	exit_code;
	int	stdio_backup[3];

	init_stdio_backup_redir(stdio_backup);
	if (!node)
		return (1);
	if (apply_redirections(node->fds, stdio_backup) < 0)
		return (restore_stdio(stdio_backup), 1);
	if (node->left)
		exit_code = execute_ast(minibox, node->left, env);
	else if (node->right)
		exit_code = execute_ast(minibox, node->right, env);
	else
		exit_code = 0;
	return (restore_stdio(stdio_backup), exit_code);
}
