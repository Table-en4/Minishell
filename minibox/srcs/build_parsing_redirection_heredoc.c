/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_parsing_redirection_heredoc.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 23:03:08 by raamayri          #+#    #+#             */
/*   Updated: 2025/09/15 18:38:37 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minibox_internal.h"

// TODO: HANDLE SIG
static void	ft_write_heredoc(t_minibox *minibox, t_minifd *node)
{
	const char	*eof = node->file;
	char		*line;

	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
			ft_set_minibox_error(minibox, MINICODE_ERRNO);
		if (minibox->error.code != MINICODE_NONE)
			break ;
		if (ft_strcmp(line, eof) == 0)
			break ;
		ft_dprintf(node->fd, "%s\n", line);
		free(line);
		line = NULL;
	}
	if (line)
		free(line);
	if (close(node->fd) == -1)
		ft_set_minibox_error(minibox, MINICODE_ERRNO);
}

static char	*ft_generate_id(t_minibox *minibox, t_minifd *node)
{
	static int	i = 0;
	uintptr_t	ptr_hash;
	int			hash;
	char		*id;

	ptr_hash = ((uintptr_t)node ^ (uintptr_t)(&i)) * (unsigned long)2654435761;
	hash = (int)((ptr_hash ^ i++) % INT_MAX);
	if (hash < 0)
		hash *= -1;
	id = ft_itoa(hash);
	if (!id)
		ft_set_minibox_error(minibox, MINICODE_ERRNO);
	if (minibox->error.code != MINICODE_NONE)
		return (NULL);
	return (id);
}

static char	*ft_generate_file_name(t_minibox *minibox, t_minifd *node)
{
	char		*file_name;
	char		*id;

	while (1)
	{
		id = ft_generate_id(minibox, node);
		if (minibox->error.code != MINICODE_NONE)
			return (NULL);
		1 && (file_name = ft_strjoin(".minibox_heredoc_", id)), free(id);
		if (!file_name)
			ft_set_minibox_error(minibox, MINICODE_ERRNO);
		if (minibox->error.code != MINICODE_NONE)
			return (NULL);
		node->fd = open(file_name, O_WRONLY | O_CREAT | O_EXCL, 0644);
		if (node->fd != -1)
			break ;
		free(file_name);
		if (errno != EEXIST)
			ft_set_minibox_error(minibox, MINICODE_ERRNO);
		if (minibox->error.code != MINICODE_NONE)
			return (NULL);
		errno = 0;
	}
	printf("\n\n\n%s\n\n\n", file_name);
	return (file_name);
}

int	ft_open_heredoc(t_minibox *minibox, t_minifd *node)
{
	int		fd;
	char	*temp_file;

	temp_file = ft_generate_file_name(minibox, node);
	if (minibox->error.code != MINICODE_NONE)
		return (-1);
	ft_write_heredoc(minibox, node);
	if (minibox->error.code != MINICODE_NONE)
	{
		if (unlink(temp_file) == -1)
			ft_set_minibox_error(minibox, MINICODE_ERRNO);
		return (free(temp_file), -1);
	}
	free(node->file);
	node->file = temp_file;
	fd = open(node->file, O_RDONLY);
	if (fd == -1)
		ft_set_minibox_error(minibox, MINICODE_ERRNO);
	if (minibox->error.code != MINICODE_NONE)
	{
		if (unlink(node->file) == -1)
			ft_set_minibox_error(minibox, MINICODE_ERRNO);
		return (-1);
	}
	return (fd);
}
