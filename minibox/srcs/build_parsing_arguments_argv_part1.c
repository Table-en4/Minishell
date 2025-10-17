/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_parsing_arguments_argv_part1.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 20:13:42 by raamayri          #+#    #+#             */
/*   Updated: 2025/10/17 18:26:24 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minibox_internal.h"

int		ft_end_argv(t_minibox *minibox, t_miniparsing *node,
			char *temp_arg, size_t *j);
int		ft_build_argv_expand(t_minibox *minibox, t_minilexing **curr_lexing,
			size_t *i, char **tmp_arg);
void	ft_build_argv_seg_3(t_minibox *minibox, t_miniparsing *node,
			size_t *j, char **tmp_arg);

static int	ft_build_argv_seg_2_b(t_minibox *minibox, t_minilexing **curr_lexing,
	size_t *i, char **tmp_arg)
{
	if (!*tmp_arg)
		return (ft_set_minibox_error(minibox, MINICODE_ERRNO), 1);
	(*i)++;
	*curr_lexing = (*curr_lexing)->next;
	return (0);
}

static void	ft_build_argv_seg_2_a(t_minibox *minibox, t_miniparsing *node,
	size_t *j, char **tmp_arg)
{
	if (*tmp_arg && ft_strlen(*tmp_arg) > 0)
	{
		ft_end_argv(minibox, node, *tmp_arg, j);
		*tmp_arg = ft_strdup("");
	}
	else if (*tmp_arg)
	{
		free(*tmp_arg);
		*tmp_arg = ft_strdup("");
	}
}

static int	ft_build_argv_seg_1_b(t_minibox *minibox, t_minilexing **curr_lexing,
	size_t *i, char **tmp_arg)
{
	if (!*tmp_arg)
		return (ft_set_minibox_error(minibox, MINICODE_ERRNO), 1);
	(*i)++;
	*curr_lexing = (*curr_lexing)->next;
	if (*curr_lexing && (*curr_lexing)->token == MINITOKEN_WSPACE)
	{
		(*i)++;
		*curr_lexing = (*curr_lexing)->next;
	}
	return (0);
}

static void	ft_build_argv_seg_1_a(t_minibox *minibox, t_miniparsing *node,
	size_t *j, char **tmp_arg)
{
	if (*tmp_arg && ft_strlen(*tmp_arg) > 0)
	{
		ft_end_argv(minibox, node, *tmp_arg, j);
		*tmp_arg = ft_strdup("");
	}
	else if (*tmp_arg)
	{
		free(*tmp_arg);
		*tmp_arg = ft_strdup("");
	}
}

int	ft_build_parsing_argv(t_minibox *minibox, t_miniparsing *node,
	t_minilexing *lexing, const size_t lexing_len)
{
	t_minilexing	*curr_lexing;
	size_t			ij[2];
	char			*tmp_arg;

	1 && (ij[0] = 0), ij[1] = 0, curr_lexing = lexing, tmp_arg = ft_strdup("");
	if (!tmp_arg)
		return (ft_set_minibox_error(minibox, MINICODE_ERRNO), 0);
	while (curr_lexing && ij[0] < lexing_len && ij[1] < node->argc)
	{
		if (ft_isred(curr_lexing->token))
			ft_build_argv_seg_1_a(minibox, node, &ij[1], &tmp_arg);
		if (ft_isred(curr_lexing->token))
			if (ft_build_argv_seg_1_b(minibox, &curr_lexing, &ij[0], &tmp_arg))
				return (0);
		if (curr_lexing->token == MINITOKEN_WSPACE)
			ft_build_argv_seg_2_a(minibox, node, &ij[1], &tmp_arg);
		if (curr_lexing->token == MINITOKEN_WSPACE)
			if (ft_build_argv_seg_2_b(minibox, &curr_lexing, &ij[0], &tmp_arg))
				return (0);
		if (ft_build_argv_expand(minibox, &curr_lexing, &ij[0], &tmp_arg))
			return (0);
		if (minibox->error.code != MINICODE_NONE)
			return (free(tmp_arg), 0);
	}
	return (ft_build_argv_seg_3(minibox, node, &ij[1], &tmp_arg), 0);
}
