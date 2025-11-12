/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_parsing_arguments_argv_part2.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 20:13:42 by raamayri          #+#    #+#             */
/*   Updated: 2025/11/12 15:24:31 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minibox_internal.h"

int	ft_end_argv(t_minibox *minibox, t_miniparsing *node,
		char *temp_arg, size_t *j);

void	ft_build_argv_seg_3(t_minibox *minibox, t_miniparsing *node,
	size_t *j, char **tmp_arg)
{
	if (minibox->error.code != MINICODE_NONE)
		return ;
	if (*tmp_arg && ft_strlen(*tmp_arg) > 0 && *j < node->argc)
		ft_end_argv(minibox, node, *tmp_arg, j);
	else if (*tmp_arg)
		free(*tmp_arg);
}

void	ft_build_argv_seg_2_b(t_minibox *minibox, t_minilexing **curr_lexing,
	size_t *i, char **tmp_arg)
{
	if (minibox->error.code != MINICODE_NONE)
		return ;
	if (!*tmp_arg)
		ft_set_minibox_error(minibox, MINICODE_ERRNO);
	if (minibox->error.code != MINICODE_NONE)
		return ;
	(*i)++;
	*curr_lexing = (*curr_lexing)->next;
}

void	ft_build_argv_seg_2_a(t_minibox *minibox, t_miniparsing *node,
	size_t *j, char **tmp_arg)
{
	if (minibox->error.code != MINICODE_NONE)
		return ;
	if (*tmp_arg && ft_strlen(*tmp_arg) > 0)
	{
		ft_end_argv(minibox, node, *tmp_arg, j);
		*tmp_arg = ft_strdup("");
		if (!*tmp_arg)
			ft_set_minibox_error(minibox, MINICODE_ERRNO);
	}
	else if (*tmp_arg)
	{
		free(*tmp_arg);
		*tmp_arg = ft_strdup("");
		if (!*tmp_arg)
			ft_set_minibox_error(minibox, MINICODE_ERRNO);
	}
}

void	ft_build_argv_seg_1_b(t_minibox *minibox, t_minilexing **curr_lexing,
	size_t *i, char **tmp_arg)
{
	if (minibox->error.code != MINICODE_NONE)
		return ;
	if (!*tmp_arg)
		ft_set_minibox_error(minibox, MINICODE_ERRNO);
	if (minibox->error.code != MINICODE_NONE)
		return ;
	(*i)++;
	*curr_lexing = (*curr_lexing)->next;
	if (*curr_lexing && (*curr_lexing)->token == MINITOKEN_WSPACE)
	{
		(*i)++;
		*curr_lexing = (*curr_lexing)->next;
	}
	if (*curr_lexing)
	{
		(*i)++;
		*curr_lexing = (*curr_lexing)->next;
	}
}

void	ft_build_argv_seg_1_a(t_minibox *minibox, t_miniparsing *node,
	size_t *j, char **tmp_arg)
{
	if (minibox->error.code != MINICODE_NONE)
		return ;
	if (*tmp_arg && ft_strlen(*tmp_arg) > 0)
	{
		ft_end_argv(minibox, node, *tmp_arg, j);
		*tmp_arg = ft_strdup("");
		if (!*tmp_arg)
			ft_set_minibox_error(minibox, MINICODE_ERRNO);
	}
	else if (*tmp_arg)
	{
		free(*tmp_arg);
		*tmp_arg = ft_strdup("");
		if (!*tmp_arg)
			ft_set_minibox_error(minibox, MINICODE_ERRNO);
	}
}
