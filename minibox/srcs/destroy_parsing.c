/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 17:35:31 by raamayri          #+#    #+#             */
/*   Updated: 2025/09/07 20:56:01 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minibox_internal.h"

static void	ft_destroy_argv(char **argv)
{
	size_t	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
		free(argv[i++]);
	free(argv);
}

static void	ft_destroy_fds(t_minifd *minifd)
{
	t_minifd	*curr_fd;
	t_minifd	*next_fd;

	if (!minifd)
		return ;
	while (minifd->prev)
		minifd = minifd->prev;
	curr_fd = minifd;
	while (curr_fd)
	{
		next_fd = curr_fd->next;
		if (curr_fd->file)
			free(curr_fd->file);
		if (curr_fd->fd >= 0)
			close(curr_fd->fd);
		free(curr_fd);
		curr_fd = next_fd;
	}
}

void	ft_destroy_parsing(t_miniparsing *parsing)
{
	if (!parsing)
		return ;
	if (parsing->subshell)
		ft_destroy_parsing(parsing->subshell);
	if (parsing->left)
		ft_destroy_parsing(parsing->left);
	if (parsing->right)
		ft_destroy_parsing(parsing->right);
	if (parsing->argv)
		ft_destroy_argv(parsing->argv);
	if (parsing->fds)
		ft_destroy_fds(parsing->fds);
	free(parsing);
}

void	ft_destroy_minibox_parsing(t_minibox *minibox, t_miniparsing *parsing)
{
	if (!minibox || !minibox->parsing || !parsing)
		return ;
	ft_destroy_parsing(parsing);
	minibox->parsing = NULL;
}
