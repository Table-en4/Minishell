/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 12:22:58 by molapoug          #+#    #+#             */
/*   Updated: 2025/09/17 12:23:15 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_input(char *file)
{
	int	fd;

	if (!file)
		return (-1);
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_dprintf(2, "minishell: %s: ", file);
		perror("");
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	redirect_output(char *file, int flags)
{
	int	fd;

	if (!file)
		return (-1);
	fd = open(file, O_WRONLY | O_CREAT | flags, 0644);
	if (fd == -1)
	{
		ft_dprintf(2, "minishell: %s: ", file);
		perror("");
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}
