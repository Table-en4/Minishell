/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_lexing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 19:45:55 by raamayri          #+#    #+#             */
/*   Updated: 2025/09/15 21:35:45 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minibox_internal.h"

static size_t	ft_get_node_value_length(t_minibox *minibox, const char *str)
{
	const t_minitoken	token = minibox->lexing->token;
	const char			**miniops = ft_get_token_operators();
	size_t				i;

	if (miniops[token])
		return (ft_strlen(miniops[token]));
	i = (token == MINITOKEN_SQUOTE || token == MINITOKEN_DQUOTE);
	if (token == MINITOKEN_WSPACE)
		while (ft_isspace(str[i]))
			i++;
	if (token == MINITOKEN_UQUOTE)
		while (str[i + 1] && !(str[i + 1] == 34 || str[i + 1] == 36 || \
			str[i + 1] == 38 || str[i + 1] == 39 || str[i + 1] == 40 || \
			str[i + 1] == 41 || str[i + 1] == 60 || str[i + 1] == 62 || \
			str[i + 1] == 124 || ft_isspace(str[i + 1])))
			i++;
	if (token == MINITOKEN_SQUOTE || token == MINITOKEN_DQUOTE)
	{
		while (str[i] && !((token == MINITOKEN_SQUOTE && str[i] == 39)
				|| (token == MINITOKEN_DQUOTE && str[i] == 34)))
			i++;
		if (!str[i])
			ft_set_minibox_error(minibox, MINICODE_UNCLOSED_QUOTES);
	}
	return (i - (token == MINITOKEN_SQUOTE || token == MINITOKEN_DQUOTE));
}

static size_t	ft_set_node_value(t_minibox *minibox, const char *str)
{
	t_minilexing	*node;
	size_t			len;
	size_t			ofst;

	node = minibox->lexing;
	len = ft_get_node_value_length(minibox, str);
	if (node->token == MINITOKEN_UQUOTE)
		len++;
	if (minibox->error.code != MINICODE_NONE)
		return (0);
	node->value = ft_calloc(len + 1, sizeof(char));
	if (!node->value)
		ft_set_minibox_error(minibox, MINICODE_ERRNO);
	if (minibox->error.code != MINICODE_NONE)
		return (0);
	ofst = (node->token == MINITOKEN_DQUOTE || node->token == MINITOKEN_SQUOTE);
	ft_memcpy(node->value, &str[ofst], len);
	return (len + ofst * 2);
}

static size_t	ft_add_node(t_minibox *minibox, t_minitoken token,
	const char *str)
{
	t_minilexing	*node;
	size_t			len;

	if (minibox->error.code != MINICODE_NONE)
		return (0);
	node = ft_calloc(1, sizeof(t_minilexing));
	if (!node)
		ft_set_minibox_error(minibox, MINICODE_ERRNO);
	if (minibox->error.code != MINICODE_NONE)
		return (0);
	node->token = token;
	node->next = NULL;
	node->prev = NULL;
	if (minibox->lexing)
	{
		node->prev = minibox->lexing;
		minibox->lexing->next = node;
		minibox->lexing = minibox->lexing->next;
	}
	else
		minibox->lexing = node;
	len = ft_set_node_value(minibox, str);
	if (minibox->error.code != MINICODE_NONE)
		return (0);
	return (len);
}

static t_minitoken	ft_get_token(const char *str)
{
	const char	**miniops = ft_get_token_operators();
	size_t		miniops_len;
	size_t		i;

	if (ft_isspace(str[0]))
		return (MINITOKEN_WSPACE);
	i = 1;
	while (miniops[i])
	{
		miniops_len = ft_strlen(miniops[i]);
		if (!ft_strncmp(str, miniops[i], miniops_len))
			return ((t_minitoken)i);
		i++;
	}
	if (str[0] == 34)
		return (MINITOKEN_DQUOTE);
	if (str[0] == 39)
		return (MINITOKEN_SQUOTE);
	return (MINITOKEN_UQUOTE);
}

void	ft_build_minibox_lexing(t_minibox *minibox)
{
	const t_miniinput	*input = minibox->input;
	char				*curr_value;
	int					paren_count;
	size_t				i;

	minibox->lexing = NULL;
	paren_count = 0;
	i = 0;
	while (input->cmd[i])
	{
		curr_value = &input->cmd[i];
		i += ft_add_node(minibox, ft_get_token(curr_value), curr_value);
		if (ft_get_token(curr_value) == MINITOKEN_LPAREN)
			paren_count++;
		if (ft_get_token(curr_value) == MINITOKEN_RPAREN)
			paren_count--;
		if (paren_count < 0)
			ft_set_minibox_error(minibox, MINICODE_UNCLOSED_PARENTHESIS);
		if (minibox->error.code != MINICODE_NONE)
			return ;
	}
	while (minibox->lexing && minibox->lexing->prev)
		minibox->lexing = minibox->lexing->prev;
	if (paren_count != 0)
		ft_set_minibox_error(minibox, MINICODE_UNCLOSED_PARENTHESIS);
}
