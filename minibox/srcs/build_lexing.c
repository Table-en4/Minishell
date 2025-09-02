/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_lexing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raamayri <raamayri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 19:15:10 by raamayri          #+#    #+#             */
/*   Updated: 2025/09/02 21:51:04 by raamayri         ###   ########.fr       */
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
	const char	**miniops = ft_get_token_operators();
	const char	*miniop = miniops[node->token];
	size_t		i[2];

	i[0] = (node->token == MINITOKEN_SQUOTE || node->token == MINITOKEN_DQUOTE);
	i[1] = 0;
	if (node->token != MINITOKEN_TEXT && !i[0])
		i[1] = ft_strlen(miniop);
	while ((node->token == MINITOKEN_TEXT || i[0]) && str[i[1] + i[0]])
	{
		if ((i[0] && !ft_strncmp(&str[i[1] + i[0]], miniop, ft_strlen(miniop)))
			|| (node->token == MINITOKEN_TEXT && ft_istoken(str[i[1] + i[0]])))
			break ;
		i[1]++;
	}
	if (i[0] && ft_strncmp(&str[i[1] + i[0]], miniop, ft_strlen(miniop)))
		ft_set_minibox_error(minibox, MINICODE_UNCLOSED_QUOTES);
	else
		node->value = ft_calloc(i[1] + 1, sizeof(char));
	if (minibox->error.code == MINICODE_ERRNO && !node->value)
		ft_set_minibox_error(minibox, MINICODE_ERRNO);
	if (minibox->error.code != MINICODE_NONE)
		return (-1);
	ft_memcpy(node->value, &str[i[0]], i[1]);
	return ((node->value[i[1]] = '\0'), (node->length = i[1]), i[1]);
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
		return (-1);
	node->token = token;
	len = ft_set_node_value(minibox, node, str);
	if (minibox->error.code != MINICODE_NONE)
		return (free(node), -1);
	if (node->token == MINITOKEN_SQUOTE || node->token == MINITOKEN_DQUOTE)
		len += 2;
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
