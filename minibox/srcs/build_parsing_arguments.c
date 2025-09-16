/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_parsing_arguments.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 20:13:42 by raamayri          #+#    #+#             */
/*   Updated: 2025/09/15 19:02:20 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minibox_internal.h"

static void	ft_set_expended_val(t_minibox *minibox, t_miniparsing *node,
	const t_minilexing *curr_lexing, size_t *j)
{
	char	*expd;
	char	**match;
	size_t	count;
	size_t	i;

	expd = ft_get_expand_val(minibox, curr_lexing);
	if (minibox->error.code != MINICODE_NONE)
		return ;
	if (curr_lexing->token != MINITOKEN_SQUOTE && ft_strchr(expd, 42))
	{
		i = 0;
		count = 0;
		1 && (match = ft_expand_wildcard(minibox, expd, &count)), free(expd);
		if (minibox->error.code != MINICODE_NONE)
			return ;
		while (i < count)
			node->argv[(*j)++] = match[i++];
		free(match);
	}
	else
		node->argv[(*j)++] = expd;
}

void	ft_build_parsing_argv(t_minibox *minibox, t_miniparsing *node,
	const t_minilexing *lexing, const size_t lexing_len)
{
	t_minilexing	*curr_lexing;
	size_t			i;
	size_t			j;

	curr_lexing = (t_minilexing *)lexing;
	1 && (i = 0), j = 0;
	while (curr_lexing && i < lexing_len && j < node->argc)
	{
		if (ft_isred(curr_lexing->token))
		{
			1 && (i++), curr_lexing = curr_lexing->next;
			if (curr_lexing && curr_lexing->token == MINITOKEN_WSPACE)
				1 && (i++), curr_lexing = curr_lexing->next;
		}
		else if (curr_lexing->token != MINITOKEN_WSPACE)
			ft_set_expended_val(minibox, node, curr_lexing, &j);
		if (minibox->error.code != MINICODE_NONE)
			return ;
		1 && (i++), curr_lexing = curr_lexing->next;
	}
}

static size_t	ft_get_expended_len(t_minibox *minibox,
	const t_minilexing *curr_lexing)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*ed;
	int				len;

	1 && (len = 0), ed = ft_get_expand_val(minibox, curr_lexing);
	if (minibox->error.code != MINICODE_NONE)
		return (0);
	if (curr_lexing->token != MINITOKEN_SQUOTE && ft_strchr(ed, 42))
	{
		dir = opendir(".");
		if (!dir)
			return (ft_set_minibox_error(minibox, MINICODE_ERRNO), free(ed), 1);
		entry = readdir(dir);
		while (entry)
		{
			if (!(entry->d_name[0] == 46 && ed[0] != 46)
				&& ft_wildcard_match(ed, entry->d_name))
				len++;
			entry = readdir(dir);
		}
		return (closedir(dir), free(ed), len * (len > 0) + (len == 0));
	}
	return (free(ed), 1);
}

void	ft_build_parsing_argc(t_minibox *minibox, t_miniparsing *node,
	const t_minilexing *lexing, const size_t lexing_len)
{
	t_minilexing	*curr_lexing;
	size_t			i;

	i = 0;
	curr_lexing = (t_minilexing *)lexing;
	while (curr_lexing && i < lexing_len)
	{
		if (ft_isred(curr_lexing->token))
		{
			1 && (i++), curr_lexing = curr_lexing->next;
			if (curr_lexing && curr_lexing->token == MINITOKEN_WSPACE)
				1 && (i++), curr_lexing = curr_lexing->next;
		}
		else if (curr_lexing->token != MINITOKEN_WSPACE)
			node->argc += ft_get_expended_len(minibox, curr_lexing);
		1 && (i++), curr_lexing = curr_lexing->next;
	}
}
