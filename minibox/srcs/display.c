/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 17:04:44 by raamayri          #+#    #+#             */
/*   Updated: 2025/09/07 20:49:54 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minibox_internal.h"

static void	ft_display_minibox_asccii(void)
{
	int		fd;
	char	*line;

	fd = open("./txts/ascii_minibox.txt", O_RDONLY);
	if (fd == -1)
	{
		ft_printf("minibox\n");
		return ;
	}
	line = get_next_line(fd);
	while (line)
	{
		ft_printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	ft_printf("\n");
}

void	ft_display_minibox(const t_minibox *minibox)
{
	if (!minibox)
		return ;
	ft_display_minibox_asccii();
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
