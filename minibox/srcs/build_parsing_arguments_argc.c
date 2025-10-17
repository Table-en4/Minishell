/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_parsing_arguments_argc.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 20:13:42 by raamayri          #+#    #+#             */
/*   Updated: 2025/10/17 20:24:27 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minibox_internal.h"

static size_t	ft_count_wildcard_matches(t_minibox *minibox,
	const char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	size_t			count;

	if (!ft_strchr(pattern, 42))
		return (1);
	count = 0;
	dir = opendir(".");
	if (!dir)
		return (ft_set_minibox_error(minibox, MINICODE_ERRNO), 1);
	entry = readdir(dir);
	while (entry)
	{
		if (!(entry->d_name[0] == 46 && pattern[0] != 46)
			&& ft_wildcard_match(pattern, entry->d_name))
			count++;
		entry = readdir(dir);
	}
	closedir(dir);
	if (count > 0)
		return (count);
	return (1);
}

static size_t	ft_count_argument_parts(t_minibox *minibox,
	const t_minilexing *lexing, const size_t lexing_len)
{
	t_minilexing	*curr_lex;
	size_t			i;
	char			*strs[2];
	char			*expanded_val;
	size_t			r;

	1 && (strs[0] = ft_strdup("")), curr_lex = (t_minilexing *)lexing, i = 0;
	if (!strs[0])
		return (ft_set_minibox_error(minibox, MINICODE_ERRNO), 0);
	while (curr_lex && i < lexing_len)
	{
		if (ft_isred(curr_lex->token) || curr_lex->token == MINITOKEN_WSPACE)
			break ;
		expanded_val = ft_get_expand_val(minibox, curr_lex);
		if (minibox->error.code != MINICODE_NONE)
			return (free(strs[0]), 0);
		1 && (strs[1] = strs[0]), strs[0] = ft_strjoin(strs[1], expanded_val);
		(free(strs[1]), free(expanded_val));
		if (!strs[0])
			return (ft_set_minibox_error(minibox, MINICODE_ERRNO), 0);
		1 && (i++), curr_lex = curr_lex->next;
	}
	return (r = ft_count_wildcard_matches(minibox, strs[0]), free(strs[0]), r);
}

static void	ft_skip_redirections(t_minilexing **curr_lexing, size_t *i)
{
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

void	ft_build_parsing_argc(t_minibox *minibox, t_miniparsing *node,
	const t_minilexing *lexing, const size_t lexing_len)
{
	t_minilexing	*curr_lexing;
	size_t			i;

	1 && (i = 0), curr_lexing = (t_minilexing *)lexing;
	while (curr_lexing && i < lexing_len)
	{
		if (ft_isred(curr_lexing->token))
			ft_skip_redirections(&curr_lexing, &i);
		else if (curr_lexing->token != MINITOKEN_WSPACE)
		{
			node->argc += ft_count_argument_parts(minibox, curr_lexing,
					lexing_len - i);
			if (minibox->error.code != MINICODE_NONE)
				return ;
			while (curr_lexing && !ft_isred(curr_lexing->token)
				&& curr_lexing->token != MINITOKEN_WSPACE && i < lexing_len)
				1 && (i++), curr_lexing = curr_lexing->next;
		}
		else
			1 && (i++), curr_lexing = curr_lexing->next;
	}
}
