/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizeing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 12:33:18 by molapoug          #+#    #+#             */
/*   Updated: 2025/09/17 12:33:19 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minilexing	*create_token(char *value)
{
	t_minilexing	*token;

	token = malloc(sizeof(t_minilexing));
	if (!token)
		return (NULL);
	token->value = ft_strdup(value);
	token->next = NULL;
	return (token);
}

static void	cleanup_tokens(t_minilexing *tokens)
{
	t_minilexing	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->value);
		free(tmp);
	}
}

static t_minilexing	*create_tokens_from_args(char **args)
{
	t_minilexing	*tokens;
	t_minilexing	*current;
	t_minilexing	*new_token;
	int				i;

	tokens = NULL;
	current = NULL;
	i = 0;
	while (args[i])
	{
		new_token = create_token(args[i]);
		if (!new_token)
		{
			cleanup_tokens(tokens);
			return (NULL);
		}
		if (!tokens)
			tokens = new_token;
		else
			current->next = new_token;
		current = new_token;
		i++;
	}
	return (tokens);
}

t_minibox	*create_command_node(char **args)
{
	t_minibox		*node;
	t_minilexing	*tokens;

	node = malloc(sizeof(t_minibox));
	if (!node)
		return (NULL);
	node->parsing = malloc(sizeof(t_miniparsing));
	if (!node->parsing)
		return (free(node), NULL);
	node->parsing->type = MINITYPE_CMD;
	node->parsing->left = NULL;
	node->parsing->right = NULL;
	tokens = create_tokens_from_args(args);
	if (!tokens)
		return (free(node->parsing), free(node), NULL);
	node->lexing = tokens;
	return (node);
}

void	free_token_list(t_minilexing *tokens)
{
	t_minilexing	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->value);
		free(tmp);
	}
}
