/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 22:35:53 by raamayri          #+#    #+#             */
/*   Updated: 2025/09/08 02:15:05 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minibox_internal.h"

static int	ft_display_depth(const int depth, const int base)
{
	int	cp_base;
	int	i;

	i = 0;
	cp_base = base;
	if (cp_base < 0)
		cp_base = 0;
	while (i < depth)
	{
		if (i % 2 == 0 && i <= cp_base)
			ft_printf("│    ");
		else
			ft_printf("     ");
		i++;
	}
	return (0);
}

static void	ft_display_fds(const t_minifd *fds, const int depth, const int base)
{
	t_minifd	*curr_fd;
	const char	**mininames = ft_get_type_names();
	char		*mininame;
	char		**link;

	if (!fds)
		return ;
	curr_fd = (t_minifd *)fds;
	while (curr_fd)
	{
		link = (char *[2]){"├", "│"};
		if (curr_fd->next == NULL)
			link = (char *[2]){"└", " "};
		mininame = (char *)mininames[curr_fd->type];
		if (curr_fd->prev)
			ft_display_depth(depth, base);
		else
			ft_printf("│    ");
		ft_printf("%s─── type: %s\n", link[0], curr_fd->type);
		ft_display_depth(depth + 1, base);
		ft_printf("%s─── file: [%s]\n", link[1], curr_fd->file);
		ft_display_depth(depth + 1, base);
		ft_printf("%s─── fd: %d\n", link[1], curr_fd->fd);
		curr_fd = curr_fd->next;
	}
}

static void	ft_display_data(const t_miniparsing *parsing,
	const int depth, const int base)
{
	int	i;

	ft_display_depth(depth, base);
	ft_printf("├─── argc: %d\n", parsing->argc);
	i = 0;
	1 && (ft_display_depth(depth, base)), ft_printf("├─── argv: ");
	if (parsing->argv)
	{
		while (i < (int)parsing->argc)
		{
			if (i == 0)
				ft_printf("[");
			ft_printf("[%s]", parsing->argv[i++]);
			if (i == (int)parsing->argc)
				ft_printf("]\n");
		}
	}
	else
		ft_printf("NULL\n");
	1 && (ft_display_depth(depth, base)), ft_printf("├─── fds\n");
	ft_display_depth(depth, base);
	if (parsing->fds)
		ft_display_fds(parsing->fds, depth + 1, base);
	else
		ft_printf("│    └─── NULL\n");
}

static int	ft_display_parsing(const t_miniparsing *parsing,
	const int depth, const int base)
{
	const char	**mininames = ft_get_type_names();
	char		*mininame;

	if (!parsing)
	{
		ft_display_depth(depth - 1, base - 2);
		ft_printf("│    └─── NULL\n");
		return (1);
	}
	mininame = (char *)mininames[parsing->type];
	ft_display_depth(depth, base);
	ft_printf("└─── type: %s\n", mininame);
	ft_display_data(parsing, depth + 1, base);
	ft_display_depth(depth + 1, base);
	ft_printf("├─── subshell\n");
	ft_display_parsing(parsing->subshell, depth + 2, base + 2);
	ft_display_depth(depth + 1, base);
	ft_printf("├─── left\n");
	ft_display_parsing(parsing->left, depth + 2, base + 2);
	ft_display_depth(depth + 1, base);
	ft_printf("└─── right\n");
	if (!parsing->right)
		return (ft_display_depth(depth + 2, base), ft_printf("└─── NULL\n"), 1);
	return (ft_display_parsing(parsing->right, depth + 2, base), 0);
}

void	ft_display_minibox_parsing(const t_miniparsing *parsing)
{
	int	depth;
	int	base;

	if (!parsing)
		return ;
	depth = 1;
	base = 0;
	ft_display_parsing(parsing, depth, base);
}
