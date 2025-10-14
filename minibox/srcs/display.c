/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 17:04:44 by raamayri          #+#    #+#             */
/*   Updated: 2025/10/14 21:30:49 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minibox_internal.h"

static int	ft_open_ascii(void)
{
	char	*path[2];
	int		fd;

	path[0] = getcwd(NULL, 0);
	if (!path[0])
		return (-1);
	path[1] = ft_strjoin(path[0], "/minibox/txts/ascii_minibox.txt");
	if (!path[1])
		return (free(path[0]), -1);
	1 && (fd = open(path[1], O_RDONLY)), free(path[1]);
	if (fd != -1)
		return (free(path[0]), fd);
	path[1] = ft_strjoin(path[0], "/txts/ascii_minibox.txt");
	if (!path[1])
		return (free(path[0]), -1);
	1 && (fd = open(path[1], O_RDONLY)), free(path[1]);
	if (fd != -1)
		return (free(path[0]), fd);
	path[1] = ft_strjoin(path[0], "/ascii_minibox.txt");
	if (!path[1])
		return (free(path[0]), -1);
	1 && (fd = open(path[1], O_RDONLY)), free(path[1]);
	if (fd != -1)
		return (free(path[0]), fd);
	return (free(path[0]), 1);
}

static int	ft_display_minibox_ascii(void)
{
	int		fd;
	char	*line;

	fd = ft_open_ascii();
	if (fd == -1)
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		ft_printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	return (close(fd), ft_printf("\n"), 0);
}

void	ft_display_minibox(const t_minibox *minibox)
{
	if (!minibox)
		return ;
	if (ft_display_minibox_ascii())
		ft_printf("minibox\n");
	ft_printf("├─── input\n");
	if (minibox->input)
		ft_display_minibox_input(minibox->input);
	else
		ft_printf("│    └─── NULL\n");
	ft_printf("├─── lexing\n");
	if (minibox->lexing)
		ft_display_minibox_lexing(minibox->lexing);
	else
		ft_printf("│    └─── NULL\n");
	ft_printf("├─── parsing\n");
	if (minibox->parsing)
		ft_display_minibox_parsing(minibox->parsing);
	else
		ft_printf("│    └─── NULL\n");
	ft_printf("└─── error\n");
	ft_display_minibox_error(minibox->error);
}
