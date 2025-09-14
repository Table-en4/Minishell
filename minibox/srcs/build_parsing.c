/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 17:19:05 by raamayri          #+#    #+#             */
/*   Updated: 2025/09/13 23:26:45 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minibox_internal.h"

static int	ft_build_parsing_ao(t_minibox *minibox, t_miniparsing *parent,
				const t_minilexing *lexing, const size_t lexing_len);

static int	ft_build_parsing_cmd(t_minibox *minibox, t_miniparsing *parent,
	const t_minilexing *lexing, const size_t lexing_len)
{
	t_minilexing	*curr_lexing;
	t_miniparsing	*node;

	curr_lexing = (t_minilexing *)lexing;
	ft_check_syntax_cmd(minibox, curr_lexing, lexing_len);
	if (minibox->error.code != MINICODE_NONE)
		return (1);
	node = ft_new_node(minibox, parent, MINITYPE_CMD);
	if (minibox->error.code != MINICODE_NONE)
		return (1);
	node->fds = ft_build_parsing_red(minibox, curr_lexing, lexing_len);
	if (minibox->error.code != MINICODE_NONE)
		return (1);
	ft_build_parsing_argc(node, lexing, lexing_len);
	node->argv = ft_calloc(node->argc + 1, sizeof(char *));
	if (!node->argv)
		ft_set_minibox_error(minibox, MINICODE_ERRNO);
	if (minibox->error.code != MINICODE_NONE)
		return (1);
	ft_build_parsing_argv(minibox, node, lexing, lexing_len);
	return (0);
}

static int	ft_build_parsing_ss(t_minibox *minibox, t_miniparsing *parent,
	const t_minilexing *lexing, const size_t lexing_len)
{
	t_minilexing	*curr_lexing;
	t_miniparsing	*node;
	size_t			i;

	curr_lexing = (t_minilexing *)lexing;
	i = ft_find_tokens(minibox, &curr_lexing, lexing_len,
			(t_minitoken [2]){MINITOKEN_RPAREN, MINITOKEN_NONE});
	if (minibox->error.code != MINICODE_NONE)
		return (1);
	if (!curr_lexing || i >= lexing_len)
		return (ft_build_parsing_cmd(minibox, parent, lexing, lexing_len));
	ft_check_syntax_ss(minibox, lexing, lexing_len);
	if (minibox->error.code == MINICODE_NONE)
		node = ft_new_node(minibox, parent, MINITYPE_SUBSHELL);
	if (minibox->error.code == MINICODE_NONE)
		node->fds = ft_build_parsing_red(minibox, lexing, lexing_len);
	if (minibox->error.code != MINICODE_NONE)
		return (1);
	curr_lexing = (t_minilexing *)lexing;
	i -= ft_find_tokens(minibox, &curr_lexing, lexing_len,
			(t_minitoken [2]){MINITOKEN_LPAREN, MINITOKEN_NONE});
	if (minibox->error.code != MINICODE_NONE)
		return (1);
	return (ft_build_parsing_ao(minibox, node, curr_lexing->next, i - 1));
}

static int	ft_build_parsing_p(t_minibox *minibox, t_miniparsing *parent,
	const t_minilexing *lexing, const size_t lexing_len)
{
	t_minilexing	*curr_lexing;
	t_miniparsing	*node;
	t_minitype		node_type;
	size_t			i;

	curr_lexing = (t_minilexing *)lexing;
	i = ft_find_tokens(minibox, &curr_lexing, lexing_len,
			(t_minitoken [2]){MINITOKEN_PIPE, MINITOKEN_NONE});
	if (minibox->error.code != MINICODE_NONE)
		return (1);
	if (!curr_lexing || i >= lexing_len)
		return (ft_build_parsing_ss(minibox, parent, lexing, lexing_len));
	node_type = ft_cnv_token_to_type(curr_lexing->token);
	node = ft_new_node(minibox, parent, node_type);
	if (minibox->error.code != MINICODE_NONE)
		return (1);
	ft_check_syntax_aop(minibox, curr_lexing);
	if (minibox->error.code != MINICODE_NONE)
		return (1);
	ft_build_parsing_ss(minibox, node, lexing, i);
	if (minibox->error.code != MINICODE_NONE)
		return (1);
	i = lexing_len - i - 1;
	return (ft_build_parsing_p(minibox, node, curr_lexing->next, i));
}

static int	ft_build_parsing_ao(t_minibox *minibox, t_miniparsing *parent,
	const t_minilexing *lexing, const size_t lexing_len)
{
	t_minilexing	*curr_lexing;
	t_miniparsing	*node;
	t_minitype		node_type;
	size_t			i;

	curr_lexing = (t_minilexing *)lexing;
	i = ft_find_tokens(minibox, &curr_lexing, lexing_len,
			(t_minitoken [3]){MINITOKEN_AND, MINITOKEN_OR, MINITOKEN_NONE});
	if (minibox->error.code != MINICODE_NONE)
		return (1);
	if (!curr_lexing || i >= lexing_len)
		return (ft_build_parsing_p(minibox, parent, lexing, lexing_len));
	node_type = ft_cnv_token_to_type(curr_lexing->token);
	node = ft_new_node(minibox, parent, node_type);
	if (minibox->error.code != MINICODE_NONE)
		return (1);
	ft_check_syntax_aop(minibox, curr_lexing);
	if (minibox->error.code != MINICODE_NONE)
		return (1);
	ft_build_parsing_p(minibox, node, lexing, i);
	if (minibox->error.code != MINICODE_NONE)
		return (1);
	i = lexing_len - i - 1;
	return (ft_build_parsing_ao(minibox, node, curr_lexing->next, i));
}

void	ft_build_minibox_parsing(t_minibox *minibox)
{
	t_minilexing	*curr_lexing;
	size_t			lexing_len;

	curr_lexing = minibox->lexing;
	lexing_len = 0;
	while (curr_lexing)
	{
		lexing_len++;
		curr_lexing = curr_lexing->next;
	}
	ft_build_parsing_ao(minibox, NULL, minibox->lexing, lexing_len);
	if (minibox->error.code != MINICODE_NONE)
		return ;
}
