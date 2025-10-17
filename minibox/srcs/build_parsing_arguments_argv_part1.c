/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_parsing_arguments_argv_part1.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 20:13:42 by raamayri          #+#    #+#             */
/*   Updated: 2025/10/17 20:22:56 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minibox_internal.h"

void	ft_build_argv_seg_3(t_minibox *minibox, t_miniparsing *node,
			size_t *j, char **tmp_arg);
void	ft_build_argv_seg_2_b(t_minibox *minibox, t_minilexing **curr_lexing,
			size_t *i, char **tmp_arg);
void	ft_build_argv_seg_2_a(t_minibox *minibox, t_miniparsing *node,
			size_t *j, char **tmp_arg);
void	ft_build_argv_seg_1_b(t_minibox *minibox, t_minilexing **curr_lexing,
			size_t *i, char **tmp_arg);
void	ft_build_argv_seg_1_a(t_minibox *minibox, t_miniparsing *node,
			size_t *j, char **tmp_arg);

int	ft_end_argv(t_minibox *minibox, t_miniparsing *node,
	char *temp_arg, size_t *j)
{
	char	**match;
	size_t	count;
	size_t	i;

	if (ft_strchr(temp_arg, 42))
	{
		i = 0;
		count = 0;
		match = ft_expand_wildcard(minibox, temp_arg, &count);
		free(temp_arg);
		if (minibox->error.code != MINICODE_NONE)
			return (-1);
		while (i < count && *j < node->argc)
			node->argv[(*j)++] = match[i++];
		free(match);
	}
	else
		node->argv[(*j)++] = temp_arg;
	return (0);
}

static int	ft_build_argv_expand(t_minibox *minibox, t_minilexing **curr_lexing,
	size_t *i, char **tmp_arg)
{
	char	*old_tmp;
	char	*exp_val;

	exp_val = ft_get_expand_val(minibox, *curr_lexing);
	if (minibox->error.code != MINICODE_NONE)
		return (1);
	1 && (old_tmp = *tmp_arg), *tmp_arg = ft_strjoin(old_tmp, exp_val);
	(free(old_tmp), free(exp_val));
	if (!*tmp_arg)
		return (ft_set_minibox_error(minibox, MINICODE_ERRNO), 1);
	1 && (*i)++, *curr_lexing = (*curr_lexing)->next;
	return (0);
}

static int	ft_build_parsing_argv_init(t_minibox *minibox, t_minilexing *lexing,
	size_t *ij, t_minilexing **curr_lexing, char **tmp_arg)
{
	ij[0] = 0;
	ij[1] = 0;
	*curr_lexing = lexing;
	*tmp_arg = ft_strdup("");
	if (!*tmp_arg)
		return (ft_set_minibox_error(minibox, MINICODE_ERRNO), 1);
	return (0);
}

int	ft_build_parsing_argv(t_minibox *minibox, t_miniparsing *node,
	t_minilexing *lexing, const size_t lexing_len)
{
	t_minilexing	*curr_lexing;
	char			*tmp_arg;
	size_t			ij[2];

	if (ft_build_parsing_argv_init(minibox, lexing, ij, &curr_lexing, &tmp_arg))
		return (0);
	while (curr_lexing && ij[0] < lexing_len && ij[1] < node->argc)
	{
		if (ft_isred(curr_lexing->token))
		{
			ft_build_argv_seg_1_a(minibox, node, &ij[1], &tmp_arg);
			ft_build_argv_seg_1_b(minibox, &curr_lexing, &ij[0], &tmp_arg);
		}
		else if (curr_lexing->token == MINITOKEN_WSPACE)
		{
			ft_build_argv_seg_2_a(minibox, node, &ij[1], &tmp_arg);
			ft_build_argv_seg_2_b(minibox, &curr_lexing, &ij[0], &tmp_arg);
		}
		else if (ft_build_argv_expand(minibox, &curr_lexing, &ij[0], &tmp_arg))
				return (0);
		if (minibox->error.code != MINICODE_NONE)
			return (free(tmp_arg), 0);
	}
	return (ft_build_argv_seg_3(minibox, node, &ij[1], &tmp_arg), 0);
}
