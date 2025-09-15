/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 22:35:53 by raamayri          #+#    #+#             */
/*   Updated: 2025/09/15 21:35:12 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minibox_internal.h"

static int	ft_print_depth(const int depth, const int base[MINITREE_MAX_DEPTH])
{
	int	i;

	i = 0;
	while (i < depth)
	{
		if (base[i])
			ft_printf("│    ");
		else
			ft_printf("     ");
		i++;
	}
	return (0);
}

static void	ft_display_fds(const t_minifd *fds,
	const int depth, int base[MINITREE_MAX_DEPTH])
{
	t_minifd	*curr_fd;
	const char	**mininames = ft_get_type_names();
	char		*mininame;
	char		**link;

	if (!fds)
	{
		1 && ft_print_depth(depth, base), ft_printf("└─── NULL\n");
		return ;
	}
	curr_fd = (t_minifd *)fds;
	while (curr_fd)
	{
		link = (char *[2]){"├", "│"};
		if (curr_fd->next == NULL)
			link = (char *[2]){"└", " "};
		mininame = (char *)mininames[curr_fd->type];
		ft_print_depth(depth, base);
		ft_printf("%s─── type: %s\n", link[0], mininame);
		ft_print_depth(depth, base);
		ft_printf("%s    ├─── file: [%s]\n", link[1], curr_fd->file);
		ft_print_depth(depth, base);
		ft_printf("%s    └─── fd: %d\n", link[1], curr_fd->fd);
		curr_fd = curr_fd->next;
	}
}

static void	ft_display_data(const t_miniparsing *node,
	const int depth, int base[MINITREE_MAX_DEPTH])
{
	int	i;

	1 && ft_print_depth(depth, base), ft_printf("├─── argc: %d\n", node->argc);
	1 && ft_print_depth(depth, base), ft_printf("├─── argv: ");
	if (!node->argv)
		ft_printf("NULL\n");
	else
	{
		i = 0;
		ft_printf("[");
		while (i < (int)node->argc)
			ft_printf("[%s]", node->argv[i++]);
		ft_printf("]\n");
	}
	1 && (ft_print_depth(depth, base)), ft_printf("├─── fds\n");
	ft_display_fds(node->fds, depth + 1, base);
}

static void	ft_display_parsing(const t_miniparsing *parsing,
	const int depth, int base[MINITREE_MAX_DEPTH])
{
	const char	**mininames = ft_get_type_names();
	char		*mininame;

	if (!parsing || depth > MINITREE_MAX_DEPTH)
	{
		ft_print_depth(depth, base);
		if (!parsing)
			ft_printf("└─── NULL\n");
		else
			ft_printf("└─── ...minihell goes deeper.\n");
		return ;
	}
	mininame = (char *)mininames[parsing->type];
	base[depth + 1] = 1;
	1 && ft_print_depth(depth, base), ft_printf("└─── type: %s\n", mininame);
	ft_display_data(parsing, depth + 1, base);
	1 && ft_print_depth(depth + 1, base), ft_printf("├─── subshell\n");
	ft_display_parsing(parsing->subshell, depth + 2, base);
	1 && ft_print_depth(depth + 1, base), ft_printf("├─── left\n");
	ft_display_parsing(parsing->left, depth + 2, base);
	base[depth + 1] = 0;
	1 && ft_print_depth(depth + 1, base), ft_printf("└─── right\n");
	ft_display_parsing(parsing->right, depth + 2, base);
}

void	ft_display_minibox_parsing(const t_miniparsing *parsing)
{
	int		depth;
	int		base[MINITREE_MAX_DEPTH];
	size_t	i;

	if (!parsing)
		return ;
	depth = 1;
	i = 0;
	base[i++] = 1;
	while (i < MINITREE_MAX_DEPTH)
		base[i++] = 0;
	ft_display_parsing(parsing, depth, base);
}
