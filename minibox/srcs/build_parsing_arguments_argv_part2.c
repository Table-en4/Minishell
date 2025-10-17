/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_parsing_arguments_argv_part2.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 20:13:42 by raamayri          #+#    #+#             */
/*   Updated: 2025/10/17 18:26:25 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minibox_internal.h"

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

int	ft_build_argv_expand(t_minibox *minibox, t_minilexing **curr_lexing,
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

void	ft_build_argv_seg_3(t_minibox *minibox, t_miniparsing *node,
	size_t *j, char **tmp_arg)
{
	if (*tmp_arg && ft_strlen(*tmp_arg) > 0 && *j < node->argc)
		ft_end_argv(minibox, node, *tmp_arg, j);
	else if (*tmp_arg)
		free(*tmp_arg);
}
