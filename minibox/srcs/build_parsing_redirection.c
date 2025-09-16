/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_parsing_redirection.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 20:09:59 by raamayri          #+#    #+#             */
/*   Updated: 2025/09/15 21:12:34 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minibox_internal.h"

static int	ft_open_red(t_minibox *minibox, t_minifd *node)
{
	int	fd;

	fd = -1;
	if (node->type == MINITYPE_REDIN)
		fd = open(node->file, O_RDONLY);
	else if (node->type == MINITYPE_REDOUT)
		fd = open(node->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (node->type == MINITYPE_REDAPP)
		fd = open(node->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (node->type == MINITYPE_HEREDOC)
		fd = ft_open_heredoc(minibox, node);
	if (fd == -1)
		ft_set_minibox_error(minibox, MINICODE_UNCLOSED_QUOTES);
	return (fd);
}

static int	ft_add_node(t_minibox *minibox,
	const t_minilexing *lexing, const t_minitoken token, t_minifd **red)
{
	t_minilexing	*next_lexing;
	t_minifd		*node;

	node = ft_calloc(1, sizeof(t_minifd));
	if (!node)
		ft_set_minibox_error(minibox, MINICODE_ERRNO);
	if (minibox->error.code != MINICODE_NONE)
		return (1);
	node->type = ft_cnv_token_to_type(token);
	next_lexing = (t_minilexing *)lexing->next;
	if (next_lexing->token == MINITOKEN_WSPACE)
		next_lexing = next_lexing->next;
	node->file = ft_strdup(next_lexing->value);
	if (!node->file)
		ft_set_minibox_error(minibox, MINICODE_ERRNO);
	if (minibox->error.code != MINICODE_NONE)
		return (free(node), 1);
	node->fd = ft_open_red(minibox, node);
	if (minibox->error.code != MINICODE_NONE)
		return (free(node->file), free(node), 1);
	if (!*red)
		*red = node;
	else
		1 && (node->prev = *red), ((*red)->next = node), *red = (*red)->next;
	return (0);
}

t_minifd	*ft_build_parsing_red(t_minibox *minibox,
	const t_minilexing *lexing, const size_t lexing_len)
{
	t_minilexing	*curr_lexing;
	t_minifd		*red;
	size_t			i;

	i = 0;
	red = NULL;
	curr_lexing = (t_minilexing *)lexing;
	while (curr_lexing && i < lexing_len)
	{
		if (curr_lexing->token == MINITOKEN_LPAREN)
			i += ft_skip_subshell(minibox, &curr_lexing, lexing_len - i);
		else if (ft_isred(curr_lexing->token))
			ft_add_node(minibox, curr_lexing, curr_lexing->token, &red);
		if (minibox->error.code != MINICODE_NONE)
			return (red);
		1 && (i++), curr_lexing = curr_lexing->next;
	}
	while (red && red->prev)
		red = red->prev;
	return (red);
}
