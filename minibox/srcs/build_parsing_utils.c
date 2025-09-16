/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_parsing_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 20:43:53 by raamayri          #+#    #+#             */
/*   Updated: 2025/09/14 18:29:14 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minibox_internal.h"

int	ft_isred(const t_minitoken token)
{
	if (token == MINITOKEN_REDAPP || token == MINITOKEN_HEREDOC || \
		token == MINITOKEN_REDOUT || token == MINITOKEN_REDIN)
		return (1);
	return (0);
}

t_minitype	ft_cnv_token_to_type(const t_minitoken token)
{
	static const t_minitype	token_to_type[MINITOKEN_SIZE] = {
	[MINITOKEN_AND] = MINITYPE_AND,
	[MINITOKEN_OR] = MINITYPE_OR,
	[MINITOKEN_PIPE] = MINITYPE_PIPE,
	[MINITOKEN_LPAREN] = MINITYPE_SUBSHELL,
	[MINITOKEN_RPAREN] = MINITYPE_SUBSHELL,
	[MINITOKEN_REDAPP] = MINITYPE_REDAPP,
	[MINITOKEN_HEREDOC] = MINITYPE_HEREDOC,
	[MINITOKEN_REDOUT] = MINITYPE_REDOUT,
	[MINITOKEN_REDIN] = MINITYPE_REDIN,
	};

	if (!token_to_type[token])
		return (MINITYPE_NONE);
	return (token_to_type[token]);
}

size_t	ft_find_tokens(t_minibox *minibox, t_minilexing **lexing,
	const size_t lexing_len, t_minitoken *tokens)
{
	t_minilexing	*curr_lexing;
	size_t			i;
	size_t			j;

	i = 0;
	curr_lexing = (t_minilexing *)*lexing;
	while (curr_lexing && i < lexing_len)
	{
		j = 0;
		while (tokens[j] != MINITOKEN_NONE)
		{
			if (curr_lexing->token == tokens[j++])
				return ((*lexing = curr_lexing), i);
		}
		if (curr_lexing->token == MINITOKEN_LPAREN)
			i += ft_skip_subshell(minibox, &curr_lexing, lexing_len);
		else
			1 && (i++), curr_lexing = curr_lexing->next;
		if (minibox->error.code != MINICODE_NONE)
			return (i);
	}
	return ((*lexing = curr_lexing), i);
}

t_miniparsing	*ft_new_node(t_minibox *minibox, t_miniparsing *parent,
	const t_minitype type)
{
	t_miniparsing	*node;

	node = ft_calloc(1, sizeof(t_miniparsing));
	if (!node)
		ft_set_minibox_error(minibox, MINICODE_ERRNO);
	if (minibox->error.code != MINICODE_NONE)
		return (NULL);
	node->type = type;
	if (!parent)
		minibox->parsing = node;
	else if (parent->type == MINITYPE_SUBSHELL && type == MINITYPE_SUBSHELL)
		ft_set_minibox_error(minibox, MINICODE_SUBSHELL_EMPTY);
	else if (parent->type == MINITYPE_SUBSHELL && !parent->subshell)
		parent->subshell = node;
	else if (parent->type == MINITYPE_SUBSHELL)
		ft_set_minibox_error(minibox, MINICODE_PARENT_OVERLOAD);
	else if (!parent->left)
		parent->left = node;
	else if (!parent->right)
		parent->right = node;
	else
		ft_set_minibox_error(minibox, MINICODE_PARENT_OVERLOAD);
	if (minibox->error.code != MINICODE_NONE)
		return (free(node), NULL);
	return (node);
}
