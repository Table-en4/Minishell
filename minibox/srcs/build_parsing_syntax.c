/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_parsing_syntax.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 20:42:46 by raamayri          #+#    #+#             */
/*   Updated: 2025/09/14 18:36:45 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minibox_internal.h"

static size_t	ft_check_syntax_red(t_minibox *minibox, t_minilexing **lexing)
{
	t_minilexing	*curr_lexing;
	size_t			i;

	i = 1;
	curr_lexing = (*lexing)->next;
	if (curr_lexing && curr_lexing->token == MINITOKEN_WSPACE)
		1 && (i++), curr_lexing = curr_lexing->next;
	if (!curr_lexing || \
		(curr_lexing->token != MINITOKEN_UQUOTE && \
		curr_lexing->token != MINITOKEN_SQUOTE && \
		curr_lexing->token != MINITOKEN_DQUOTE))
		ft_set_minibox_error(minibox, MINICODE_REDIRECTION_LOST);
	if (minibox->error.code != MINICODE_NONE)
		return (i);
	*lexing = curr_lexing;
	return (i);
}

size_t	ft_skip_subshell(t_minibox *minibox, t_minilexing **lexing,
	const size_t lexing_len)
{
	t_minilexing	*curr_lexing;
	size_t			i;

	i = 1;
	curr_lexing = (*lexing)->next;
	while (curr_lexing && curr_lexing->token != MINITOKEN_RPAREN && \
		i < lexing_len)
	{
		if (curr_lexing->token == MINITOKEN_LPAREN)
			i += ft_skip_subshell(minibox, &curr_lexing, lexing_len - i);
		if (minibox->error.code != MINICODE_NONE)
			return (i);
		i++;
		curr_lexing = curr_lexing->next;
	}
	if (i == 1)
		ft_set_minibox_error(minibox, MINICODE_SUBSHELL_EMPTY);
	if (minibox->error.code != MINICODE_NONE)
		return (i);
	*lexing = curr_lexing;
	return (i);
}

void	ft_check_syntax_cmd(t_minibox *minibox, const t_minilexing *lexing,
	const size_t lexing_len)
{
	t_minilexing	*curr_lexing;
	size_t			i;

	i = 0;
	curr_lexing = (t_minilexing *)lexing;
	while (curr_lexing && i++ < lexing_len)
	{
		if (curr_lexing->token == MINITOKEN_LPAREN || \
			curr_lexing->token == MINITOKEN_RPAREN)
			ft_set_minibox_error(minibox, MINICODE_PROCESSORS_COLLISION);
		else if (ft_isred(curr_lexing->token))
		{
			i += ft_check_syntax_red(minibox, &curr_lexing);
			if (minibox->error.code != MINICODE_NONE)
				return ;
		}
		curr_lexing = curr_lexing->next;
	}
}

void	ft_check_syntax_ss(t_minibox *minibox, const t_minilexing *lexing,
	const size_t lexing_len)
{
	t_minilexing	*curr_lexing;
	size_t			subshell_count;
	size_t			i;

	i = 0;
	subshell_count = 0;
	curr_lexing = (t_minilexing *)lexing;
	while (curr_lexing && i < lexing_len)
	{
		if (curr_lexing->token == MINITOKEN_LPAREN && ++subshell_count > 1)
			ft_set_minibox_error(minibox, MINICODE_PARENT_OVERLOAD);
		if (curr_lexing->token == MINITOKEN_LPAREN)
			i += ft_skip_subshell(minibox, &curr_lexing, lexing_len - i);
		else if (ft_isred(curr_lexing->token))
			i += ft_check_syntax_red(minibox, &curr_lexing);
		else if (curr_lexing->token != MINITOKEN_WSPACE)
			ft_set_minibox_error(minibox, MINICODE_PROCESSORS_COLLISION);
		if (minibox->error.code != MINICODE_NONE)
			return ;
		i++;
		curr_lexing = curr_lexing->next;
	}
}

void	ft_check_syntax_aop(t_minibox *minibox, const t_minilexing *lexing)
{
	t_minilexing	*next_lexing;
	t_minilexing	*prev_lexing;

	next_lexing = lexing->next;
	if (next_lexing && next_lexing->token == MINITOKEN_WSPACE)
		next_lexing = next_lexing->next;
	prev_lexing = lexing->prev;
	if (prev_lexing && prev_lexing->token == MINITOKEN_WSPACE)
		prev_lexing = prev_lexing->prev;
	if (!next_lexing || !prev_lexing)
		ft_set_minibox_error(minibox, MINICODE_OPERATOR_LOST);
	else if (next_lexing->token == MINITOKEN_AND || \
		next_lexing->token == MINITOKEN_OR || \
		next_lexing->token == MINITOKEN_PIPE || \
		prev_lexing->token == MINITOKEN_AND || \
		prev_lexing->token == MINITOKEN_OR || \
		prev_lexing->token == MINITOKEN_PIPE)
		ft_set_minibox_error(minibox, MINICODE_OPERATORS_COLLISION);
}
