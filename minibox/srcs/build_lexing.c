/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_lexing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 19:15:10 by raamayri          #+#    #+#             */
/*   Updated: 2025/08/31 15:28:59 by raamayri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minibox_internal.h"

static int	ft_istoken(const char c)
{
	if (ft_isspace(c))
		return (1);
	if (c == 34 || c == 36 || c == 38 || \
		c == 39 || c == 40 || c == 41 || \
		c == 60 || c == 62 || c == 124)
		return (1);
	return (0);
}

static size_t	ft_set_node_value(t_minibox *minibox, t_minilexing *node,
	char *str)
{
	const char		**miniops = ft_get_token_operators();
	const char		*miniop = miniops[node->token];
	size_t			i[2];

	i[0] = 0;
	i[1] = (node->token == MINITOKEN_SQUOTE || node->token == MINITOKEN_DQUOTE);
	if (node->token == MINITOKEN_SQUOTE || node->token == MINITOKEN_DQUOTE)
		while (str[i[0]] && str[i[0] + 1] && \
			ft_strncmp(&str[i[0] + 1], miniop, ft_strlen(miniop)) != 0)
			i[0]++;
	else if (node->token == MINITOKEN_TEXT)
		while (str[++i[0]] && !ft_istoken(str[i[0]]))
			;
	else
		i[0] = ft_strlen(miniop);
	node->value = ft_calloc(i[0] + 1, sizeof(char));
	if (!node->value)
		ft_set_minibox_error(minibox, MINICODE_ERRNO);
	if (minibox->error.code != MINICODE_NONE)
		return (0);
	ft_memcpy(node->value, &str[i[1]], i[0]);
	node->value[i[0]] = '\0';
	node->length = i[0];
	return (i[0]);
}

static size_t	ft_add_lexing_node(t_minibox *minibox, t_minitoken token,
	char *str)
{
	t_minilexing	*node;
	size_t			len;

	node = ft_calloc(1, sizeof(t_minilexing));
	if (!node)
		ft_set_minibox_error(minibox, MINICODE_ERRNO);
	if (minibox->error.code != MINICODE_NONE)
		return (0);
	node->token = token;
	len = ft_set_node_value(minibox, node, str);
	if (node->token == MINITOKEN_SQUOTE || node->token == MINITOKEN_DQUOTE)
		len += 2;
	if (minibox->error.code != MINICODE_NONE)
		return (0);
	node->next = NULL;
	if (!minibox->lexing)
	{
		node->prev = NULL;
		minibox->lexing = node;
		return (len);
	}
	node->prev = minibox->lexing;
	minibox->lexing->next = node;
	minibox->lexing = minibox->lexing->next;
	return (len);
}

static t_minitoken	ft_get_lexing_token(const char *str)
{
	const char	**miniops = ft_get_token_operators();
	size_t		j;
	size_t		len;

	j = 0;
	while (miniops[j])
	{
		len = ft_strlen(miniops[j]);
		if (ft_strncmp(str, miniops[j], len) == 0)
			return ((t_minitoken)j);
		j++;
	}
	return (MINITOKEN_TEXT);
}

void	ft_build_minibox_lexing(t_minibox *minibox)
{
	t_minitoken	token;
	size_t		i;

	minibox->lexing = NULL;
	i = 0;
	while (i < (size_t)minibox->input->length)
	{
		while (ft_isspace(minibox->input->value[i]))
			i++;
		if (!minibox->input->value[i])
			break ;
		token = ft_get_lexing_token(&minibox->input->value[i]);
		i += ft_add_lexing_node(minibox, token, &minibox->input->value[i]);
		if (minibox->error.code != MINICODE_NONE)
			return ;
	}
	while (minibox->lexing && minibox->lexing->prev)
		minibox->lexing = minibox->lexing->prev;
}
